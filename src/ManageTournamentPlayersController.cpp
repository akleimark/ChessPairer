#include "ManageTournamentPlayersController.h"
#include <iostream>
#include "ViewModel.h"
#include "Defs.h"
#include <wx/msgdlg.h>

void ManageTournamentPlayersController::changeTournament(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
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
void ManageTournamentPlayersController::selectPlayer(wxGridEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    if(viewModel->getTournamentModel() == nullptr)
    {
        return;
    }
    ChessplayerModel *chessplayer = viewModel->getChessplayerList()->get(event.GetRow());
    TournamentPlayerModel *tournamentPlayer = TournamentPlayerModel::clone(chessplayer);
    tournamentPlayer->setTournamentID(viewModel->getTournamentModel()->getId());
    viewModel->setTournamentPlayer(tournamentPlayer);
}

void ManageTournamentPlayersController::selectTournamentPlayer(wxGridEvent &event)
{
    const unsigned int ROW_INDEX = event.GetRow();
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    if(viewModel->getTournamentModel() == nullptr)
    {
        return;
    }

    TournamentPlayerModel *tournamentPlayer = viewModel->getTournamentModel()->atIndex(ROW_INDEX);
    viewModel->setTournamentPlayer(tournamentPlayer);
}



void ManageTournamentPlayersController::addPlayer(wxCommandEvent &event)
{
    try
    {
        ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
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

void ManageTournamentPlayersController::removePlayer(wxCommandEvent &event)
{
    try
    {
        ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
        TournamentPlayerModel *tournamentPlayer = viewModel->getTournamentPlayerModel();
        viewModel->getTournamentModel()->removeTournamentPlayer(tournamentPlayer);
        viewModel->notifyView(view);
    }
    catch(Exception &error)
    {
        error.showDialog();
    }
}

void ManageTournamentPlayersController::generatePlayerNumbers(wxCommandEvent &event)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;
    TournamentModel *tournament = viewModel->getTournamentModel();
    if(tournament == nullptr)
    {
        return;
    }

    tournament->generatePlayerNumbers();
    viewModel->notifyView(view);
}

