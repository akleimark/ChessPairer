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
    Det här är en händelsestyrd funktion, som endast körs om användaren har klickat på knappen för att lägga till en ny
    turnering. Funktionen visar en dialogruta (model) och tar emot de värden som användaren önskar på turneringen som skall
    läggas till.
**/
void ListTournamentsController::addTournament(wxCommandEvent &event)
{

}

void ListTournamentsController::removeTournament(wxCommandEvent &event)
{


}
