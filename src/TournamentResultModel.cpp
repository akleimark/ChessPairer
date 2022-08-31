#include "TournamentResultModel.h"
#include "Defs.h"

TournamentResultModel::TournamentResultModel():
    white(nullptr), black(nullptr), result(NO_RESULT)
{

}

TournamentResultModel::~TournamentResultModel()
{

}

bool TournamentResultModel::validate() const
{
    if(result == "1-0" || result == "0.5-0.5" || result == "0-1" || result == "1-0.5" || result =="0.5-1" || result == "0.5-0" || result == "0-0.5" || result == "0-0")
    {
            return true;
    }

    return false;
}
