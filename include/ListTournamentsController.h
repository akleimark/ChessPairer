#ifndef LISTTOURNAMENTSCONTROLLER_H
#define LISTTOURNAMENTSCONTROLLER_H

#include "ModelViewController.h"

/**
    Den här klassen ärver klassen 'Controller'. Den ingår i MVC-strukturen.
    Klassen använder sig av en vy (ListTournamentsView) och en modell(ManageTournamentPlayersViewModel).
*/

class ListTournamentsController : public Controller
{
    public:
        ListTournamentsController(Model *_model, View *_view);
        /// Klassen skapar inga egna objekt med 'new', varpå destruktorn är tom.
        virtual ~ListTournamentsController() {}
        void addTournament(wxCommandEvent &event);
        void removeTournament(wxCommandEvent &event);

    protected:

    private:
};

#endif // LISTTOURNAMENTSCONTROLLER_H
