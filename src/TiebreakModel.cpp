#include "TiebreakModel.h"
/**
    En instans av klassen skapas med hj?lp av den h?r konstruktorn.
    @param pID Namnet p? s?rskiljningssystemet.
*/
TiebreakModel::TiebreakModel(const wxString &pID):
    id(pID)
{

}

/**
    Den h?r ?verlagrade operatorn j?mf?r tv? objekt av typen 'TiebreakModel'.
    Om deras respektive namn ?r lika, returneras 'true', annars 'false'.
*/
bool TiebreakModel::operator==(const TiebreakModel &tiebreakModel)
{
    if(id == tiebreakModel.getID())
    {
        return true;
    }
    return false;
}
