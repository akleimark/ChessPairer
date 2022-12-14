#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <map>
#include <vector>
#include <wx/string.h>

/**
    Det h?r ?r databasklassen, som anv?nds f?r att h?mta data ur databasen. Sj?lva databashanteraren anv?nder
    sig av sqlite.
*/
class Database
{
    public:

        virtual ~Database();
        void open();
        void close();
        void executeSql(const std::string &sql);
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
            Den h?r variabeln anv?nds f?r att g?ra slagningar i databasen och ?ven att
            kontrollera huruvida n?gonting gick fel.
        */
        int rc;
        /// Den h?r variabeln h?ller reda p? namnet p? databsen. Namnet ?r en konstant.
        const static wxString DATABASE_NAME;
        void createTables();
        /// I den h?r variablen hamnar alla eventuella felmeddelanden.
        char* errorMessage;
        /// Den h?r klassvariabeln anv?nds f?r att s?kerst?lla att endast en instans av klassen skapas.
        static Database* instance;

        static int callback(void *data, int argc, char **argv, char **azColName);
        /// I den h?r vektorn hamnar alla resultat efter slagningar i databasen.
        static std::vector<std::vector<wxString>> dataRecords;
};

#endif // DATABASE_H
