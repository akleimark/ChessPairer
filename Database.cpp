#include "Database.h"
#include <stdexcept>
#include "Logger.h"

const QString Database::DATABASE_NAME = "chesspairing.db";
Database* Database::instance = nullptr;

Database::Database():
    db(QSqlDatabase::addDatabase("QSQLITE"))
{    
    db.setDatabaseName(Database::DATABASE_NAME);

    try
    {
        if (!db.open())
        {
            const QString ERROR_MESSAGE = "Det uppstod ett fel vid anslutning till databasen.";
            Logger::getInstance()->logError(ERROR_MESSAGE);
            throw std::runtime_error(ERROR_MESSAGE.toStdString());
        }
        createTables();
    }
    catch(const std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE); // Avsluta programmet med felstatus
    }
}

Database::~Database()
{
    if (db.isOpen())
    {
        db.close();
    }
}

void Database::createTables()
{
    QSqlQuery query;
    QStringList queries;
    // Sql för tabellen med spelare.
    queries << "CREATE TABLE IF NOT EXISTS players ("
               "fide_id INTEGER PRIMARY KEY, "
               "name TEXT NOT NULL, "
               "rating INTEGER NOT NULL)";

    // Sql för inställningar.
    queries << "CREATE TABLE IF NOT EXISTS settings("
                "type TEXT PRIMARY KEY, "
                "value TEXT NOT NULL)";

    // Sql för turneringar
    queries << "CREATE TABLE IF NOT EXISTS tournaments("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT NOT NULL, "
                "start_date DATE NOT NULL, "
                "end_date DATE NOT NULL, "
                "number_of_rounds INTEGER NOT NULL, "
                "pairing_system TEXT NOT NULL)"
        ;

    for (QStringList::const_iterator it = queries.cbegin(); it != queries.cend(); ++it)
    {
        const QString &cQuery = *it;
        if (!query.exec(cQuery))
        {
            throw std::runtime_error("SQl-frågan misslyckades (" + cQuery.toStdString() + ")" + query.lastError().text().toStdString());
        }
    }

}

Database* Database::getInstance()
{
    if (!instance)
    {
        instance = new Database();
    }
    return instance;
}

void Database::executeQuery(const QString& queryStr, const QVector<QVariant>& bindValues)
{
    QSqlQuery query;

    // Prepare the SQL query
    if (!query.prepare(queryStr))
    {
        throw std::runtime_error("Failed to prepare SQL query: " + query.lastError().text().toStdString());
    }

    // Bind all provided values securely
    for (const QVariant& value : bindValues)
    {
        query.addBindValue(value);
    }

    // Execute the query and handle errors
    if (!query.exec())
    {
        throw std::runtime_error("SQL error: " + query.lastError().text().toStdString());
    }
}

bool Database::executeQueryWithResult(const QString& queryStr, const QVector<QVariant>& bindValues, QSqlQuery &query)
{
    // Förbered SQL-frågan
    if (!query.prepare(queryStr))
    {
        throw std::runtime_error("Misslyckades med prepare: " + query.lastError().text().toStdString());
    }

    // Bind alla värden till SQL-frågan
    for (const QVariant& value : bindValues)
    {
        query.addBindValue(value);
    }

    // Utför frågan
    if (!query.exec())
    {
        throw std::runtime_error("SQL-fel: " + query.lastError().text().toStdString());
    }

    // Kontrollera om frågan returnerar resultat (t.ex. SELECT)
    return query.next();  // Returnerar true om en rad är tillgänglig
}

QSqlQuery Database::selectQuery(const QString& queryStr)
{
    QSqlQuery query;
    if (!query.exec(queryStr))
    {
        throw std::runtime_error("SQL-fel:" + query.lastError().text().toStdString());
    }
    return query;
}

void Database::loadTournamentsFromDatabase(TournamentListModel *model)
{
    try
    {
        if (!model)
        {
            throw std::runtime_error("Ett okänt fel uppstod.");
        }

        model->reset(); // Rensa modellen innan vi laddar om data

        QSqlQuery query = Database::getInstance()->selectQuery(
            "SELECT id, name, start_date, end_date, number_of_rounds, pairing_system FROM tournaments ORDER BY name"
            );
        while (query.next())
        {
            const unsigned int id = query.value(0).toUInt();
            const QString name = query.value(1).toString();

            // Säkerställ att datum konverteras korrekt
            const QString startDateStr = query.value(2).toString();
            const QString endDateStr = query.value(3).toString();
            const QDate startDate = QDate::fromString(startDateStr, "yyyy-MM-dd");
            const QDate endDate = QDate::fromString(endDateStr, "yyyy-MM-dd");

            if (!startDate.isValid() || !endDate.isValid())
            {
                qWarning() << "Ogiltigt datum i databasen: " << startDateStr << ", " << endDateStr;
                continue; // Hoppa över denna post
            }

            const unsigned int numberOfRounds = query.value(4).toUInt();
            const QString pairingSystem = query.value(5).toString();

            // Lägg till turneringen i modellen
            model->addToContainer(Tournament(name, startDate, endDate, numberOfRounds, pairingSystem, id));
        }
    }
    catch(std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void Database::loadPlayersFromDatabase(PlayerListModel *model, const QString &orderList)
{
    try
    {
        if(!model)
        {
            throw std::runtime_error("Ett okänt fel uppstod.");
        }
        model->reset();
        QSqlQuery query = Database::getInstance()->selectQuery("SELECT name, rating, fide_id FROM players ORDER BY " + orderList);

        while (query.next())
        {
            QString name = query.value(0).toString();
            int rating = query.value(1).toInt();
            int fideId = query.value(2).toInt();
            model->addToContainer(Player(name, rating, fideId));  // Lägg till spelare i MVC
        }
    }
    catch(std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void Database::loadSettingsFromDatabase(SettingsModel* model)
{
    try
    {
        if(!model)
        {
            throw std::runtime_error("Ett okänt fel uppstod.");
        }

        model->reset();
        QSqlQuery query = Database::getInstance()->selectQuery("SELECT type, value FROM settings");

        while (query.next())
        {
            QString type = query.value(0).toString();
            QString value = query.value(1).toString();
            model->addSettingToContainer(Setting(type, value));  // Lägg till inställning i MVC
        }
    }
    catch(std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}
