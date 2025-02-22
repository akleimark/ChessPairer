#ifndef DATABASE_H
#define DATABASE_H

#include "PlayerListModel.h"
#include "TournamentListModel.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @class Database
 * @brief Hanterar anslutningen till SQLite-databasen och exekvering av SQL-frågor.
 *
 * Database implementerar en singleton-design för att säkerställa att endast en
 * databasanslutning existerar under programmets körning.
 */
class Database
{
    public:
    /**
     * @brief Hämtar instansen av Database-klassen (singleton).
     *
     * @return En pekare till den enda instansen av Database.
     */
    static Database* getInstance();

    /**
     * @brief Exekverar en SQL-fråga som inte returnerar några resultat, t.ex. INSERT, UPDATE eller DELETE.
     *
     * @param queryStr SQL-frågan som ska exekveras.
     * @return true om frågan exekverades framgångsrikt, annars false.
     */
    void executeQuery(const QString& queryStr, const QVector<QVariant>& bindValues);

    bool executeQueryWithResult(const QString& queryStr, const QVector<QVariant>& bindValues, QSqlQuery &query);

    /**
     * @brief Exekverar en SQL-fråga som returnerar resultat, t.ex. SELECT.
     *
     * @param queryStr SQL-frågan som ska exekveras.
     */
    QSqlQuery selectQuery(const QString& queryStr);

    /**
 * @brief Hämtar databasinstansen.
 *
 * @return Referens till den öppna databasen.
 */
    QSqlDatabase& getDatabase()
    {
        return db;
    }

    void loadTournamentsFromDatabase(TournamentListModel *model);


    /**
 * @brief Laddar spelare från databasen och fyller en modell.
 *
 * @param model Pekare till PlayerListModel där spelarna ska laddas in.
 * @param orderList (Valfritt) Anger hur spelarna ska sorteras, standardvärdet är "name".
 */
    void loadPlayersFromDatabase(PlayerListModel *model, const QString &orderList = "name");

    /**
 * @brief Laddar inställningar från databasen och fyller en modell.
 *
 * @param model Pekare till SettingsModel där inställningarna ska laddas in.
 */
    void loadSettingsFromDatabase(SettingsModel* model);
    private:
    /**
     * @brief Privat konstruktor för att förhindra direkt instansiering (singleton-mönster).
     */
    Database();

    /**
     * @brief Privat destruktor.
     */
    ~Database();

    /**
     * @brief Förhindrar kopiering av Database-instansen.
     */
    Database(const Database&) = delete;

    /**
     * @brief Förhindrar tilldelning av Database-instansen.
     */
    Database& operator=(const Database&) = delete;

    /**
     * @brief Skapar de nödvändiga tabellerna i databasen om de inte redan finns.
     */
    void createTables();

    /**
     * @brief Pekare till den enda instansen av Database-klassen.
     */
    static Database* instance;

    /**
     * @brief SQLite-databasanslutningen.
     */
    QSqlDatabase db;

    /**
     * @brief Namnet på databasen.
     */
    static const QString DATABASE_NAME;

};

#endif // DATABASE_H
