#include "ListTournamentsController.h"
#include "Dialog.h"
#include "ListChessplayersView.h"
#include <wx/msgdlg.h>
#include "Exception.h"

ListTournamentsController::ListTournamentsController(Model *_model, View *_view):
    Controller(_model, _view)
{

}

ListTournamentsController::~ListTournamentsController()
{

}

/**
    Det h�r �r en h�ndelsestyrd funktion, som endast k�rs om anv�ndaren har klickat p� knappen f�r att l�gga till en ny
    turnering. Funktionen visar en dialogruta (model) och tar emot de v�rden som anv�ndaren �nskar p� turneringen som skall
    l�ggas till.
**/
void ListTournamentsController::addTournament(wxCommandEvent &event)
{

}

void ListTournamentsController::removeTournament(wxCommandEvent &event)
{


}