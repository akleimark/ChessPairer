#ifndef TOURNAMENTLISTMODEL_H
#define TOURNAMENTLISTMODEL_H

#include <QString>
#include <QDate>
#include "Interfaces.h"
#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"

/**
 * @class Tournament
 * @brief Representerar en turnering i systemet.
 *
 * Denna klass hanterar information om en turnering, såsom dess namn, start- och slutdatum,
 * antal omgångar, och pairing-system. Den implementerar också gränssnittet PrintInterface för
 * att möjliggöra utskrift av turneringens detaljer.
 *
 * @see PrintInterface
 */
class Tournament : public PrintInterface
{
public:
    /**
     * @brief Standardkonstruktor för Tournament.
     *
     * Skapar en turnering med standardvärden.
     */
    Tournament();

    /**
     * @brief Konstruktor för Tournament med anpassade värden.
     *
     * Skapar en turnering med specifika parametrar, inklusive namn, datum, antal omgångar och pairing-system.
     *
     * @param name Namnet på turneringen (standard: "DEFAULT_TOURNAMENT_NAME").
     * @param startDate Startdatum för turneringen (standard: "DEFAULT_START_DATE").
     * @param endDate Slutdatum för turneringen (standard: "DEFAULT_END_DATE").
     * @param numberOfRounds Antal omgångar i turneringen (standard: "DEFAULT_NUMBER_OF_ROUNDS").
     * @param pairingSystem Systemet för paring av spelare (standard: "DEFAULT_PAIRING_SYSTEM").
     * @param id ID för turneringen (standard: "DEFAULT_TOURNAMENT_ID").
     */
    explicit Tournament(const QString &name = DEFAULT_TOURNAMENT_NAME,
                        const QDate &startDate = Tournament::DEFAULT_START_DATE, const QDate &endDate = Tournament::DEFAULT_END_DATE,
                        const unsigned int &numberOfRounds = Tournament::DEFAULT_NUMBER_OF_ROUNDS, const QString &pairingSystem = Tournament::DEFAULT_PAIRING_SYSTEM, const unsigned int &id = Tournament::DEFAULT_TOURNAMENT_ID);

    /**
     * @brief Skriver ut turneringens information.
     *
     * Denna metod skriver ut detaljer om turneringen, inklusive namn, datum och andra parametrar.
     *
     * @override
     */
    virtual void print() const override;

    /**
     * @brief Hämtar turneringens ID.
     *
     * @return ID för turneringen.
     */
    unsigned int getId() const { return id; }

    /**
     * @brief Hämtar turneringens namn.
     *
     * @return Namnet på turneringen.
     */
    QString getName() const { return name; }

    /**
     * @brief Hämtar turneringens startdatum.
     *
     * @return Startdatum för turneringen.
     */
    QDate getStartDate() const { return startDate; }

    /**
     * @brief Hämtar turneringens slutdatum.
     *
     * @return Slutdatum för turneringen.
     */
    QDate getEndDate() const { return endDate; }

    /**
     * @brief Hämtar antal omgångar i turneringen.
     *
     * @return Antal omgångar i turneringen.
     */
    unsigned int getNumberOfRounds() const { return numberOfRounds; }

    /**
     * @brief Hämtar systemet för paring av spelare.
     *
     * @return Paringsystemet för turneringen.
     */
    QString getPairingSystem() const { return pairingSystem; }

    /**
     * @brief Sätter ett nytt namn för turneringen.
     *
     * @param newName Det nya namnet på turneringen.
     */
    void setName(const QString &newName) { name = newName; }

    /**
     * @brief Sätter ett nytt startdatum för turneringen.
     *
     * @param newDate Det nya startdatumet för turneringen.
     */
    void setStartDate(const QDate &newDate) { startDate = newDate; }

    /**
     * @brief Sätter ett nytt slutdatum för turneringen.
     *
     * @param newDate Det nya slutdatumet för turneringen.
     */
    void setEndDate(const QDate &newDate) { endDate = newDate; }

    /**
     * @brief Sätter ett nytt antal omgångar för turneringen.
     *
     * @param newNumberOfRounds Det nya antalet omgångar för turneringen.
     */
    void setNumberOfRounds(const unsigned int &newNumberOfRounds) { numberOfRounds = newNumberOfRounds; }

    /**
     * @brief Sätter ett nytt paringsystem för turneringen.
     *
     * @param newPairingSystem Det nya paringsystemet för turneringen.
     */
    void setPairingSystem(const QString &newPairingSystem) { pairingSystem = newPairingSystem; }

private:
    unsigned int id; /**< ID för turneringen. */
    QString name; /**< Namn på turneringen. */
    QDate startDate; /**< Startdatum för turneringen. */
    QDate endDate; /**< Slutdatum för turneringen. */
    unsigned int numberOfRounds; /**< Antal omgångar i turneringen. */
    QString pairingSystem; /**< System för paring av spelare. */

    const static unsigned int DEFAULT_TOURNAMENT_ID; /**< Standardvärde för turnerings-ID. */
    const static unsigned int DEFAULT_NUMBER_OF_ROUNDS; /**< Standardvärde för antal omgångar. */
    const static QString DEFAULT_PAIRING_SYSTEM; /**< Standardvärde för paringsystem. */
    const static QString DEFAULT_TOURNAMENT_NAME; /**< Standardvärde för turneringsnamn. */
    const static QDate DEFAULT_START_DATE; /**< Standardvärde för startdatum. */
    const static QDate DEFAULT_END_DATE; /**< Standardvärde för slutdatum. */
};


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
    explicit TournamentListModel(SettingsModel *settingsModel);

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
    virtual void addToDatabase(const Tournament &tournament) override;

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
};


#endif // TOURNAMENTLISTMODEL_H
