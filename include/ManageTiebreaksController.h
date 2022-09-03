#ifndef MANAGETIEBREAKSCONTROLLER_H
#define MANAGETIEBREAKSCONTROLLER_H

#include "ModelViewController.h"

class ManageTiebreaksController : public Controller
{
    public:
        ManageTiebreaksController(Model *_model, View *_view):
            Controller(_model, _view) {}
        virtual ~ManageTiebreaksController();

    protected:

    private:
};

#endif // MANAGETIEBREAKSCONTROLLER_H
