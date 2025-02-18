#include "PlayerListController.h"
#include <QInputDialog>
#include <QMessageBox>

PlayerListController::PlayerListController(PlayerListModel *model, PlayerListView *view)
    : Controller(model, view), playerListModel(model), playerListView(view)
{
    // Koppla signalen från vyn till kontrollerns slot
    connect(view, &PlayerListView::cellChanged, this, &PlayerListController::onCellChanged);
}

void PlayerListController::onAddPlayerClicked()
{
    bool ok;
    QString name = QInputDialog::getText(view, "Lägg till spelare", "Namn:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    int rating = QInputDialog::getInt(view, "Lägg till spelare", "Rating:", 1000, 100, 3000, 1, &ok);
    if (!ok) return;

    int fideId = QInputDialog::getInt(view, "Lägg till spelare", "FIDE-ID:", 1000000, 100000, 9999999, 1, &ok);
    if (!ok) return;

    PlayerListModel &playerModel = *static_cast<PlayerListModel*>(model);
    playerModel.addToContainer(Player(name, rating, fideId));
    playerModel.addToDatabase(Player(name, rating, fideId));

    playerListModel->doSort();
    playerListModel->notifyAllViews();
}

void PlayerListController::onCellChanged(int row, int column, const QString &newValue)
{   
    if (row >= 0 && row < playerListModel->size())
    {
        Player &player = playerListModel->at(row);

        switch (column)
        {
        case 0:
            player.setName(newValue);
            break;
        case 1:
            player.setRating(newValue.toInt());
            break;
        case 2:
            player.setFideId(newValue.toInt());
            break;
        }

        // Uppdatera databasen via modellen
        playerListModel->updateDatabase(player);
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
        // Ta bort spelaren från modellen och databasen
        if (model)
        {
            playerListModel->removeById(fideId); // Ta bort spelaren från modellen och databasen
            playerListModel->notifyAllViews();
        }
    }
}




