#include "ManageTournamentPlayersController.h"
#include <iostream>
#include "ViewModel.h"
#include "Defs.h"
#include <wx/msgdlg.h>

/**
    Den h?r funktionen k?rs, n?r anv?ndaren har valt att ?ndra p? vilken turnering som han eller hon vill
    jobba med f?r tillf?llet.
*/
void ManageTournamentPlayersController::changeTournament(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);
    unsigned int index = event.GetSelection();

    TournamentModel *tournament = viewModel->getTournaments()->get(index);
    viewModel->setTournament(tournament);

    try
    {
         tournament->getAllTournamentPlayers();
    }
    catch(DatabaseErrorException &error)
    {
        std::cout << error.what() << std::endl;
    }
    viewModel->notifyView(view);
}

/**
    Den h?r funktionen ?ndrar vilken spelare som f?r tillf?llet ?r vald. Den spelaren kan
    anv?ndaren senare l?gga till.
*/
void ManageTournamentPlayersController::selectPlayer(wxGridEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);
    if(viewModel->getTournamentModel() == nullptr)
    {
        return;
    }
    ChessplayerModel *chessplayer = viewModel->getChessplayerList()->get(event.GetRow());
    TournamentPlayerModel *tournamentPlayer = TournamentPlayerModel::clone(chessplayer);
    tournamentPlayer->setTournamentID(viewModel->getTournamentModel()->getId());
    viewModel->setTournamentPlayer(tournamentPlayer);
}

/**

    Den h?r funktionen ?ndrar vilken turneringsspelare som f?r tillf?llet ?r vald. Den spelaren kan
    anv?ndaren senare v?lja att ta bort fr?n turneringen.
*/

void ManageTournamentPlayersController::selectTournamentPlayer(wxGridEvent &event)
{
    const unsigned int ROW_INDEX = event.GetRow();
    ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);
    if(viewModel->getTournamentModel() == nullptr)
    {
        return;
    }

    TournamentPlayerModel *tournamentPlayer = viewModel->getTournamentModel()->atIndex(ROW_INDEX);
    viewModel->setTournamentPlayer(tournamentPlayer);
}
/**
    Den h?r funktionen anv?nds f?r att l?gga till den spelare som f?r tillf?llet ?r vald till
    den valda turneringen.
*/
void ManageTournamentPlayersController::addPlayer(wxCommandEvent &event)
{
    try
    {
        ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);
        TournamentPlayerModel *player = viewModel->getTournamentPlayerModel();
        TournamentModel *tournament = viewModel->getTournamentModel();
        if(tournament == nullptr || player == nullptr)
        {
            return;
        }

        player->addToDatabase();
        tournament->addTournamentPlayer(player);
        viewModel->notifyView(view);
    }
    catch(Exception &error)
    {
        wxMessageBox(error.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
    }
}
/**
    Den h?r funktionen anv?nds f?r att ta bort vald turneringsspelare ur den turnering, som f?r tillf?llet
    ?r vald.
*/
void ManageTournamentPlayersController::removePlayer(wxCommandEvent &event)
{
    try
    {
        ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);
        TournamentPlayerModel *tournamentPlayer = viewModel->getTournamentPlayerModel();
        viewModel->getTournamentModel()->removeTournamentPlayer(tournamentPlayer);
        viewModel->notifyView(view);
    }
    catch(Exception &error)
    {
        error.showDialog();
    }
}

/**
    Den h?r funktionen anv?nds f?r att generera nya inlottningsnummer till turneringsdeltagarna.
*/
void ManageTournamentPlayersController::generatePlayerNumbers(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);
    TournamentModel *tournament = viewModel->getTournamentModel();
    if(tournament == nullptr)
    {
        return;
    }

    try
    {
        tournament->generatePlayerNumbers();
        viewModel->notifyView(view);
    }
    catch(Exception &error)
    {
        error.showDialog();
    }

}
