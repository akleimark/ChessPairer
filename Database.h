#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database
{
    public:
        static Database* getInstance();
        bool executeQuery(const QString& queryStr);
        QSqlQuery selectQuery(const QString& queryStr);

    private:
        Database();
        ~Database();
        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;
        void createTables();
        static Database* instance;
        QSqlDatabase db;
        const static QString DATABASE_NAME;
};

#endif // DATABASE_H
