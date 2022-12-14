#include "ManageTiebreaksView.h"
#include "ViewModel.h"
#include "ManageTiebreaksController.h"
#include "Defs.h"

/**
    I den h?r konstruktorn skapas alla objekt, som ?r specifika f?r den h?r underklassen.
    I konstruktorn st?lls ocks? storleksf?rh?llandena in. Vissa av objekten skall vara sm?, medan
    andra beh?ver vara litet st?rre. Det ?r d?rf?r viktigt att st?lla in dessa korrekt.
*/
ManageTiebreaksView::ManageTiebreaksView(wxWindow *p_parent):
    View(p_parent, L"Hantera s\u00E4rskiljning")
{
    tournamentBox = new wxBoxSizer(wxHORIZONTAL);
    tournamentComboBox = new wxComboBox(parent, -1);
    tournamentComboBox->SetMinSize(wxSize(COMBOBOX_MIN_WIDTH, COMBOBOX_MIN_HEIGHT));
    tournamentBox->Add(tournamentComboBox, 0, wxALL, 10);
    this->Add(tournamentBox, 1, wxALL, 0);

    bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    leftSizer = new wxBoxSizer(wxVERTICAL);
    tiebreaksTableHeader = new wxStaticText(parent, -1, L"Tillg\u00E4ngliga s\u00E4rskiljningssystem");
    tiebreaksTableHeader->SetFont(View::H3_FONT);
    tiebreaksTable = new Table(parent, {"Namn"});
    addButton = new wxButton(parent, -1, L"L\u00E4gg till");
    leftSizer->Add(tiebreaksTableHeader, 0, wxALL, 10);
    leftSizer->Add(tiebreaksTable, 4, wxALL, 10);
    leftSizer->Add(addButton, 1, wxLEFT, 10);
    bottomSizer->Add(leftSizer, 0, wxALL, 10);
    tiebreaksTable->Fit();

    rightSizer = new wxBoxSizer(wxVERTICAL);
    selectedTiebreaksHeader = new wxStaticText(parent, -1, L"Valda s\u00E4rskiljningssystem");
    selectedTiebreaksHeader->SetFont(View::H3_FONT);
    selectedTiebreaksTable = new Table(parent, {"Namn"});
    removeButton = new wxButton(parent, -1, "Ta bort");
    rightSizer->Add(selectedTiebreaksHeader, 0, wxALL, 10);
    rightSizer->Add(selectedTiebreaksTable, 4, wxALL | wxEXPAND, 10);
    rightSizer->Add(removeButton, 0, wxLEFT, 1);
    bottomSizer->Add(rightSizer, 0, wxALL, 10);

    this->Add(bottomSizer, 3, wxALL, 0);
}

/**
    I den h?r funktionen uppdateras vyn. Det ?r modellen som anv?nder sig av den h?r funktionen.
    Funktionen anv?nder sig av tv? separata privata funktioner f?r att uppdatera de tv? tabeller som klassen
    anv?nder sig av. Det ?r viktigt att avsluta med kodsnutten: 'this->Layout()', eftersom tabellerna
    dynamiskt l?gger till och drar av objekt, utifr?n hur m?nga tillg?ngliga-, respektive valda s?rkiljningssystem som
    finns till hands.
*/
void ManageTiebreaksView::update(Model *model)
{
    ManageTiebreaksViewModel *viewModel = dynamic_cast<ManageTiebreaksViewModel*> (model);
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

    updateAvailableTiebreaks(viewModel->getTiebreaks());
    updateSelectedTiebreaks(viewModel->getTournament());

    this->Layout();
}

/**
    Den h?r funktionen l?gger till alla h?ndelsestyrda objekt till den kontrollklass, som vyn anv?nder sig av.
*/
void ManageTiebreaksView::setController(Controller *_controller)
{
    ManageTiebreaksController *mController = dynamic_cast<ManageTiebreaksController*> (_controller);
    tournamentComboBox->Bind(wxEVT_COMBOBOX, &ManageTiebreaksController::changeTournament, mController);
    tiebreaksTable->Bind(wxEVT_GRID_SELECT_CELL, &ManageTiebreaksController::selectTiebreakToAdd, mController);
    selectedTiebreaksTable->Bind(wxEVT_GRID_SELECT_CELL, &ManageTiebreaksController::selectTiebreakToRemove, mController);
    addButton->Bind(wxEVT_BUTTON, &ManageTiebreaksController::addTiebreakSystem, mController);
    removeButton->Bind(wxEVT_BUTTON, &ManageTiebreaksController::removeTiebreakSystem, mController);
}

void ManageTiebreaksView::updateAvailableTiebreaks(ListModel<TiebreakModel*> *model)
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

void ManageTiebreaksView::updateSelectedTiebreaks(TournamentModel *tournament)
{
    if(tournament != nullptr)
    {
        selectedTiebreaksTable->ClearGrid();
        selectedTiebreaksTable->setRowCount(tournament->getNumberOfTiebreaks());
        for(unsigned int index = 0; index < tournament->getNumberOfTiebreaks(); index++)
        {
            selectedTiebreaksTable->SetCellValue(index, 0, tournament->getTiebreak(index)->getID());
        }
    }
    selectedTiebreaksTable->Fit();
    selectedTiebreaksTable->SetMinSize(wxSize(tiebreaksTable->GetSize()));

}

