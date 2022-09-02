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

    bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    leftSizer = new wxBoxSizer(wxVERTICAL);
    playerPoolHeader = new wxStaticText(parent, -1, L"Tillg\u00E4ngliga spelare");
    playerPoolHeader->SetFont(View::H3_FONT);
    chessplayerPool = new Table(parent, {"Id", "Namn"});
    addButton = new wxButton(parent, -1, L"L\u00E4gg till");
    leftSizer->Add(playerPoolHeader, 0, wxALL, 10);
    leftSizer->Add(chessplayerPool, 0, wxALL, 10);
    leftSizer->Add(addButton, 0, wxALL, 10);
    bottomSizer->Add(leftSizer, 1, wxALL, 10);

    rightSizer = new wxBoxSizer(wxVERTICAL);
    tournamentPlayersHeader = new wxStaticText(parent, -1, "Turneringsspelare");
    tournamentPlayersHeader->SetFont(View::H3_FONT);
    tournamentPlayers = new Table(parent, {"Id", "Namn"});
    rightSizer->Add(tournamentPlayersHeader, 0, wxALL | wxEXPAND, 10);
    rightSizer->Add(tournamentPlayers, 0, wxALL, 10);
    bottomSizer->Add(rightSizer, 1, wxALL, 10);

    this->Add(bottomSizer, View::MARGIN, wxALL | wxEXPAND, 0);

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
    }

    updatePlayerPool(chessplayers);
    addButton->Enable(chessplayers->getSize() != 0 && viewModel->getTournamentModel() != nullptr);

}

void ManageTournamentPlayersView::setController(Controller *_controller)
{
    ManageTournamentPlayersController *mController = (ManageTournamentPlayersController*) _controller;

    tournamentComboBox->Bind(wxEVT_COMBOBOX, &ManageTournamentPlayersController::changeTournament, mController);
    chessplayerPool->Bind(wxEVT_GRID_SELECT_CELL, &ManageTournamentPlayersController::selectPlayer, mController);
    addButton->Bind(wxEVT_BUTTON, &ManageTournamentPlayersController::addPlayer, mController);
}

void ManageTournamentPlayersView::updatePlayerPool(ListModel<ChessplayerModel*> *model)
{
    chessplayerPool->ClearGrid();

    try
    {
        chessplayerPool->setRowCount(model->getSize());

    }
    catch(ArgumentErrorException &exception)
    {
        wxMessageBox(exception.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    for(unsigned int index = 0; index < model->getSize(); index++)
    {
        ChessplayerModel *chessplayer = model->get(index);
        chessplayerPool->SetCellValue(index, 0, std::to_string(chessplayer->getId()));
        chessplayerPool->SetCellValue(index, 1, chessplayer->getName());
    }

    chessplayerPool->Fit();

}
