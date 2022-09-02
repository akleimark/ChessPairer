#ifndef IMPORTCHESSPLAYERSVIEW_H
#define IMPORTCHESSPLAYERSVIEW_H

#include "ModelViewController.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include "Table.h"
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>

class ImportChessplayersView: public View
{
    public:
        ImportChessplayersView(wxWindow *parent);
        virtual ~ImportChessplayersView() {}
        virtual void update(Model*) {}
        virtual void setController(Controller *_controller);

    protected:

    private:

        /// Den här instansen av 'wxBoxSizer' används för att lägga till objekt, som ger användaren möjlighet attvälja filtyp.
        wxBoxSizer *fileTypeBox;
        /// Den här instansen av typen 'wxStaticText' visar en etikett med texten 'File type'.
        wxStaticText *fileTypeLabel;
        /// Den här instansen av 'wxBoxSizer' används för att visa alla knapparna på en rad.
        wxBoxSizer *buttonBox;
        /// Den här variabeln används för att visa en knapp, som ger användaren möjlighet att importera schackspelare.
        wxButton *importButton;
        /// Den här instansen av typen 'wxRadioButton' används för att visa en radioknapp med möjlighet att välja filtypen xml.
        wxRadioButton *xmlButton;
        /// Den här instansen av typen 'wxRadioButton' används för att visa en radioknapp med möjlighet att välja filtypen textfil.
        wxRadioButton *textFileButton;
        /// Den här instansen av 'wxBoxSizer' visar objekt för att användaren skall kunna välja filtyp.
        wxBoxSizer *selectFileBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Select file:'.
        wxStaticText *selectFileLabel;
        /// Den här instansen av 'wxTextCtrl' används för att ge användaren möjlighet att välja sökväg till filen, som skall användas.
        wxTextCtrl *selectFileField;
};

#endif // IMPORTCHESSPLAYERSVIEW_H
