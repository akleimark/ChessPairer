#ifndef PLAYERLISTMODEL_H
#define PLAYERLISTMODEL_H

#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"
#include <QString>
#include "Player.h"



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
    explicit PlayerListModel(SettingsModel &settingsModel)
        : ListModel<Player>(settingsModel) {}
    virtual ~PlayerListModel() = default;

    /**
     * @brief Lägger till en spelare i databasen.
     *
     * Denna metod lägger till en spelare i databasen. Om spelaren redan finns kan en uppdatering göras istället.
     *
     * @param player Spelaren som ska sparas i databasen.
     */
    virtual unsigned int addToDatabase(const Player &player) override;

    /**
     * @brief Uppdaterar en spelare i databasen.
     *
     * Uppdaterar spelarens information i databasen baserat på den spelare som skickas in.
     *
     * @param player Spelaren vars information ska uppdateras.
     */
    virtual void updateDatabase(const Player &player) override;

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

    Player *findPlayerById(const unsigned int &fideId);
};

#endif // PLAYERLISTMODEL_H
