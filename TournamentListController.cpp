#include "TournamentListController.h"
#include <QInputDialog>
#include <QMessageBox>

TournamentListController::TournamentListController(TournamentListModel *model, TournamentListView *view)
    : Controller(model, view), tournamentListModel(model), tournamentListView(view)
{
    // Koppla signalen från vyn till kontrollerns slot
    connect(view, &TournamentListView::cellChanged, this, &TournamentListController::onCellChanged);
}

void TournamentListController::onAddTournamentClicked()
{
    const QString TITLE = "Lägg till en turnering";
    bool ok;

    const QString name = QInputDialog::getText(view, TITLE, "Namn:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    const QString startDateStr = QInputDialog::getText(view, TITLE, "Startdatum (YYYY-MM-DD):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok) return;
    QDate startDate = QDate::fromString(startDateStr, "yyyy-MM-dd");
    if (!startDate.isValid()) {
        QMessageBox::warning(view, TITLE, "Ogiltigt startdatum. Ange formatet YYYY-MM-DD.");
        return;
    }

    const QString endDateStr = QInputDialog::getText(view, TITLE, "Slutdatum (YYYY-MM-DD):", QLineEdit::Normal, QDate::currentDate().toString("yyyy-MM-dd"), &ok);
    if (!ok) return;
    QDate endDate = QDate::fromString(endDateStr, "yyyy-MM-dd");
    if (!endDate.isValid())
    {
        QMessageBox::warning(view, TITLE, "Ogiltigt slutdatum. Ange formatet YYYY-MM-DD.");
        return;
    }

    const unsigned int numberOfRounds = QInputDialog::getInt(view, TITLE, "Antal ronder:", 7, 3, 14, 1, &ok);
    if (!ok) return;

    const QString pairingSystem = QInputDialog::getText(view, TITLE, "Lottningssystem:", QLineEdit::Normal, "", &ok);
    if (!ok || pairingSystem.isEmpty()) return;

    const Tournament TOURNAMENT(name, startDate, endDate, numberOfRounds, pairingSystem);

    tournamentListModel->addToDatabase(TOURNAMENT);
    tournamentListModel->addToContainer(TOURNAMENT);
    tournamentListModel->notifyAllViews();
}


void TournamentListController::onCellChanged(int row, int column, const QString &newValue)
{
    if (row >= 0 && row < tournamentListModel->size())
    {
        Tournament &tournament = tournamentListModel->at(row);

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
        tournamentListModel->updateDatabase(tournament);
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





