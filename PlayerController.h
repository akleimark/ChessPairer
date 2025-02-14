#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "MVC.h"
#include "PlayerModel.h"
#include "PlayerListView.h"

class PlayerController : public Controller {
    public:
        PlayerController(PlayerModel *model, PlayerListView *view);
        void addPlayer(const QString &name, int rating, int fideId);

    private:
        PlayerModel *playerModel;
        PlayerListView *playerView;
};

#endif // PLAYERCONTROLLER_H
