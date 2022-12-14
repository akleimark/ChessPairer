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

        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att l?gga till objekt, som ger anv?ndaren m?jlighet attv?lja filtyp.
        wxBoxSizer *fileTypeBox;
        /// Den h?r instansen av typen 'wxStaticText' visar en etikett med texten 'File type'.
        wxStaticText *fileTypeLabel;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa alla knapparna p? en rad.
        wxBoxSizer *buttonBox;
        /// Den h?r variabeln anv?nds f?r att visa en knapp, som ger anv?ndaren m?jlighet att importera schackspelare.
        wxButton *importButton;
        /// Den h?r instansen av typen 'wxRadioButton' anv?nds f?r att visa en radioknapp med m?jlighet att v?lja filtypen xml.
        wxRadioButton *xmlButton;
        /// Den h?r instansen av typen 'wxRadioButton' anv?nds f?r att visa en radioknapp med m?jlighet att v?lja filtypen textfil.
        wxRadioButton *textFileButton;
        /// Den h?r instansen av 'wxBoxSizer' visar objekt f?r att anv?ndaren skall kunna v?lja filtyp.
        wxBoxSizer *selectFileBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Select file:'.
        wxStaticText *selectFileLabel;
        /// Den h?r instansen av 'wxTextCtrl' anv?nds f?r att ge anv?ndaren m?jlighet att v?lja s?kv?g till filen, som skall anv?ndas.
        wxTextCtrl *selectFileField;
};

#endif // IMPORTCHESSPLAYERSVIEW_H
