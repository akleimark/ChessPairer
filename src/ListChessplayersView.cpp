#include "ListChessplayersView.h"
#include "ChessplayerModel.h"
#include <wx/msgdlg.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include "Dialog.h"
#include "Exception.h"
#include "ListChessplayersController.h"

/**
    Med hjälp av den här konstruktorn skapas en instans av klassen. När den visas ser användaren en rubrik, en tabell med schackspelare, samt en
    panel med knappar, där denne exempelvis kan välja att lägga till en ny schackspelare eller radera en befintlig.
**/
ListChessplayersView::ListChessplayersView(wxWindow *p_parent):
    View(p_parent, "List chessplayers"), rowNumber(-1)
{
    std::vector<wxString> columns = {"Id", "Name", "Birthdate", "Club"};
    table = new Table(parent, columns);
    this->Add(table, 10, wxALL, View::MARGIN);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(parent, -1, "Add");
    removeButton = new wxButton(parent, -1, "Remove");

    buttonBox->Add(addButton, -1, wxALL, 10);
    buttonBox->Add(removeButton, -1, wxALL, 10);
    this->Add(buttonBox, View::MARGIN, wxALL, 0);

}

ListChessplayersView::~ListChessplayersView()
{

}

/**
    Den här funktionen uppdaterar vyn med hjälp av en instans av en modellklass.
    Tabellen kommer nu att visa den senaste versionen och om en schackspelare har lagts till eller tagits bort visas alltså
    tabellen enligt de uppdateringarna.
**/
void ListChessplayersView::update(Model *model)
{
    ChessplayerListModel *m = (ChessplayerListModel*) model;
    table->ClearGrid();

    try
    {
        table->setRowCount(m->getSize());
    }
    catch(RangeErrorException &exception)
    {
        wxMessageBox(exception.what(),
                 "Error", wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    for(unsigned int index = 0; index < m->getSize(); index++)
    {
        ChessplayerModel chessplayer = m->get(index);
        table->SetCellValue(index, 0, std::to_string(chessplayer.getId()));
        table->SetCellValue(index, 1, chessplayer.getName());
        table->SetCellValue(index, 2, chessplayer.getBirthDate());
        table->SetCellValue(index, 3, chessplayer.getChessclub());
    }

    table->Fit();

}

void ListChessplayersView::setController(Controller *_controller)
{
    ListChessplayersController *controller = (ListChessplayersController*) _controller;

    addButton->Bind(wxEVT_BUTTON, &ListChessplayersController::addChessplayer, controller);
    removeButton->Bind(wxEVT_BUTTON, &ListChessplayersController::removeChessplayer, controller);
}

