#ifndef MANAGETOURNAMENTPLAYERSVIEW_H
#define MANAGETOURNAMENTPLAYERSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>
#include "Table.h"
#include "ListModel.h"
#include <wx/button.h>

class ManageTournamentPlayersView : public View
{
    public:
        ManageTournamentPlayersView(wxWindow *p_parent);
        virtual ~ManageTournamentPlayersView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);

    protected:

    private:
        wxBoxSizer *tournamentBox;
        wxComboBox *tournamentComboBox;
        wxBoxSizer *bottomSizer;
        wxBoxSizer *leftSizer;
        wxBoxSizer *rightSizer;
        wxBoxSizer *rightButtonPanel;

        Table *chessplayerPool;
        Table *tournamentPlayers;
        wxStaticText *playerPoolHeader;
        wxStaticText *tournamentPlayersHeader;

        wxButton *addButton;
        wxButton *removeButton;
        wxButton *generateButton;

        void updatePlayerPool(ListModel<ChessplayerModel*> *model);
        void updateTournamentPlayers(TournamentModel *model);

};

#endif // MANAGETOURNAMENTPLAYERSVIEW_H
