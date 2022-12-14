#ifndef LISTCHESSPLAYERS_H
#define LISTCHESSPLAYERS_H

#include <wx/sizer.h>
#include "Table.h"
#include "ModelViewController.h"
#include <wx/button.h>

/**
    Den h?r klassen, som ?rver View, anv?nds f?r att visa alla schackspelare som har lagts till i databasen.
    Det finns ?ven m?jlighet att l?gga till en schackspelare, samt att radera en given schackspelare.
**/

class ListChessplayersView : public View
{
    public:
        ListChessplayersView(wxWindow *p_parent);
        /// Alla klassens pekare har en f?r?lder som h?r till wxWidgets. Det inneb?r
        /// att wxWidgets ansvarar f?r att radera dessa objekt.
        virtual ~ListChessplayersView() {}
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);
        /// Den h?r funktionen returnerar tabellen som anv?nds.
        Table* getTable() const { return table; }

    protected:

    private:

        /// Den h?r variabeln anv?nds f?r att visa en tabell med alla tillagda schackspelare.
        Table *table;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa alla knapparna p? en rad.
        wxBoxSizer *buttonBox;
        /// Den h?r variabeln anv?nds f?r att visa en knapp, som ger anv?ndaren m?jlighet att l?gga till fler schackspelare.
        wxButton *addButton;
        /// Den h?r variabeln anv?nds f?r att visa en knapp, som ger anv?ndaren m?jlighet att ta bort en schackspelare.
        wxButton *removeButton;
};

#endif // LISTCHESSPLAYERS_H
