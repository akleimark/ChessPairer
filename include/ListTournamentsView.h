#ifndef LISTTOURNAMENTSVIEW_H
#define LISTTOURNAMENTSVIEW_H

#include <wx/sizer.h>
#include "Table.h"
#include "ModelViewController.h"
#include <wx/button.h>

/**
    Den här klassen, som ärver View, används för att visa alla schackspelare som har lagts till i databasen.
    Det finns även möjlighet att lägga till en schackspelare, samt att radera en given schackspelare.
**/

class ListTournamentsView : public View
{
    public:
        ListTournamentsView(wxWindow *p_parent);
        virtual ~ListTournamentsView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);
    protected:

    private:

        /// Den här variabeln används för att visa en tabell med alla tillagda turneringar.
        Table *table;
        /// Den här instansen av 'wxBoxSizer' används för att visa alla knapparna på en rad.
        wxBoxSizer *buttonBox;
        /// Den här variabeln används för att visa en knapp, som ger användaren möjlighet att lägga till fler turneringar.
        wxButton *addButton;
        /// Den här variabeln används för att visa en knapp, som ger användaren möjlighet att ta bort en turnering.
        wxButton *removeButton;
};


#endif // LISTTOURNAMENTSVIEW_H
