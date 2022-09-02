#include "ManageTournamentPlayersController.h"
#include <iostream>
#include "ViewModel.h"

void ManageTournamentPlayersController::changeTournament(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    unsigned int index = event.GetSelection();

    TournamentModel *tournament = viewModel->getTournaments()->get(index);

    try
    {
         tournament->getAllTournamentPlayers();
    }
    catch(DatabaseErrorException &error)
    {
        std::cout << error.what() << std::endl;
    }

}
