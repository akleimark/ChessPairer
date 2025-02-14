#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "MVC.h"
#include <vector>
#include <QString>

class Player
{
    public:
        Player(const QString &name, int rating, int fideId)
            : name(name), rating(rating), fideId(fideId) {}

        QString getName() const { return name; }
        int getRating() const { return rating; }
        int getFideId() const { return fideId; }

    private:
        QString name;
        int rating;
        int fideId;
};

class PlayerModel : public Model
{
    public:
        void addPlayer(const Player &player)
        {
            players.push_back(player);
            notifyAllViews();
        }

        const std::vector<Player>& getPlayers() const { return players; }

        private:
            std::vector<Player> players;
};

#endif // PLAYERMODEL_H
