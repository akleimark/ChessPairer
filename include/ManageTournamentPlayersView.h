#ifndef MANAGETOURNAMENTPLAYERSVIEW_H
#define MANAGETOURNAMENTPLAYERSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>
#include "Table.h"
#include "ListModel.h"
#include <wx/button.h>

/**
    Den h?r klassen visar en vy f?r att hantera deltagare i de
    turneringar som har skapats i programmet och s?ledes lagts till i databasen.
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
        /// Den h?r instansen av 'wxBoxSizer' visar en combobox, som ger anv?ndaren m?jlighet att
        /// v?lja bland de skapade turneringarna.
        wxBoxSizer *tournamentBox;
        /// Den h?r comboboxen anv?nds f?r att visa de turneringar som har skapats i programmet.
        wxComboBox *tournamentComboBox;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa tabeller med tillg?ngliga spelare,
        /// nuvarande turneringsspelare, samt knappar f?r att l?gga till och ta bort spelare.
        wxBoxSizer *bottomSizer;
        /// Det h?r ?r en sub-vy, d?r den v?nstra delen av 'bottomSizer' visas.
        wxBoxSizer *leftSizer;
        /// Det h?r ?r en sub-vy, d?r den h?gra delen av 'bottomSizer' visas.
        wxBoxSizer *rightSizer;
        /// I den h?r panelen visas knapparna f?r att ta bort en spelare och att generera nya inlottningsnummer.
        wxBoxSizer *rightButtonPanel;
        /// I den h?r tabellen visas alla tillg?ngliga schackspelare.
        Table *chessplayerPool;
        /// I den h?r tabellen visas alla tillagda turneringsspelare.
        Table *tournamentPlayers;
        /// I den h?r etiketten visas rubriken 'Tillg?ngliga spelare'.
        wxStaticText *playerPoolHeader;
        /// I den h?r etiketten visas rubriken 'Turneringsspelare'.
        wxStaticText *tournamentPlayersHeader;
        /// Den h?r knappen anv?nds f?r att l?gga till en vald spelare till turneringen.
        wxButton *addButton;
        /// Den h?r knappen anv?nds f?r att ta bort en vald spelare ur turneringen.
        wxButton *removeButton;
        /// Den h?r knappen anv?nds f?r att generera nya inlottningsnummer.
        wxButton *generateButton;

        void updatePlayerPool(ListModel<ChessplayerModel*> *model);
        void updateTournamentPlayers(TournamentModel *model);

};

#endif // MANAGETOURNAMENTPLAYERSVIEW_H
