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
    // Skapa tabellen om den inte finns
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS players ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "rating INTEGER, "
               "fide_id INTEGER UNIQUE)");
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
