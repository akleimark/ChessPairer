#ifndef TOURNAMENTPLAYER_H
#define TOURNAMENTPLAYER_H

#include <QString>
#include <QDate>
#include "Interfaces.h"
#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"
#include "PlayerListModel.h"
#include <set>


class TournamentPlayer : public Player, public PrintInterface
{
public:
    TournamentPlayer():
        Player(0, "", 0), playerNumber(0)
    {

    }
    TournamentPlayer(const unsigned int &fideId, const QString &name, const unsigned int &rating, const unsigned int &playerNumber);
    bool operator<(const TournamentPlayer &player) const;
    unsigned int getPlayerNumber() const {return playerNumber; }
    void setPlayerNumber(const unsigned int &newPlayerNumber) {playerNumber = newPlayerNumber; }
    virtual void print() const override;
private:
    unsigned int playerNumber;
};




#endif // TOURNAMENTPLAYER_H
