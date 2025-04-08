#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QString>
#include <QDate>
#include "Interfaces.h"
#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"
#include "PlayerListModel.h"
#include <set>
#include "TournamentPlayer.h"

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

    /** Tillägg av en turneringsspelare */
    void addTournamentPlayer(const TournamentPlayer &player);
    /** Borttagning av en turneringsspelare. */
    void removeTournamentPlayer(const TournamentPlayer &player);
    /** Vi hämtar turneringsspelare på index 'index'. */
    TournamentPlayer* at(const unsigned int &index);
    /** Samma som Tournament::at */
    TournamentPlayer* operator[](const unsigned int &index) const;
    /** Metod för att hitta en pekare till den spelare som har angivet FideID. */
    TournamentPlayer* findByFideId(const unsigned int &fideId) const;
    /** Metod för att returnera en iterator till det första objektet i containern med spelare. */
    std::set<TournamentPlayer>::const_iterator cbegin() const { return players.cbegin(); }
    /** Metod för att returnera en iterator till det sista objektet i containern med spelare. */
    std::set<TournamentPlayer>::const_iterator cend() const { return players.cend(); }
    /** Metod för att returnera antalet turneringsspelare i containern med spelare. */
    unsigned int size() const { return players.size(); }
    /** Metod för att hämta data om en viss turnering från databasen och sedan lagra den i turneringsobjektet. */
    void getTournamentDataFromDatabase();

private:
    unsigned int id; /**< ID för turneringen. */
    QString name; /**< Namn på turneringen. */
    QDate startDate; /**< Startdatum för turneringen. */
    QDate endDate; /**< Slutdatum för turneringen. */
    unsigned int numberOfRounds; /**< Antal omgångar i turneringen. */
    QString pairingSystem; /**< System för paring av spelare. */
    std::set<TournamentPlayer> players; /** Container med turneringsspelare */

    const static unsigned int DEFAULT_TOURNAMENT_ID; /**< Standardvärde för turnerings-ID. */
    const static unsigned int MINIMUM_NUMBER_OF_ROUNDS; /**< Minimalt antal ronder. */
    const static unsigned int MAXIMUM_NUMBER_OF_ROUNDS; /**< Maximalt antal ronder. */
    const static unsigned int DEFAULT_NUMBER_OF_ROUNDS; /**< Standardvärde för antal ronder. */
    const static QString DEFAULT_PAIRING_SYSTEM; /**< Standardvärde för paringsystem. */
    const static QString DEFAULT_TOURNAMENT_NAME; /**< Standardvärde för turneringsnamn. */
    const static QDate DEFAULT_START_DATE; /**< Standardvärde för startdatum. */
    const static QDate DEFAULT_END_DATE; /**< Standardvärde för slutdatum. */
};

#endif // TOURNAMENT_H
