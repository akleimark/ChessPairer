#include "TournamentListController.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Logger.h"

TournamentListController::TournamentListController(TournamentListModel *model, TournamentListView *view)
    : Controller(model, view), tournamentListModel(model), tournamentListView(view)
{
    // Koppla signalen från vyn till kontrollerns slot
    connect(view, &TournamentListView::cellChanged, this, &TournamentListController::onCellChanged);
}

void TournamentListController::onAddTournamentClicked()
{
    Tournament tournament;
    const QString TITLE = "Lägg till en turnering";
    bool ok;

    const QString NAME = QInputDialog::getText(view, TITLE, "Namn:", QLineEdit::Normal, "", &ok);
    tournament.setName(NAME);
    if (!ok || !tournament.checkName()) return;

    const QString STARTDATE_STR = QInputDialog::getText(view, TITLE, "Startdatum (YYYY-MM-DD):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok) return;
    QDate startDate = QDate::fromString(STARTDATE_STR, "yyyy-MM-dd");
    tournament.setStartDate(startDate);
    if (tournament.checkStartDate())
    {
        return;
    }

    const QString ENDDATE_STR = QInputDialog::getText(view, TITLE, "Slutdatum (YYYY-MM-DD):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok) return;
    QDate endDate = QDate::fromString(ENDDATE_STR, "yyyy-MM-dd");
    tournament.setEndDate(endDate);
    if (!tournament.checkEndDate())
    {      
        return;
    }

    const unsigned int NUMBER_OF_ROUNDS = QInputDialog::getInt(view, TITLE, "Antal ronder:", Tournament::getDefaultNumberOfRounds(), Tournament::getMinimumNumberOfRounds(), Tournament::getMaximumNumberOfRounds(), 1, &ok);
    tournament.setNumberOfRounds(NUMBER_OF_ROUNDS);
    if (!ok || !tournament.checkNumberOfRounds()) return;

    const QString PAIRING_SYSTEM = QInputDialog::getText(view, TITLE, "Lottningssystem:", QLineEdit::Normal, "", &ok);
    tournament.setPairingSystem(PAIRING_SYSTEM);
    if (!ok || !tournament.checkPairingSystem()) return;

    tournamentListModel->addToDatabase(tournament);
    tournamentListModel->addToContainer(tournament);
    tournamentListModel->notifyAllViews();
}


void TournamentListController::onCellChanged(int row, int column, const QString &newValue)
{
    if (row >= 0 && row < tournamentListModel->size())
    {
        Tournament &tournament = tournamentListModel->at(row);
        const Tournament oldTournament = tournament;
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

        // Uppdatera databasen via modellen
        if(tournament.isValid())
        {
            tournamentListModel->updateDatabase(tournament);
        }
        else
        {
            tournament = oldTournament;
            Logger::getInstance()->logWarning("Felaktiga turneringdata angivna.");
            tournamentListModel->notifyView(view);
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
        // Ta bort turneringen från modellen och databasen
        if (model)
        {
            tournamentListModel->removeById(id); // Ta bort turneringen från modellen och databasen
            tournamentListModel->notifyAllViews();
        }
    }
}
