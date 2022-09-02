#include "ManageTournamentPlayersController.h"
#include <iostream>
#include "ViewModel.h"

void ManageTournamentPlayersController::changeTournament(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    unsigned int index = event.GetSelection();

    TournamentModel *tournament = viewModel->getTournaments()->get(index);
    viewModel->tournament(tournament);

    try
    {
         tournament->getAllTournamentPlayers();
    }
    catch(DatabaseErrorException &error)
    {
        std::cout << error.what() << std::endl;
    }

    //viewModel->notifyView(view);

}
void ManageTournamentPlayersController::selectPlayer(wxGridEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    ChessplayerModel *chessplayer = viewModel->getChessplayerList()->get(event.GetRow());
    TournamentPlayerModel *tournamentPlayer = TournamentPlayerModel::clone(chessplayer);
    viewModel->tournamentPlayer(tournamentPlayer);
}

void ManageTournamentPlayersController::addPlayer(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    TournamentPlayerModel *player = viewModel->getTournamentPlayerModel();
    player->print();

}

