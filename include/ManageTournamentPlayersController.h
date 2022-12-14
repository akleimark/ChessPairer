#ifndef MANAGETOURNAMENTPLAYERSCONTROLLER_H
#define MANAGETOURNAMENTPLAYERSCONTROLLER_H

#include "ModelViewController.h"
#include <wx/grid.h>
/**
    Den h?r klassen som ?rver 'Controller' utg?r kontrollklass f?r att hantera
    turneringsdeltagare i de olika turneringarna.
*/
class ManageTournamentPlayersController : public Controller
{
    public:
        /// I den h?r konstruktorn k?rs bara basklassens motsvarande konstruktor.
        ManageTournamentPlayersController(Model *_model, View *_view):
            Controller(_model, _view) {}
        /// I klassen skapas inga objekt med 'new', varp? konstruktorn ?r tom.
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
