#include "PlayerListController.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Logger.h"

PlayerListController::PlayerListController(PlayerListModel &model, PlayerListView *view)
    : Controller(model, view), playerListModel(model), playerListView(view)
{
    // Koppla signalen från vyn till kontrollerns slot
    connect(view, &PlayerListView::cellChanged, this, &PlayerListController::onCellChanged);
}

void PlayerListController::onAddPlayerClicked()
{
    Player newPlayer;

    bool ok;
    const QString NAME = QInputDialog::getText(view, "Lägg till spelare", "Namn:", QLineEdit::Normal, "", &ok);
    newPlayer.setName(NAME);
    if (!ok || !newPlayer.checkName()) return;

    const unsigned int RATING = QInputDialog::getInt(view, "Lägg till spelare", "Rating:", 1000, Player::getMinimumRating(), Player::getMaximumRating(), 1, &ok);
    newPlayer.setRating(RATING);
    if (!ok || !newPlayer.checkRating()) return;

    int fideId = QInputDialog::getInt(view, "Lägg till spelare", "FIDE-ID:", 1000000, 100000, 9999999, 1, &ok);
    newPlayer.setFideId(fideId);
    if (!ok || !newPlayer.checkFideId()) return;

    playerListModel.addToContainer(newPlayer);
    playerListModel.addToDatabase(newPlayer);

    playerListModel.doSort();
    playerListModel.notifyAllViews();

}

void PlayerListController::onCellChanged(const unsigned int &row, const unsigned int &column, const QString &newValue)
{
    if (row >= 0 && row < playerListModel.size())
    {
        Player &player = playerListModel.at(row);
        Player oldPlayer = player; // Skapa en kopia av objektet

        switch (column)
        {
        case 0:
            player.setName(newValue);
            break;
        case 1:
            player.setRating(newValue.toUInt());
            break;
        }

        if (!player.isValid())
        {
            player = oldPlayer; // Återställ originalet vid felaktig inmatning
            Logger::getInstance()->logWarning("Felaktiga spelaruppgifter angivna.");
            playerListModel.notifyView(view);
        }
        else
        {
            // Uppdatera databasen via modellen
            playerListModel.updateDatabase(player);
        }
    }
}


void PlayerListController::onRemovePlayerRequested(const unsigned int &fideId)
{
    const QString message = QString("Bekräfta borttagning av %1").arg(fideId);
    // Skapa en bekräftelsedialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(playerListView, message,
          "Är du säker på att du vill ta bort denna spelare?",
          QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        playerListModel.removeById(fideId); // Ta bort spelaren från modellen och databasen
        playerListModel.notifyAllViews();
    }
}
