#ifndef PLAYERLISTCONTROLLER_H
#define PLAYERLISTCONTROLLER_H

#include "MVC.h"
#include "PlayerModel.h"
#include "PlayerListView.h"

class PlayerListController : public Controller {

    public:
        PlayerListController(PlayerModel *model, PlayerListView *view);


    public slots:
        void onAddPlayerClicked();

    private:
        PlayerModel *playerModel;
        PlayerListView *playerView;
};

#endif // PLAYERLISTCONTROLLER_H
