#include "ManageTiebreaksView.h"
#include "ViewModel.h"
#include "ManageTiebreaksController.h"


ManageTiebreaksView::ManageTiebreaksView(wxWindow *p_parent):
    View(p_parent, L"Hantera s\u00E4rskiljning")
{
    tournamentBox = new wxBoxSizer(wxHORIZONTAL);
    tournamentComboBox = new wxComboBox(parent, -1);
    tournamentComboBox->SetMinSize(wxSize(200, 40));
    tournamentBox->Add(tournamentComboBox, 0, wxALL, 10);
    this->Add(tournamentBox, View::MARGIN, wxALL, 0);

    bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    leftSizer = new wxBoxSizer(wxVERTICAL);
    tiebreaksTableHeader = new wxStaticText(parent, -1, L"Tillg\u00E4ngliga s\u00E4rskiljningssystem");
    tiebreaksTableHeader->SetFont(View::H3_FONT);
    tiebreaksTable = new Table(parent, {"Namn"});
    addButton = new wxButton(parent, -1, L"L\u00E4gg till");
    leftSizer->Add(tiebreaksTableHeader, 0, wxALL, 10);
    leftSizer->Add(tiebreaksTable, 0, wxALL, 10);
    leftSizer->Add(addButton, 0, wxLEFT, 10);
    bottomSizer->Add(leftSizer, 0, wxALL, 10);
    tiebreaksTable->Fit();

    rightSizer = new wxBoxSizer(wxVERTICAL);
    selectedTiebreaksHeader = new wxStaticText(parent, -1, L"Valda s\u00E4rskiljningssystem");
    selectedTiebreaksHeader->SetFont(View::H3_FONT);
    selectedTiebreaksList = new wxListBox(parent, -1);
    rightSizer->Add(selectedTiebreaksHeader, 0, wxALL, 10);
    rightSizer->Add(selectedTiebreaksList, 0, wxALL, 10);
    bottomSizer->Add(rightSizer, 0, wxALL, 10);

    this->Add(bottomSizer, View::MARGIN, wxALL, 0);

}

ManageTiebreaksView::~ManageTiebreaksView()
{

}

void ManageTiebreaksView::update(Model *model)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;

    ListModel<TournamentModel*> *tournaments = viewModel->getTournaments();

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

    updateTiebreaks(viewModel->getTiebreaks());

    TournamentModel *tournament = viewModel->getTournament();
    if(tournament != nullptr)
    {
        selectedTiebreaksList->Clear();
        for(unsigned int index = 0; index < tournament->getNumberOfTiebreaks(); index++)
        {
            selectedTiebreaksList->AppendAndEnsureVisible(tournament->getTiebreak(index)->getID());
        }
        std::cout << "S: " << tournament->getNumberOfTiebreaks() << std::endl;
    }
    selectedTiebreaksList->Fit();

}

void ManageTiebreaksView::setController(Controller *_controller)
{
    ManageTiebreaksController *mController = (ManageTiebreaksController*) _controller;
    tournamentComboBox->Bind(wxEVT_COMBOBOX, &ManageTiebreaksController::changeTournament, mController);
    tiebreaksTable->Bind(wxEVT_GRID_SELECT_CELL, &ManageTiebreaksController::selectTiebreakSystem, mController);
    addButton->Bind(wxEVT_BUTTON, &ManageTiebreaksController::addTiebreakSystem, mController);

}

void ManageTiebreaksView::updateTiebreaks(ListModel<TiebreakModel*> *model)
{
    tiebreaksTable->ClearGrid();
    try
    {
        tiebreaksTable->setRowCount(model->getSize());

    }
    catch(ArgumentErrorException &error)
    {
        error.showDialog();
        exit(-1);
    }

    for(unsigned int index = 0; index < model->getSize(); index++)
    {
        TiebreakModel *tiebreakModel = model->get(index);
        tiebreaksTable->SetCellValue(index, 0, tiebreakModel->getID());
    }

    tiebreaksTable->Fit();

}



