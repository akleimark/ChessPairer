#ifndef TOURNAMENTLISTMODEL_H
#define TOURNAMENTLISTMODEL_H

#include <QString>
#include <QDate>
#include "Interfaces.h"
#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"
#include "PlayerListModel.h"
#include <set>
#include "TournamentPlayer.h"
#include "Tournament.h"

/**
 * @class TournamentListModel
 * @brief Hanterar listan av turneringar och databashantering för dessa.
 *
 * Denna klass hanterar en lista av turneringar och implementerar funktionalitet för att
 * lägga till, uppdatera och ta bort turneringar i databasen.
 *
 * @see Tournament
 */
class TournamentListModel : public ListModel<Tournament>
{
public:
    /**
     * @brief Konstruktor för TournamentListModel.
     *
     * Skapar en instans av TournamentListModel och tar emot en referens till instansen av SettingsModel.
     *
     * @param settingsModel Pekare till en instans av SettingsModel som hanterar applikationens inställningar.
     */
    explicit TournamentListModel(Tournament &tournament, SettingsModel &settingsModel);

    /**
     * @brief Destruktör för TournamentListModel.
     *
     * Hanterar borttagning av alla resurser som används av modellen.
     */
    virtual ~TournamentListModel() = default;

    /**
     * @brief Lägger till en turnering i databasen.
     *
     * Denna metod lägger till en ny turnering i databasen.
     *
     * @param tournament Den turnering som ska läggas till i databasen.
     */
    virtual unsigned int addToDatabase(const Tournament &tournament) override;

    /**
     * @brief Uppdaterar en turnering i databasen.
     *
     * Denna metod uppdaterar en befintlig turnering i databasen baserat på turneringens ID.
     *
     * @param tournament Den turnering som ska uppdateras i databasen.
     */
    virtual void updateDatabase(const Tournament &tournament) override;

    /**
     * @brief Tar bort en turnering från databasen baserat på dess ID.
     *
     * Denna metod tar bort en turnering från databasen baserat på dess ID.
     *
     * @param id ID för den turnering som ska tas bort från databasen.
     */
    virtual void removeById(const unsigned int &id) override;

    Tournament getTournament() const { return tournament; }

    Tournament *findTournamentById(const unsigned int &id);

    void setSelectedTournament(Tournament &selectedTournament) { tournament = selectedTournament; }

private:
    Tournament &tournament;
};


#endif // TOURNAMENTLISTMODEL_H
