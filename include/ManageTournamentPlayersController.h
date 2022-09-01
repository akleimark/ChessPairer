#ifndef MANAGETOURNAMENTPLAYERSCONTROLLER_H
#define MANAGETOURNAMENTPLAYERSCONTROLLER_H

#include "ModelViewController.h"

class ManageTournamentPlayersController : public Controller
{
    public:
        ManageTournamentPlayersController(Model *_model, View *_view):
            Controller(_model, _view) {}
        virtual ~ManageTournamentPlayersController() {}
        void changeTournament(wxCommandEvent &event);

    protected:

    private:
};

#endif // MANAGETOURNAMENTPLAYERSCONTROLLER_H
