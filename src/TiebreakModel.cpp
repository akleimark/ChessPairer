#include "TiebreakModel.h"
/**
    En instans av klassen skapas med hjälp av den här konstruktorn.
    @param pID Namnet på särskiljningssystemet.
*/
TiebreakModel::TiebreakModel(const wxString &pID):
    id(pID)
{

}

/**
    Den här överlagrade operatorn jämför två objekt av typen 'TiebreakModel'.
    Om deras respektive namn är lika, returneras 'true', annars 'false'.
*/
bool TiebreakModel::operator==(const TiebreakModel &tiebreakModel)
{
    if(id == tiebreakModel.getID())
    {
        return true;
    }
    return false;
}
