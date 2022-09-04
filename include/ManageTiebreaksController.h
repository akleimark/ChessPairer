#ifndef MANAGETIEBREAKSCONTROLLER_H
#define MANAGETIEBREAKSCONTROLLER_H

#include "ModelViewController.h"
#include <wx/grid.h>


class ManageTiebreaksController : public Controller
{
    public:
        ManageTiebreaksController(Model *_model, View *_view):
            Controller(_model, _view) {}
        virtual ~ManageTiebreaksController();
        void changeTournament(wxCommandEvent &event);
        void addTiebreakSystem(wxCommandEvent &event);
        void removeTiebreakSystem(wxCommandEvent &event);
        void selectTiebreakToAdd(wxGridEvent &event);
        void selectTiebreakToRemove(wxGridEvent &event);

    protected:

    private:
};

#endif // MANAGETIEBREAKSCONTROLLER_H
