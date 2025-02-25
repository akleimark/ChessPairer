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

class TournamentPlayer : public Player
{
public:
    explicit TournamentPlayer(const unsigned int &fideId, const QString &name, const unsigned int &rating, const unsigned int &playerNumber);
    bool operator<(const TournamentPlayer &player) const;
    unsigned int getPlayerNumber() const {return playerNumber; }
    void setPlayerNumber(const unsigned int &newPlayerNumber) {playerNumber = newPlayerNumber; }
private:
    unsigned int playerNumber;
};

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
class Tournament : public PrintInterface, public ValidateInterface
{
public:

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

    virtual ~Tournament() = default;

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

    void setId(const unsigned int &newId) { id = newId; }

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

    /**
 * @brief Validerar turneringsobjektet.
 *
 * Utför en övergripande validering av turneringen baserat på alla dess attribut.
 *
 * @return true om turneringen är giltig, annars false.
 */
    virtual bool isValid() const override;

    /**
 * @brief Kontrollerar om turneringens namn är giltigt.
 *
 * Validerar att namnet inte är tomt och att det inte innehåller otillåtna tecken.
 *
 * @return true om namnet är giltigt, annars false.
 */
    bool checkName() const;

    /**
 * @brief Kontrollerar om startdatumet för turneringen är giltigt.
 *
 * Validerar att startdatumet är korrekt formaterat och ligger i framtiden eller nuet.
 *
 * @return true om startdatumet är giltigt, annars false.
 */
    bool checkStartDate() const;

    /**
 * @brief Kontrollerar om slutdatumet för turneringen är giltigt.
 *
 * Validerar att slutdatumet är korrekt formaterat och att det är senare än startdatumet.
 *
 * @return true om slutdatumet är giltigt, annars false.
 */
    bool checkEndDate() const;

    /**
 * @brief Kontrollerar om antalet ronder i turneringen är giltigt.
 *
 * Säkerställer att antalet ronder ligger inom det tillåtna intervallet.
 *
 * @return true om antalet ronder är giltigt, annars false.
 */
    bool checkNumberOfRounds() const;

    /**
 * @brief Kontrollerar om det valda lottningssystemet är giltigt.
 *
 * Validerar att lottningssystemet är ett av de stödda systemen (t.ex. Schweizer-systemet eller Berger-tabellen).
 *
 * @return true om lottningssystemet är giltigt, annars false.
 */
    bool checkPairingSystem() const;

    /**
 * @brief Hämtar standardvärdet för antal ronder.
 *
 * @return unsigned int Standardvärdet för antal ronder.
 */
    static unsigned int getDefaultNumberOfRounds() { return Tournament::DEFAULT_NUMBER_OF_ROUNDS; }

    /**
 * @brief Hämtar det minsta tillåtna antalet ronder.
 *
 * @return unsigned int Det minsta tillåtna antalet ronder för en turnering.
 */
    static unsigned int getMinimumNumberOfRounds() { return Tournament::MINIMUM_NUMBER_OF_ROUNDS; }

    /**
 * @brief Hämtar det maximala tillåtna antalet ronder.
 *
 * @return unsigned int Det maximala tillåtna antalet ronder för en turnering.
 */
    static unsigned int getMaximumNumberOfRounds() { return Tournament::MAXIMUM_NUMBER_OF_ROUNDS; }

    void addTournamentPlayer(TournamentPlayer *player) {players.insert(player);}

    TournamentPlayer* at(const unsigned int &index) const;


private:
    unsigned int id; /**< ID för turneringen. */
    QString name; /**< Namn på turneringen. */
    QDate startDate; /**< Startdatum för turneringen. */
    QDate endDate; /**< Slutdatum för turneringen. */
    unsigned int numberOfRounds; /**< Antal omgångar i turneringen. */
    QString pairingSystem; /**< System för paring av spelare. */
    std::set<TournamentPlayer*> players;

    const static unsigned int DEFAULT_TOURNAMENT_ID; /**< Standardvärde för turnerings-ID. */
    const static unsigned int MINIMUM_NUMBER_OF_ROUNDS; /**< Minimalt antal ronder. */
    const static unsigned int MAXIMUM_NUMBER_OF_ROUNDS; /**< Maximalt antal ronder. */
    const static unsigned int DEFAULT_NUMBER_OF_ROUNDS; /**< Standardvärde för antal ronder. */
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
    explicit TournamentListModel(Tournament * tournament, SettingsModel *settingsModel);

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
    virtual unsigned int addToDatabase(const Tournament *tournament) override;

    /**
     * @brief Uppdaterar en turnering i databasen.
     *
     * Denna metod uppdaterar en befintlig turnering i databasen baserat på turneringens ID.
     *
     * @param tournament Den turnering som ska uppdateras i databasen.
     */
    virtual void updateDatabase(const Tournament *tournament) override;

    /**
     * @brief Tar bort en turnering från databasen baserat på dess ID.
     *
     * Denna metod tar bort en turnering från databasen baserat på dess ID.
     *
     * @param id ID för den turnering som ska tas bort från databasen.
     */
    virtual void removeById(const unsigned int &id) override;

    Tournament* getTournament() const { return tournament; }

    Tournament* findTournamentById(const unsigned int &id) const;

    void setSelectedTournament(Tournament *selectedTournament) { tournament = selectedTournament; }

private:
    Tournament *tournament;
};


#endif // TOURNAMENTLISTMODEL_H
