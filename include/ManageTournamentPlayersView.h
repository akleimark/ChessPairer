#ifndef MANAGETOURNAMENTPLAYERSVIEW_H
#define MANAGETOURNAMENTPLAYERSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>
#include "Table.h"
#include "ListModel.h"
#include <wx/button.h>

/**
    Den här klassen visar en vy för att hantera deltagare i de
    turneringar som har skapats i programmet och således lagts till i databasen.
*/

class ManageTournamentPlayersView : public View
{
    public:
        ManageTournamentPlayersView(wxWindow *p_parent);
        virtual ~ManageTournamentPlayersView() {}
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);

    protected:

    private:
        /// Den här instansen av 'wxBoxSizer' visar en combobox, som ger användaren möjlighet att
        /// välja bland de skapade turneringarna.
        wxBoxSizer *tournamentBox;
        /// Den här comboboxen används för att visa de turneringar som har skapats i programmet.
        wxComboBox *tournamentComboBox;
        /// Den här instansen av 'wxBoxSizer' används för att visa tabeller med tillgängliga spelare,
        /// nuvarande turneringsspelare, samt knappar för att lägga till och ta bort spelare.
        wxBoxSizer *bottomSizer;
        /// Det här är en sub-vy, där den vänstra delen av 'bottomSizer' visas.
        wxBoxSizer *leftSizer;
        /// Det här är en sub-vy, där den högra delen av 'bottomSizer' visas.
        wxBoxSizer *rightSizer;
        /// I den här panelen visas knapparna för att ta bort en spelare och att generera nya inlottningsnummer.
        wxBoxSizer *rightButtonPanel;
        /// I den här tabellen visas alla tillgängliga schackspelare.
        Table *chessplayerPool;
        /// I den här tabellen visas alla tillagda turneringsspelare.
        Table *tournamentPlayers;
        /// I den här etiketten visas rubriken 'Tillgängliga spelare'.
        wxStaticText *playerPoolHeader;
        /// I den här etiketten visas rubriken 'Turneringsspelare'.
        wxStaticText *tournamentPlayersHeader;
        /// Den här knappen används för att lägga till en vald spelare till turneringen.
        wxButton *addButton;
        /// Den här knappen används för att ta bort en vald spelare ur turneringen.
        wxButton *removeButton;
        /// Den här knappen används för att generera nya inlottningsnummer.
        wxButton *generateButton;

        void updatePlayerPool(ListModel<ChessplayerModel*> *model);
        void updateTournamentPlayers(TournamentModel *model);

};

#endif // MANAGETOURNAMENTPLAYERSVIEW_H
