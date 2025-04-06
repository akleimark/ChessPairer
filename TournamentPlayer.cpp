#include "TournamentPlayer.h"

TournamentPlayer::TournamentPlayer(const unsigned int &fideId, const QString &name, const unsigned int &rating, const unsigned int &playerNumber):
    Player(fideId, name, rating), playerNumber(playerNumber)
{
    if(!Player(fideId, name, rating).isValid())
    {
        Logger::getInstance()->logError("Data otillåten.");
    }
}


bool TournamentPlayer::operator<(const TournamentPlayer &player) const
{
    return fideId < player.fideId;
}

