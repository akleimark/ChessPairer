#ifndef PLAYERLISTMODEL_H
#define PLAYERLISTMODEL_H

#include "MVC.h"
#include "SettingsModel.h"
#include <vector>
#include <QString>

/**
 * @class Player
 * @brief Representerar en schackspelare med namn, rating och FIDE-ID.
 */
class Player
{
    public:
    /**
     * @brief Skapar en ny spelare.
     *
     * @param name Spelarens namn.
     * @param rating Spelarens rating.
     * @param fideId Spelarens unika FIDE-ID.
     */
    Player(const QString &name, int rating, int fideId)
        : name(name), rating(rating), fideId(fideId) {}

    /**
     * @brief Hämtar spelarens namn.
     * @return QString Namnet på spelaren.
     */
    QString getName() const { return name; }
    /**
     * @brief Hämtar spelarens rating.
     * @return int Ratingen för spelaren.
     */
    int getRating() const { return rating; }
    /**
     * @brief Hämtar spelarens FIDE-ID.
     * @return int Spelarens FIDE-ID.
     */
    int getFideId() const { return fideId; }

    private:
    QString name; ///< Spelarens namn.
    int rating;   ///< Spelarens rating.
    int fideId;   ///< Spelarens FIDE-ID.
};

/**
 * @class PlayerListModel
 * @brief Hanterar lagring och hantering av spelardata.
 */
class PlayerListModel : public Model
{
    public:
    explicit PlayerListModel(SettingsModel *settingsModel):
            settingsModel(settingsModel) {}
    /**
     * @brief Lägger till en spelare i den interna listan (men inte i databasen).
     *
     * @param player Spelaren som ska läggas till.
     */
    void addPlayerToContainer(const Player &player);
        /**
     * @brief Lägger till en spelare i databasen.
     *
     * @param player Spelaren som ska sparas i databasen.
     */
    void addPlayerToDatabase(const Player &player);
    /**
     * @brief Hämtar en lista över alla spelare.
     *
     * @return En konstant referens till en vektor av spelare.
     */
    const std::vector<Player>& getPlayers() const { return players; }
    const SettingsModel* getSettingsModel() { return settingsModel; }
    virtual void reset() override {players.clear(); }

    private:
        SettingsModel *settingsModel;
        std::vector<Player> players; ///< Intern behållare för spelare.
};

#endif // PLAYERLISTMODEL_H
