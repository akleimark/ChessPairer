#include "ManageTournamentPlayersController.h"
#include <iostream>
#include "ViewModel.h"
#include "Defs.h"
#include <wx/msgdlg.h>

/**
    Den här funktionen körs, när användaren har valt att ändra på vilken turnering som han eller hon vill
    jobba med för tillfället.
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
    Den här funktionen ändrar vilken spelare som för tillfället är vald. Den spelaren kan
    användaren senare lägga till.
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

    Den här funktionen ändrar vilken turneringsspelare som för tillfället är vald. Den spelaren kan
    användaren senare välja att ta bort från turneringen.
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
    Den här funktionen används för att lägga till den spelare som för tillfället är vald till
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
    Den här funktionen används för att ta bort vald turneringsspelare ur den turnering, som för tillfället
    är vald.
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
    Den här funktionen används för att generera nya inlottningsnummer till turneringsdeltagarna.
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
