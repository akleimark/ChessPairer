#ifndef PLAYERLISTMODEL_H
#define PLAYERLISTMODEL_H

#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"
#include <QString>

/**
 * @class Player
 * @brief Representerar en schackspelare med namn, rating och FIDE-ID.
 *
 * Klassen Player används för att lagra information om en schackspelare, inklusive spelarens namn,
 * rating och unika FIDE-ID. Den tillhandahåller getter- och setter-metoder för dessa attribut.
 */
class Player : public ValidateInterface
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
    explicit Player(const unsigned int &fideId = 0, const QString &name = "", const unsigned int &rating = Player::MINIMUM_RATING)
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

    const static unsigned int getMinimumRating() {return Player::MINIMUM_RATING; }
    const static unsigned int getMaximumRating() {return Player::MAXIMUM_RATING; }

    virtual bool isValid() const override;
    bool checkName() const;
    bool checkRating() const;
    bool checkFideId() const;

protected:
    unsigned int fideId; ///< Spelarens FIDE-ID.
    QString name; ///< Spelarens namn.
    unsigned int rating; ///< Spelarens rating.    
    const static unsigned int MINIMUM_RATING;
    const static unsigned int MAXIMUM_RATING;
};


/**
 * @class PlayerListModel
 * @brief Hanterar lagring och hantering av spelardata.
 *
 * Klassen PlayerListModel ansvarar för att lagra och manipulera en lista med spelare. Den tillhandahåller funktioner
 * för att lägga till, ta bort och uppdatera spelare både i minnet och i databasen, samt funktioner för att hämta och
 * sortera spelare.
 */
class PlayerListModel : public ListModel<Player>
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
        : ListModel<Player>(settingsModel) {}
    virtual ~PlayerListModel() = default;

    /**
     * @brief Lägger till en spelare i databasen.
     *
     * Denna metod lägger till en spelare i databasen. Om spelaren redan finns kan en uppdatering göras istället.
     *
     * @param player Spelaren som ska sparas i databasen.
     */
    virtual unsigned int addToDatabase(const Player *player) override;

    /**
     * @brief Uppdaterar en spelare i databasen.
     *
     * Uppdaterar spelarens information i databasen baserat på den spelare som skickas in.
     *
     * @param player Spelaren vars information ska uppdateras.
     */
    virtual void updateDatabase(const Player *player) override;

    /**
     * @brief Tar bort en spelare från databasen och den interna listan.
     *
     * Denna metod tar bort en spelare från både databasen och den interna spelardatabasen baserat på FIDE-ID.
     *
     * @param id Spelarens FIDE-ID.
     */
    virtual void removeById(const unsigned int &id) override;

    /**
     * @brief Sorterar spelarna baserat på de angivna kriterierna.
     *
     * Denna metod sorterar spelarna enligt de kriterier som skickas in. Standardkriteriet är "Name".
     *
     * @param sortCriteria En lista med strängar som representerar sorteringskriterier (t.ex. "Name", "Rating").
     */
    void doSort(const QStringList &sortCriteria = QStringList("Name"));
};

#endif // PLAYERLISTMODEL_H
