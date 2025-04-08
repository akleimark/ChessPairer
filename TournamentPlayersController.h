#ifndef TOURNAMENTPLAYERLISTCONTROLLER_H
#define TOURNAMENTPLAYERLISTCONTROLLER_H

#include "MVC.h"
#include "TournamentPlayersModel.h"
#include "TournamentPlayersView.h"

class TournamentPlayersController : public Controller
{
public:
    TournamentPlayersController(TournamentPlayersModel &model, TournamentPlayersView *view);

private:
    TournamentPlayersModel &tournamentPlayersModel;
    TournamentPlayersView *tournamentPlayersView;

public slots:
    void onAddTournamentPlayerRequested(const unsigned int &fideId);
    void onRemoveTournamentPlayerRequested(const unsigned int &fideId);
};

#endif // TOURNAMENTPLAYERLISTCONTROLLER_H
