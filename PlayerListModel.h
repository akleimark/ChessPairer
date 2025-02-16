#ifndef PLAYERLISTMODEL_H
#define PLAYERLISTMODEL_H

#include "MVC.h"
#include "SettingsModel.h"
#include <vector>
#include <QString>

/**
 * @class Player
 * @brief Representerar en schackspelare med namn, rating och FIDE-ID.
 *
 * Klassen Player används för att lagra information om en schackspelare, inklusive spelarens namn,
 * rating och unika FIDE-ID. Den tillhandahåller getter- och setter-metoder för dessa attribut.
 */
class Player
{
public:
    /**
     * @brief Skapar en ny spelare.
     *
     * Konstruktorn skapar en ny instans av Player med angivet namn, rating och FIDE-ID.
     *
     * @param name Spelarens namn.
     * @param rating Spelarens rating.
     * @param fideId Spelarens unika FIDE-ID.
     */
    Player(const QString &name, int rating, int fideId)
        : name(name), rating(rating), fideId(fideId) {}

    /**
     * @brief Hämtar spelarens namn.
     *
     * Returnerar spelarens namn.
     *
     * @return QString Namnet på spelaren.
     */
    QString getName() const { return name; }

    /**
     * @brief Hämtar spelarens rating.
     *
     * Returnerar spelarens rating.
     *
     * @return unsigned int Ratingen för spelaren.
     */
    unsigned int getRating() const { return rating; }

    /**
     * @brief Hämtar spelarens FIDE-ID.
     *
     * Returnerar spelarens unika FIDE-ID.
     *
     * @return unsigned int Spelarens FIDE-ID.
     */
    unsigned int getFideId() const { return fideId; }

    /**
     * @brief Sätter spelarens namn.
     *
     * Uppdaterar spelarens namn.
     *
     * @param newName Det nya namnet för spelaren.
     */
    void setName(const QString &newName) { name = newName; }

    /**
     * @brief Sätter spelarens rating.
     *
     * Uppdaterar spelarens rating.
     *
     * @param newRating Det nya ratingvärdet för spelaren.
     */
    void setRating(const unsigned int &newRating) { rating = newRating; }

    /**
     * @brief Sätter spelarens FIDE-ID.
     *
     * Uppdaterar spelarens unika FIDE-ID.
     *
     * @param newFideId Det nya FIDE-ID:t för spelaren.
     */
    void setFideId(const unsigned int &newFideId) { fideId = newFideId; }

private:
    QString name; ///< Spelarens namn.
    unsigned int rating; ///< Spelarens rating.
    unsigned int fideId; ///< Spelarens FIDE-ID.
};


/**
 * @class PlayerListModel
 * @brief Hanterar lagring och hantering av spelardata.
 *
 * Klassen PlayerListModel ansvarar för att lagra och manipulera en lista med spelare. Den tillhandahåller funktioner
 * för att lägga till, ta bort och uppdatera spelare både i minnet och i databasen, samt funktioner för att hämta och
 * sortera spelare.
 */
class PlayerListModel : public Model
{
public:
    /**
     * @brief Skapar en PlayerListModel-instans.
     *
     * Konstruktor som initialiserar modellen med en referens till en instans av SettingsModel.
     *
     * @param settingsModel Pekare till instansen av SettingsModel som hanterar användarinställningar.
     */
    explicit PlayerListModel(SettingsModel *settingsModel)
        : settingsModel(settingsModel) {}

    /**
     * @brief Lägger till en spelare i den interna listan (men inte i databasen).
     *
     * Denna metod lägger till en spelare i den interna behållaren för spelare, men uppdaterar inte databasen.
     *
     * @param player Spelaren som ska läggas till.
     */
    void addPlayerToContainer(const Player &player);

    /**
     * @brief Lägger till en spelare i databasen.
     *
     * Denna metod lägger till en spelare i databasen. Om spelaren redan finns kan en uppdatering göras istället.
     *
     * @param player Spelaren som ska sparas i databasen.
     */
    void addPlayerToDatabase(const Player &player);

    /**
     * @brief Uppdaterar en spelare i databasen.
     *
     * Uppdaterar spelarens information i databasen baserat på den spelare som skickas in.
     *
     * @param player Spelaren vars information ska uppdateras.
     */
    void updatePlayerInDatabase(const Player &player);

    /**
     * @brief Tar bort en spelare från databasen och den interna listan.
     *
     * Denna metod tar bort en spelare från både databasen och den interna spelardatabasen baserat på FIDE-ID.
     *
     * @param fideId Spelarens FIDE-ID.
     */
    void removePlayerById(const unsigned int &fideId);

    /**
     * @brief Hämtar pekaren till instansen av SettingsModel.
     *
     * Returnerar pekaren till instansen av SettingsModel som hanterar användarens inställningar.
     *
     * @return SettingsModel* Pekare till instansen av SettingsModel.
     */
    SettingsModel* getSettingsModel() const { return settingsModel; }

    /**
     * @brief Återställer modellen genom att rensa listan av spelare.
     *
     * Denna metod rensar den interna listan med spelare.
     */
    virtual void reset() override { players.clear(); }

    /**
     * @brief Sorterar spelarna baserat på de angivna kriterierna.
     *
     * Denna metod sorterar spelarna enligt de kriterier som skickas in. Standardkriteriet är "Name".
     *
     * @param sortCriteria En lista med strängar som representerar sorteringskriterier (t.ex. "Name", "Rating").
     */
    void doSort(const QStringList &sortCriteria = QStringList("Name"));

    /**
     * @brief Hämtar storleken på listan med spelare.
     *
     * Returnerar antalet spelare i listan.
     *
     * @return unsigned int Antalet spelare i listan.
     */
    unsigned int size() const { return players.size(); }

    /**
     * @brief Hämtar spelaren på ett specifikt index.
     *
     * Returnerar en konstant referens till spelaren på det angivna indexet.
     *
     * @param index Indexet för den spelare som ska hämtas.
     * @return const Player& Den spelare som finns på det angivna indexet.
     */
    const Player& at(const unsigned int &index) const;

    /**
     * @brief Hämtar spelaren på ett specifikt index.
     *
     * Returnerar en referens till spelaren på det angivna indexet.
     *
     * @param index Indexet för den spelare som ska hämtas.
     * @return Player& Den spelare som finns på det angivna indexet.
     */
    Player& at(const unsigned int &index);

    /**
     * @brief Hämtar en iterator till början av spelardatabasen.
     *
     * Returnerar en iterator som pekar på den första spelaren i den interna listan.
     *
     * @return std::vector<Player>::const_iterator Iterator som pekar på den första spelaren.
     */
    std::vector<Player>::const_iterator cbegin() const { return players.cbegin(); }

    /**
     * @brief Hämtar en iterator till slutet av spelardatabasen.
     *
     * Returnerar en iterator som pekar på platsen efter den sista spelaren i den interna listan.
     *
     * @return std::vector<Player>::const_iterator Iterator som pekar på slutet av spelardatabasen.
     */
    std::vector<Player>::const_iterator cend() const { return players.cend(); }

private:
    SettingsModel *settingsModel;    ///< Pekare till instansen av SettingsModel.
    std::vector<Player> players; ///< Intern behållare för spelare.
};

#endif // PLAYERLISTMODEL_H
