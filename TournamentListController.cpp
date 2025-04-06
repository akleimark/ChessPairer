#include "TournamentListController.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Logger.h"
#include "TournamentListModel.h"
#include <QComboBox>
#include "ChessPairer.h"

TournamentListController::TournamentListController(TournamentListModel &model, TournamentListView *view)
    : Controller(model, view), tournamentListModel(model), tournamentListView(view)
{
    // Koppla signalen från vyn till kontrollerns slot
    connect(view, &TournamentListView::cellChanged, this, &TournamentListController::onCellChanged);
}

bool TournamentListController::askForTournamentData(Tournament &tournament)
{
    const QString TITLE = "Lägg till en turnering";
    bool ok;

    // Fråga om namn på turneringen
    const QString NAME = QInputDialog::getText(view, TITLE, "Namn:", QLineEdit::Normal, "", &ok);
    tournament.setName(NAME);
    if (!ok || !tournament.checkName())
    {
        return false;
    }

    // Fråga om startdatum
    const QString STARTDATE_STR = QInputDialog::getText(view, TITLE, "Startdatum (YYYY-MM-DD):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok)
    {
        return false;
    }
    QDate startDate = QDate::fromString(STARTDATE_STR, "yyyy-MM-dd");
    tournament.setStartDate(startDate);
    if (!tournament.checkStartDate())
    {
        return false;
    }

    // Fråga om slutdatum
    const QString ENDDATE_STR = QInputDialog::getText(view, TITLE, "Slutdatum (YYYY-MM-DD):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok)
    {
        return false;
    }
    QDate endDate = QDate::fromString(ENDDATE_STR, "yyyy-MM-dd");
    tournament.setEndDate(endDate);
    if (!tournament.checkEndDate())
    {
        return false;
    }

    // Fråga om antal ronder
    const unsigned int NUMBER_OF_ROUNDS = QInputDialog::getInt(view, TITLE, "Antal ronder:", Tournament::getDefaultNumberOfRounds(), Tournament::getMinimumNumberOfRounds(), Tournament::getMaximumNumberOfRounds(), 1, &ok);
    tournament.setNumberOfRounds(NUMBER_OF_ROUNDS);
    if (!ok || !tournament.checkNumberOfRounds())
    {
        return false;
    }

    // Skapa en combo-box för att välja lottningssystem
    QComboBox* pairingSystemComboBox = new QComboBox(view);
    pairingSystemComboBox->addItem("Monrad");
    pairingSystemComboBox->addItem("Berger");
    pairingSystemComboBox->setCurrentIndex(0);  // Förvalt till första alternativet

    // Skapa en dialog för att visa combo-boxen
    QDialog dialog(view);
    dialog.setWindowTitle(TITLE);
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(pairingSystemComboBox);
    QPushButton* okButton = new QPushButton("OK", &dialog);
    layout->addWidget(okButton);
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // Visa dialogen och vänta på användarens val
    if (dialog.exec() == QDialog::Accepted)
    {
        // Hämta valt system och sätt det på turneringen
        QString selectedPairingSystem = pairingSystemComboBox->currentText();
        tournament.setPairingSystem(selectedPairingSystem);

        // Kontrollera om det valda lottningssystemet är korrekt
        if (!tournament.checkPairingSystem())
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void TournamentListController::onAddTournamentClicked()
{
    Tournament tournament;
    if(askForTournamentData(tournament))
    {
        const unsigned int TOURNAMENT_ID = tournamentListModel.addToDatabase(tournament);
        tournament.setId(TOURNAMENT_ID);
        tournamentListModel.addToContainer(tournament);
        tournamentListModel.notifyAllViews();
    }
    else
    {
        Logger::getInstance()->logWarning("Turneringen kunde inte läggas till på grund av felaktiga data.");        
    }
}

void TournamentListController::onCellChanged(int row, int column, const QString &newValue)
{
    if (row >= 0 && row < tournamentListModel.size())
    {
        Tournament &tournament = tournamentListModel.at(row);
        Tournament oldTournament = tournament; // Skapa en djup kopia av objektet

        switch (column)
        {
        case 1: // Namn
            tournament.setName(newValue);
            break;
        case 2: // Startdatum (konvertera från QString till QDate)
            tournament.setStartDate(QDate::fromString(newValue, "yyyy-MM-dd"));
            break;
        case 3: // Slutdatum (konvertera från QString till QDate)
            tournament.setEndDate(QDate::fromString(newValue, "yyyy-MM-dd"));
            break;
        case 4: // Antal ronder (konvertera från QString till int)
            tournament.setNumberOfRounds(newValue.toInt());
            break;
        case 5: // Lottningssystem
            tournament.setPairingSystem(newValue);
            break;
        default:
            return; // Ignorera om det är en okänd kolumn
        }

        if (tournament.isValid())
        {
            // Uppdatera databasen via modellen
            tournamentListModel.updateDatabase(tournament);
        }
        else
        {
            tournament = oldTournament; // Återställ originalobjektet om valideringen misslyckas
            Logger::getInstance()->logWarning("Felaktiga turneringsdata angivna.");
            tournamentListModel.notifyView(view);
        }
    }
}


void TournamentListController::onRemoveTournamentRequested(const unsigned int &id)
{
    const QString message = QString("Bekräfta borttagning av turnering %1").arg(id);
    // Skapa en bekräftelsedialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(tournamentListView, message,
                                  "Är du säker på att du vill ta bort denna turnering?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        tournamentListModel.removeById(id); // Ta bort turneringen från modellen och databasen
        tournamentListModel.notifyAllViews();
    }
}

void TournamentListController::onSelectTournamentRequested(const unsigned int &id)
{
    Tournament *tournament = tournamentListModel.findTournamentById(id);
    tournament->getTournamentDataFromDatabase();
    tournamentListModel.setSelectedTournament(*tournament);
    ChessPairer::getInstance()->populateMenu();
}
