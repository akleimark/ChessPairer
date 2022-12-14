#include "ListTournamentsController.h"
#include "Dialog.h"
#include "ListChessplayersView.h"
#include <wx/msgdlg.h>
#include "Exception.h"
#include "ListModel.h"
#include "ListTournamentsView.h"
#include "Defs.h"

/**
    Den h?r konstruktorn k?r endast superklassens konstruktor
    @param _model En pekare till den modell som anv?nds.
    @param _view En pekare till den vy som anv?nds.
*/
ListTournamentsController::ListTournamentsController(Model *_model, View *_view):
    Controller(_model, _view)
{

}

/**
    Det h?r ?r en h?ndelsestyrd funktion, som endast k?rs om anv?ndaren har klickat p? knappen f?r att l?gga till en ny
    turnering. Funktionen visar en dialogruta (model) och tar emot de v?rden som anv?ndaren ?nskar p? turneringen som skall
    l?ggas till.
**/
void ListTournamentsController::addTournament(wxCommandEvent &event)
{
    wxString title;
    title << ADD_STRING << " en ny turnering";
    AddTournamentDialog *dialog = new AddTournamentDialog(title);

    if (dialog->ShowModal() == wxID_OK )
    {
        model->notifyAllViews();
    }
    dialog->Destroy();
}

/**
    Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren vill ta bort en turnering via vyn.
*/
void ListTournamentsController::removeTournament(wxCommandEvent &event)
{
    ListModel<TournamentModel*> *listModel = dynamic_cast<ListModel<TournamentModel*>*> (model);
    ListTournamentsView *lView = dynamic_cast<ListTournamentsView*> (view);
    wxArrayInt rowNumbers = lView->getTable()->GetSelectedRows();

    if(rowNumbers.size() == 0)
    {
        return;
    }

    for(unsigned int index = 0; index < rowNumbers.size(); index++)
    {
        if(rowNumbers[index] >= listModel->getSize())
        {
            continue;
        }
        TournamentModel *tournament = listModel->get(rowNumbers[index]);
        tournament->print();

        wxString message;
        message << CONFIRM_MESSAGE << "radera turneringen med id = " << tournament->getId() << "?";

        int result = wxMessageBox(message, CONFIRM_LABEL, wxOK|wxCANCEL | wxICON_INFORMATION);

        if(result == wxOK)
        {
            try
            {
                tournament->removeFromDatabase();
            }
            catch(DatabaseErrorException &exception)
            {
                wxMessageBox(exception.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
            }
        }

        listModel->getAll();
        listModel->notifyAllViews();
    }
}
