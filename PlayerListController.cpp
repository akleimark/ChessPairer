#include "PlayerListController.h"
#include <QInputDialog>

PlayerListController::PlayerListController(PlayerModel *model, PlayerListView *view)
    : Controller(model, view), playerModel(model), playerView(view)
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

    PlayerModel &playerModel = *static_cast<PlayerModel*>(model);
    playerModel.addPlayerToContainer(Player(name, rating, fideId));
    playerModel.addPlayerToDatabase(Player(name, rating, fideId));

    model->notifyAllViews();
}

