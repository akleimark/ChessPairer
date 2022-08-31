#ifndef MANAGETOURNAMENTPLAYERSVIEW_H
#define MANAGETOURNAMENTPLAYERSVIEW_H

#include "ModelViewController.h"

class ManageTournamentPlayersView : public View
{
    public:
        ManageTournamentPlayersView(wxWindow *p_parent);
        virtual ~ManageTournamentPlayersView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);

    protected:

    private:


};


#endif // MANAGETOURNAMENTPLAYERSVIEW_H
