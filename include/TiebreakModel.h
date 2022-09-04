#ifndef TIEBREAKMODEL_H
#define TIEBREAKMODEL_H

#include "ModelViewController.h"

class TiebreakModel : public Model
{
    public:
        TiebreakModel(const wxString &pID);
        virtual ~TiebreakModel() {}
        wxString getID() const { return id; }
        bool operator==(const TiebreakModel &tiebreakModel);

    protected:

    private:
        wxString id;
};

#endif // TIEBREAKMODEL_H
