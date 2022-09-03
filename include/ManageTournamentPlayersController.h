#ifndef MANAGETOURNAMENTPLAYERSCONTROLLER_H
#define MANAGETOURNAMENTPLAYERSCONTROLLER_H

#include "ModelViewController.h"
#include <wx/grid.h>

class ManageTournamentPlayersController : public Controller
{
    public:
        ManageTournamentPlayersController(Model *_model, View *_view):
            Controller(_model, _view) {}
        virtual ~ManageTournamentPlayersController() {}
        void changeTournament(wxCommandEvent &event);
        void selectPlayer(wxGridEvent &event);
        void selectTournamentPlayer(wxGridEvent &event);
        void addPlayer(wxCommandEvent &event);
        void removePlayer(wxCommandEvent &event);
        void generatePlayerNumbers(wxCommandEvent &event);

    protected:

    private:

};

#endif // MANAGETOURNAMENTPLAYERSCONTROLLER_H
