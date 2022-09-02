#ifndef LISTTOURNAMENTSCONTROLLER_H
#define LISTTOURNAMENTSCONTROLLER_H

#include "ModelViewController.h"

class ListTournamentsController : public Controller
{
    public:
        ListTournamentsController(Model *_model, View *_view);
        virtual ~ListTournamentsController();
        void addTournament(wxCommandEvent &event);
        void removeTournament(wxCommandEvent &event);

    protected:

    private:
};

#endif // LISTTOURNAMENTSCONTROLLER_H
