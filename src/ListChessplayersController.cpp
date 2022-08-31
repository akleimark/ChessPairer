#include "ListChessplayersController.h"
#include "Dialog.h"
#include "ListChessplayersView.h"
#include <wx/msgdlg.h>
#include "Exception.h"
#include "ListModel.h"

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
    AddChessplayerDialog *dialog = new AddChessplayerDialog(L"L\u00E4gg till en schackspelare");

    if (dialog->ShowModal() == wxID_OK )
    {
        model->notifyAllViews();
    }
    dialog->Destroy();

}

void ListChessplayersController::removeChessplayer(wxCommandEvent &event)
{
    ListModel<ChessplayerModel> *listModel = (ListModel<ChessplayerModel>*) model;
    ListChessplayersView *lView = (ListChessplayersView*) view;
    wxArrayInt rowNumbers = lView->getTable()->GetSelectedRows();
    for(unsigned int index = 0; index < rowNumbers.size(); index++)
    {
        const ChessplayerModel chessplayer = listModel->get(rowNumbers[index]);
        chessplayer.print();

        wxString message;
        message << L"\u00C5r du s\u00E4ker p\u00E5 att du vill radera schackspelaren med id = " << chessplayer.getId() << "?";

        int result = wxMessageBox(message,"Svara", wxOK|wxCANCEL | wxICON_INFORMATION);

        if(result == wxOK)
        {
            try
            {
                chessplayer.removeFromDatabase();
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
