#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <map>
#include <vector>
#include <wx/string.h>

/**
    Det här är databasklassen, som används för att hämta data ur databasen. Själva databashanteraren använder
    sig av sqlite.
*/
class Database
{
    public:

        virtual ~Database();
        void open();
        void close();
        void executeSql(const wxString &sql);
        char* getErrorMessage() const { return errorMessage; }
        static Database* getInstance();
        wxString atIndex(const unsigned int &i, const unsigned int &j) const;
        unsigned int getSize() const { return dataRecords.size(); }
        void resetDatabase();


    protected:

    private:

        Database();
        sqlite3 *database;

        /**
            Den här variabeln används för att göra slagningar i databasen och även att
            kontrollera huruvida någonting gick fel.
        */
        int rc;
        /// Den här variabeln håller reda på namnet på databsen. Namnet är en konstant.
        const static wxString DATABASE_NAME;
        void createTables();
        /// I den här variablen hamnar alla eventuella felmeddelanden.
        char* errorMessage;
        /// Den här klassvariabeln används för att säkerställa att endast en instans av klassen skapas.
        static Database* instance;

        static int callback(void *data, int argc, char **argv, char **azColName);
        /// I den här vektorn hamnar alla resultat efter slagningar i databasen.
        static std::vector<std::vector<wxString>> dataRecords;
};

#endif // DATABASE_H
