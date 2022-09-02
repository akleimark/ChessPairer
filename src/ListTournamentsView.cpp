#include "ListTournamentsView.h"
#include "ListChessplayersView.h"
#include "ChessplayerModel.h"
#include <wx/msgdlg.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include "Dialog.h"
#include "Exception.h"
#include "ListChessplayersController.h"
#include "ListTournamentsController.h"
#include "ListModel.h"
#include "Defs.h"


/**
    Med hjälp av den här konstruktorn skapas en instans av klassen. När den visas ser användaren en rubrik, en tabell med turneringar, samt en
    panel med knappar, där denne exempelvis kan välja att lägga till en ny turnering eller radera en befintlig.
**/
ListTournamentsView::ListTournamentsView(wxWindow *p_parent):
    View(p_parent, "Visa alla turneringar")
{
    std::vector<wxString> columns = {"Id", "Startdatum", "Slutdatum", "Antal ronder", "Lottningssystem"};
    table = new Table(parent, columns);
    this->Add(table, 10, wxALL, View::MARGIN);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(parent, -1, ADD_STRING);
    removeButton = new wxButton(parent, -1, REMOVE_STRING);

    buttonBox->Add(addButton, 0, wxALL, 10);
    buttonBox->Add(removeButton, 0, wxALL, 10);
    this->Add(buttonBox, View::MARGIN, wxALL, 0);
}

ListTournamentsView::~ListTournamentsView()
{

}

/**
    Den här funktionen uppdaterar vyn med hjälp av en instans av en modellklass.
    Tabellen kommer nu att visa den senaste versionen och om en turnering har lagts till eller tagits bort visas alltså
    tabellen enligt de uppdateringarna.
**/
void ListTournamentsView::update(Model *model)
{
    ListModel<TournamentModel*> *m = (ListModel<TournamentModel*>*) model;
    table->ClearGrid();

    try
    {
        table->setRowCount(m->getSize());

    }
    catch(ArgumentErrorException &exception)
    {
        wxMessageBox(exception.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    for(unsigned int index = 0; index < m->getSize(); index++)
    {
        TournamentModel *tournament = m->get(index);
        table->SetCellValue(index, 0, tournament->getId());
        table->SetCellValue(index, 1, tournament->getStartDate().getDateString());
        table->SetCellValue(index, 2, tournament->getEndDate().getDateString());
        table->SetCellValue(index, 3, std::to_string(tournament->getNumberOfRounds()));
        table->SetCellValue(index, 4, tournament->getPairingSystem());
    }

    table->Fit();
}

void ListTournamentsView::setController(Controller *_controller)
{
    ListTournamentsController *controller = (ListTournamentsController*) _controller;

    addButton->Bind(wxEVT_BUTTON, &ListTournamentsController::addTournament, controller);
    removeButton->Bind(wxEVT_BUTTON, &ListTournamentsController::removeTournament, controller);
}



