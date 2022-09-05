#include "ListChessplayersController.h"
#include "Dialog.h"
#include "ListChessplayersView.h"
#include <wx/msgdlg.h>
#include "Exception.h"
#include "ListModel.h"
#include "Defs.h"

ListChessplayersController::ListChessplayersController(Model *_model, View *_view):
    Controller(_model, _view)
{

}

ListChessplayersController::~ListChessplayersController()
{

}

/**
    Det här är en händelsestyrd funktion, som endast körs om användaren har klickat på knappen för att lägga till en ny
    schackspelare. Funktionen visar en dialogruta (model) och tar emot de värden som användaren önskar på schackspelaren som skall
    läggas till.
**/
void ListChessplayersController::addChessplayer(wxCommandEvent &event)
{
    wxString message;
    message << ADD_STRING << " en schackspelare";
    AddChessplayerDialog *dialog = new AddChessplayerDialog(message);

    if (dialog->ShowModal() == wxID_OK )
    {
        model->notifyAllViews();
    }
    dialog->Destroy();
}

void ListChessplayersController::removeChessplayer(wxCommandEvent &event)
{
    ListModel<ChessplayerModel*> *listModel = dynamic_cast<ListModel<ChessplayerModel*>*> (model);
    ListChessplayersView *lView = dynamic_cast<ListChessplayersView*> (view);
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
        ChessplayerModel *chessplayer = listModel->get(rowNumbers[index]);

        try
        {
            if(chessplayer->getNumberOfTournaments() > 0)
            {
                wxString message;
                message << "Schackspelaren med id = ";
                message << chessplayer->getId() << L" g\u00E5r inte att radera, eftersom denne \u00E4r deltagare i "
                    << "en eller flera turneringar.";
                wxMessageBox(message, GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
                continue;
            }
        }
        catch(const DatabaseErrorException &error)
        {
            error.showDialog();
        }

        wxString message;
        message << CONFIRM_MESSAGE << "radera schackspelaren med id = " << chessplayer->getId() << "?";

        int result = wxMessageBox(message,"Svara", wxOK|wxCANCEL | wxICON_INFORMATION);

        if(result == wxOK)
        {
            try
            {
                chessplayer->removeFromDatabase();
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
