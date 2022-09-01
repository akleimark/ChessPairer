#ifndef MANAGETOURNAMENTPLAYERSVIEW_H
#define MANAGETOURNAMENTPLAYERSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>
#include "Table.h"
#include "ListModel.h"

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
        wxBoxSizer *tableBox;
        Table *chessplayerPool;
        Table *tournamentPlayers;
        void updatePlayerPool(ListModel<ChessplayerModel> *model);


};


#endif // MANAGETOURNAMENTPLAYERSVIEW_H
