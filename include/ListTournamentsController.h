#ifndef LISTTOURNAMENTSCONTROLLER_H
#define LISTTOURNAMENTSCONTROLLER_H

#include "ModelViewController.h"

/**
    Den h?r klassen ?rver klassen 'Controller'. Den ing?r i MVC-strukturen.
    Klassen anv?nder sig av en vy (ListTournamentsView) och en modell(ManageTournamentPlayersViewModel).
*/

class ListTournamentsController : public Controller
{
    public:
        ListTournamentsController(Model *_model, View *_view);
        /// Klassen skapar inga egna objekt med 'new', varp? destruktorn ?r tom.
        virtual ~ListTournamentsController() {}
        void addTournament(wxCommandEvent &event);
        void removeTournament(wxCommandEvent &event);

    protected:

    private:
};

#endif // LISTTOURNAMENTSCONTROLLER_H
