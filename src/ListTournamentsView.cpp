#include "ListTournamentsView.h"
#include "ListChessplayersView.h"
#include "ChessplayerModel.h"
#include <wx/msgdlg.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include "Dialog.h"
#include "Exception.h"
#include "ListChessplayersController.h"

/**
    Med hj�lp av den h�r konstruktorn skapas en instans av klassen. N�r den visas ser anv�ndaren en rubrik, en tabell med turneringar, samt en
    panel med knappar, d�r denne exempelvis kan v�lja att l�gga till en ny turnering eller radera en befintlig.
**/
ListTournamentsView::ListTournamentsView(wxWindow *p_parent):
    View(p_parent, "List tournaments")
{
    std::vector<wxString> columns = {"Id", "Number of players", "Pairing system"};
    table = new Table(parent, columns);
    this->Add(table, 10, wxALL, View::MARGIN);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(parent, -1, "Add");
    removeButton = new wxButton(parent, -1, "Remove");

    buttonBox->Add(addButton, 0, wxALL, 10);
    buttonBox->Add(removeButton, 0, wxALL, 10);
    this->Add(buttonBox, View::MARGIN, wxALL, 0);
}

ListTournamentsView::~ListTournamentsView()
{

}

/**
    Den h�r funktionen uppdaterar vyn med hj�lp av en instans av en modellklass.
    Tabellen kommer nu att visa den senaste versionen och om en turnering har lagts till eller tagits bort visas allts�
    tabellen enligt de uppdateringarna.
**/
void ListTournamentsView::update(Model *model)
{


}

void ListTournamentsView::setController(Controller *_controller)
{

}


