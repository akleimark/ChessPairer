#include "PlayerListController.h"
#include <QInputDialog>

PlayerListController::PlayerListController(PlayerListModel *model, PlayerListView *view)
    : Controller(model, view), playerListModel(model), playerView(view)
{

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
    playerModel.addPlayerToContainer(Player(name, rating, fideId));
    playerModel.addPlayerToDatabase(Player(name, rating, fideId));

    model->notifyAllViews();
}

