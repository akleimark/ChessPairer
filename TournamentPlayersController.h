#ifndef TOURNAMENTPLAYERLISTCONTROLLER_H
#define TOURNAMENTPLAYERLISTCONTROLLER_H

#include "MVC.h"
#include "TournamentPlayersModel.h"
#include "TournamentPlayersView.h"

class TournamentPlayersController : public Controller
{
public:
    TournamentPlayersController(TournamentPlayersModel *model, TournamentPlayersView *view);

private:
    TournamentPlayersModel *tournamentPlayersModel;
    TournamentPlayersView *tournamentPlayersView;

public slots:
    void onAddTournamentPlayerClicked();

};

#endif // TOURNAMENTPLAYERLISTCONTROLLER_H
