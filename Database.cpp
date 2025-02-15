#include "Database.h"

const QString Database::DATABASE_NAME = "chesspairing.db";
Database* Database::instance = nullptr;

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Database::DATABASE_NAME);

    if (!db.open())
    {
        qDebug() << "Error: Unable to open database!" << db.lastError().text();
    } else
    {
        qDebug() << "Database successfully opened.";
        createTables();
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
    // Skapa tabellen players om den inte finns.
    query.exec("CREATE TABLE IF NOT EXISTS players ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "rating INTEGER, "
               "fide_id INTEGER UNIQUE)");
    // Skapa tabellen settings om den inte finns.
    query.exec("CREATE TABLE IF NOT EXISTS settings("
                "type TEXT PRIMARY KEY, "
                "value TEXT NOT NULL)");
}

Database* Database::getInstance()
{
    if (!instance)
    {
        instance = new Database();
    }
    return instance;
}

bool Database::executeQuery(const QString& queryStr)
{
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQuery Database::selectQuery(const QString& queryStr)
{
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "SQL Error:" << query.lastError().text();
    }
    return query;
}

void Database::loadPlayersFromDatabase(PlayerListModel *model, const QString &orderList)
{
    if(!model)
    {
        return;
    }

    model->reset();
    QSqlQuery query = Database::getInstance()->selectQuery("SELECT name, rating, fide_id FROM players ORDER BY " + orderList);

    while (query.next())
    {
        QString name = query.value(0).toString();
        int rating = query.value(1).toInt();
        int fideId = query.value(2).toInt();
        model->addPlayerToContainer(Player(name, rating, fideId));  // Lägg till spelare i MVC
    }
}

void Database::loadSettingsFromDatabase(SettingsModel* model)
{
    if(!model)
    {
        return;
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
