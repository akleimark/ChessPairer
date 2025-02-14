#include "PlayerController.h"

PlayerController::PlayerController(PlayerModel *model, PlayerListView *view)
    : Controller(model, view), playerModel(model), playerView(view)
{

}

void PlayerController::addPlayer(const QString &name, int rating, int fideId)
{
    playerModel->addPlayer(Player(name, rating, fideId));
}
