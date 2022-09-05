#ifndef MANAGETOURNAMENTPLAYERSCONTROLLER_H
#define MANAGETOURNAMENTPLAYERSCONTROLLER_H

#include "ModelViewController.h"
#include <wx/grid.h>
/**
    Den här klassen som ärver 'Controller' utgör kontrollklass för att hantera
    turneringsdeltagare i de olika turneringarna.
*/
class ManageTournamentPlayersController : public Controller
{
    public:
        /// I den här konstruktorn körs bara basklassens motsvarande konstruktor.
        ManageTournamentPlayersController(Model *_model, View *_view):
            Controller(_model, _view) {}
        /// I klassen skapas inga objekt med 'new', varpå konstruktorn är tom.
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
