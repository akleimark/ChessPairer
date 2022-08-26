#ifndef IMPORTCHESSPLAYERSVIEW_H
#define IMPORTCHESSPLAYERSVIEW_H

#include "ModelViewController.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include "Table.h"
#include <wx/button.h>
#include <wx/radiobut.h>

class ImportChessplayersView: public View
{
    public:
        ImportChessplayersView(wxWindow *parent);
        virtual ~ImportChessplayersView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);

    protected:

    private:

        wxBoxSizer *fileTypeBox;
        wxStaticText *fileTypeLabel;
        /// Den här instansen av 'wxBoxSizer' används för att visa alla knapparna på en rad.
        wxBoxSizer *buttonBox;
        /// Den här variabeln används för att visa en knapp, som ger användaren möjlighet att importera schackspelare.
        wxButton *importButton;
        wxRadioButton *xmlButton;
        wxRadioButton *textFileButton;

};


#endif // IMPORTCHESSPLAYERSVIEW_H
