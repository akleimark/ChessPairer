#ifndef LISTCHESSPLAYERS_H
#define LISTCHESSPLAYERS_H

#include <wx/sizer.h>
#include "Table.h"
#include "ModelViewController.h"
#include <wx/button.h>

/**
    Den här klassen, som ärver View, används för att visa alla schackspelare som har lagts till i databasen.
    Det finns även möjlighet att lägga till en schackspelare, samt att radera en given schackspelare.
**/

class ListChessplayersView : public View
{
    public:
        ListChessplayersView(wxWindow *p_parent);
        virtual ~ListChessplayersView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);
        Table* getTable() const { return table; }

    protected:

    private:

        /// Den här variabeln används för att visa en tabell med alla tillagda schackspelare.
        Table *table;
        /// Den här instansen av 'wxBoxSizer' används för att visa alla knapparna på en rad.
        wxBoxSizer *buttonBox;
        /// Den här variabeln används för att visa en knapp, som ger användaren möjlighet att lägga till fler schackspelare.
        wxButton *addButton;
        /// Den här variabeln används för att visa en knapp, som ger användaren möjlighet att ta bort en schackspelare.
        wxButton *removeButton;
        int rowNumber;



};

#endif // LISTCHESSPLAYERS_H
