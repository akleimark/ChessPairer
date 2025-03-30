#ifndef TOURNAMENTPLAYERSMODEL_H
#define TOURNAMENTPLAYERSMODEL_H

#include "MVC.h"
#include "PlayerListModel.h"
#include "TournamentListModel.h"

class TournamentPlayersModel : public Model
{
public:
    TournamentPlayersModel(PlayerListModel *playerListModel, Tournament *tournament, SettingsModel *settingsModel);
    SettingsModel* getSettingsModel() const { return settingsModel; }
    PlayerListModel* getPlayerListModel() const { return playerListModel;}

private:
    PlayerListModel *playerListModel;
    Tournament *tournament;
    SettingsModel *settingsModel;

};

#endif // TOURNAMENTPLAYERSMODEL_H
