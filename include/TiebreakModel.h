#ifndef TIEBREAKMODEL_H
#define TIEBREAKMODEL_H

#include "ModelViewController.h"

class TiebreakModel : public Model
{
    public:
        TiebreakModel();
        virtual ~TiebreakModel();

    protected:

    private:
        wxString id;
};

#endif // TIEBREAKMODEL_H
