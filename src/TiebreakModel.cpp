#include "TiebreakModel.h"

TiebreakModel::TiebreakModel(const wxString &pID):
    id(pID)
{

}

bool TiebreakModel::operator==(const TiebreakModel &tiebreakModel)
{
    if(id == tiebreakModel.getID())
    {
        return true;
    }

    return false;
}
