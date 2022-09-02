#include "ManageTournamentPlayersView.h"
#include "ViewModel.h"
#include "ManageTournamentPlayersController.h"
#include "Defs.h"
#include <wx/msgdlg.h>

ManageTournamentPlayersView::ManageTournamentPlayersView(wxWindow *p_parent):
    View(p_parent, "Hantera turneringsspelare")
{
    tournamentBox = new wxBoxSizer(wxHORIZONTAL);
    tournamentComboBox = new wxComboBox(parent, -1);
    tournamentComboBox->SetMinSize(wxSize(200, 40));
    tournamentBox->Add(tournamentComboBox, 0, wxALL, 10);
    this->Add(tournamentBox, View::MARGIN, wxALL, 0);

    tableBox = new wxBoxSizer(wxHORIZONTAL);
    chessplayerPool = new Table(parent, {"Id", "Namn"});
    tableBox->Add(chessplayerPool, 0, wxALL, 10);
    tournamentPlayers = new Table(parent, {"Id", "Namn"});
    tableBox->Add(tournamentPlayers, 0, wxALL, 10);


    this->Add(tableBox, View::MARGIN, wxALL, 0);


}
ManageTournamentPlayersView::~ManageTournamentPlayersView()
{

}

void ManageTournamentPlayersView::update(Model *model)
{
    ManageTournamentPlayersViewModel *viewModel = (ManageTournamentPlayersViewModel*) model;

    ListModel<TournamentModel*> *tournaments = viewModel->getTournaments();
    ListModel<ChessplayerModel*> *chessplayers = viewModel->getChessplayerList();

    tournamentComboBox->Clear();
    tournamentComboBox->SetValue(L"V\u00E4lj turnering");

    for(unsigned int index = 0; index < tournaments->getSize(); index++)
    {
        TournamentModel *tournament = tournaments->atIndex(index);
        tournamentComboBox->Append(tournament->getId());
        //tournamentComboBox->Append(tournaments[index].getId());
    }

    chessplayerPool->ClearGrid();

    try
    {
        chessplayerPool->setRowCount(chessplayers->getSize());

    }
    catch(ArgumentErrorException &exception)
    {
        wxMessageBox(exception.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    for(unsigned int index = 0; index < chessplayers->getSize(); index++)
    {
        ChessplayerModel *chessplayer = chessplayers->get(index);
        chessplayerPool->SetCellValue(index, 0, std::to_string(chessplayer->getId()));
        chessplayerPool->SetCellValue(index, 1, chessplayer->getName());
    }

    chessplayerPool->Fit();

}

void ManageTournamentPlayersView::setController(Controller *_controller)
{
    ManageTournamentPlayersController *mController = (ManageTournamentPlayersController*) _controller;

    tournamentComboBox->Bind(wxEVT_COMBOBOX, &ManageTournamentPlayersController::changeTournament, mController);

}
