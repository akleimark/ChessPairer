#ifndef LISTTOURNAMENTSVIEW_H
#define LISTTOURNAMENTSVIEW_H

#include <wx/sizer.h>
#include "Table.h"
#include "ModelViewController.h"
#include <wx/button.h>

/**
    Den h?r klassen, som ?rver View, anv?nds f?r att visa alla schackspelare som har lagts till i databasen.
    Det finns ?ven m?jlighet att l?gga till en schackspelare, samt att radera en given schackspelare.
**/

class ListTournamentsView : public View
{
    public:
        ListTournamentsView(wxWindow *p_parent);
        virtual ~ListTournamentsView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);
        Table* getTable() const { return table; }
    protected:

    private:

        /// Den h?r variabeln anv?nds f?r att visa en tabell med alla tillagda turneringar.
        Table *table;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa alla knapparna p? en rad.
        wxBoxSizer *buttonBox;
        /// Den h?r variabeln anv?nds f?r att visa en knapp, som ger anv?ndaren m?jlighet att l?gga till fler turneringar.
        wxButton *addButton;
        /// Den h?r variabeln anv?nds f?r att visa en knapp, som ger anv?ndaren m?jlighet att ta bort en turnering.
        wxButton *removeButton;
};

#endif // LISTTOURNAMENTSVIEW_H
