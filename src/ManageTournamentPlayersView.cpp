#include "ManageTournamentPlayersView.h"
#include "ViewModel.h"
#include "ManageTournamentPlayersController.h"
#include "Defs.h"
#include <wx/msgdlg.h>

/**
    I konstruktorn skapas alla objekt och läggs in i vyn.
*/
ManageTournamentPlayersView::ManageTournamentPlayersView(wxWindow *p_parent):
    View(p_parent, "Hantera turneringsspelare")
{
    tournamentBox = new wxBoxSizer(wxHORIZONTAL);
    tournamentComboBox = new wxComboBox(parent, -1);
    tournamentComboBox->SetMinSize(wxSize(200, 40));
    tournamentBox->Add(tournamentComboBox, 0, wxALL, 10);
    this->Add(tournamentBox, 1, wxALL, 0);

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
    tournamentPlayers = new Table(parent, {"Id", "Namn", "Spelarnummer"});
    rightButtonPanel = new wxBoxSizer(wxHORIZONTAL);
    removeButton = new wxButton(parent, -1, "Ta bort");
    generateButton = new wxButton(parent, -1, "Generera");
    rightButtonPanel->Add(removeButton, 0, wxALL, 0);
    rightButtonPanel->Add(generateButton, 0, wxLEFT, 10);

    rightSizer->Add(tournamentPlayersHeader, 0, wxALL | wxEXPAND, 10);
    rightSizer->Add(tournamentPlayers, 0, wxALL, 10);
    rightSizer->Add(rightButtonPanel, 0, wxALL, 10);
    bottomSizer->Add(rightSizer, 1, wxALL, 10);

    this->Add(bottomSizer, 4, wxALL | wxEXPAND, 0);
}

void ManageTournamentPlayersView::update(Model *model)
{
    ManageTournamentPlayersViewModel *viewModel = dynamic_cast<ManageTournamentPlayersViewModel*> (model);

    ListModel<TournamentModel*> *tournaments = viewModel->getTournaments();
    ListModel<ChessplayerModel*> *chessplayers = viewModel->getChessplayerList();

    if(tournamentComboBox->GetCount() == 0)
    {
        for(unsigned int index = 0; index < tournaments->getSize(); index++)
        {
            TournamentModel *tournament = tournaments->atIndex(index);
            {
                tournamentComboBox->Append(tournament->getId());
            }
        }
    }

    updatePlayerPool(chessplayers);
    updateTournamentPlayers(viewModel->getTournamentModel());
    addButton->Enable(chessplayers->getSize() != 0 && viewModel->getTournamentModel() != nullptr);
    this->Layout();
}

void ManageTournamentPlayersView::setController(Controller *_controller)
{
    ManageTournamentPlayersController *mController = dynamic_cast<ManageTournamentPlayersController*> (_controller);

    tournamentComboBox->Bind(wxEVT_COMBOBOX, &ManageTournamentPlayersController::changeTournament, mController);
    chessplayerPool->Bind(wxEVT_GRID_SELECT_CELL, &ManageTournamentPlayersController::selectPlayer, mController);
    tournamentPlayers->Bind(wxEVT_GRID_SELECT_CELL, &ManageTournamentPlayersController::selectTournamentPlayer, mController);
    removeButton->Bind(wxEVT_BUTTON, &ManageTournamentPlayersController::removePlayer, mController);
    addButton->Bind(wxEVT_BUTTON, &ManageTournamentPlayersController::addPlayer, mController);
    generateButton->Bind(wxEVT_BUTTON, &ManageTournamentPlayersController::generatePlayerNumbers, mController);
}

/**
    Den här funktionen uppdaterar tabellen med turneringsspelarna.
*/
void ManageTournamentPlayersView::updateTournamentPlayers(TournamentModel *model)
{
    if(model == nullptr)
    {
        return;
    }

    tournamentPlayers->ClearGrid();
    try
    {
        tournamentPlayers->setRowCount(model->getNumberOfPlayers());

    }
    catch(ArgumentErrorException &exception)
    {
        wxMessageBox(exception.what(),
                     GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    for(unsigned int index = 0; index < model->getNumberOfPlayers(); index++)
    {
        TournamentPlayerModel *player = model->atIndex(index);
        player->print();
        tournamentPlayers->SetCellValue(index, 0, std::to_string(player->getChessplayerID()));
        ChessplayerModel *chessplayer = ChessplayerModel::findById(player->getChessplayerID());
        tournamentPlayers->SetCellValue(index, 1, chessplayer->getName());
        tournamentPlayers->SetCellValue(index, 2, std::to_string(player->getPlayerNumber()));
    }
    tournamentPlayers->Fit();
}

/**
    Den här funktionen uppdaterar tabellen med tillgängliga spelare att välja bland.
*/
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
