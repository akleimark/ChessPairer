#include "TournamentPlayersController.h"
#include <iostream>

TournamentPlayersController::TournamentPlayersController(TournamentPlayersModel &model, TournamentPlayersView *view):
    Controller(model, view), tournamentPlayersModel(model), tournamentPlayersView(view)
{

}

void TournamentPlayersController::onAddTournamentPlayerRequested(const unsigned int &fideId)
{
    Player *player = tournamentPlayersModel.getPlayerListModel().findPlayerById(fideId);
    TournamentPlayer newPlayer = TournamentPlayer(player->getFideId(), player->getName(), player->getRating(), 0);
    tournamentPlayersModel.getTournament().addTournamentPlayer(newPlayer);
    tournamentPlayersModel.notifyAllViews();
}
