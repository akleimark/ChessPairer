#ifndef LISTCHESSPLAYERSCONTROLLER_H
#define LISTCHESSPLAYERSCONTROLLER_H

#include "ModelViewController.h"

class ListChessplayersController : public Controller
{
    public:
        ListChessplayersController(Model *_model, View *_view);
        virtual ~ListChessplayersController();
        void addChessplayer(wxCommandEvent &event);
        void removeChessplayer(wxCommandEvent &event);

    protected:

    private:
};

#endif // LISTCHESSPLAYERSCONTROLLER_H
