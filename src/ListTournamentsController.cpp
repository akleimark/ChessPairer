#include "ListTournamentsController.h"
#include "Dialog.h"
#include "ListChessplayersView.h"
#include <wx/msgdlg.h>
#include "Exception.h"
#include "ListModel.h"
#include "ListTournamentsView.h"

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
    AddTournamentDialog *dialog = new AddTournamentDialog("Add a new tournament");

    if (dialog->ShowModal() == wxID_OK )
    {
        model->notifyAllViews();
    }
    dialog->Destroy();
}

void ListTournamentsController::removeTournament(wxCommandEvent &event)
{
    ListModel<TournamentModel> *listModel = (ListModel<TournamentModel>*) model;
    ListTournamentsView *lView = (ListTournamentsView*) view;
    wxArrayInt rowNumbers = lView->getTable()->GetSelectedRows();
    for(unsigned int index = 0; index < rowNumbers.size(); index++)
    {
        const TournamentModel tournament = listModel->get(rowNumbers[index]);
        tournament.print();

        wxString message;
        message << "Are you sure you want to delete the tournament with the id = " << tournament.getId();

        int result = wxMessageBox(message,"Confirm", wxOK|wxCANCEL | wxICON_INFORMATION);

        if(result == wxOK)
        {
            try
            {
                tournament.removeFromDatabase();
            }
            catch(DatabaseErrorException &exception)
            {
                wxMessageBox(exception.what(),
                 "Error", wxOK | wxICON_INFORMATION);
            }
        }


        listModel->getAll();
        listModel->notifyAllViews();
    }

}
