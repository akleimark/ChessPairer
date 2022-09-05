#include "Database.h"
#include <iostream>
#include "Misc.h"
#include <cstring>
#include "Exception.h"

const wxString Database::DATABASE_NAME = "database.db";
Database* Database::instance = nullptr;
std::vector<std::vector<wxString>> Database::dataRecords;

/**
    Den här privata konstruktorn sätter 'errorMessage' till 0, samt nollställer 'dataRecords'.
    När man vill använda databasklassen använder man sig av Database::getInstance().
*/
Database::Database()
{
    errorMessage = 0;
    dataRecords.resize(0);
}

/**
    I den här destruktorn raderas de pekare som har skapats.
*/
Database::~Database()
{
    if(database != nullptr)
    {
        delete database;
        database = nullptr;
    }

    if(errorMessage != 0)
    {
        sqlite3_free(errorMessage);
    }

    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

/**
    Det är med hjälp av den här funktionen som den här klassen används.
    Konstruktorn är privat och klassen implementeras i stället med hjälp av
    designmönstret 'Singleton'.
*/
Database* Database::getInstance()
{
    if(Database::instance == nullptr)
    {
        instance = new Database;
    }

    return instance;
}

/**
    Syftet med den här funktionen är att öppna databasen. Om detta inte är möjligt, kommer en undantagsituation att
    hanteras av applikationen.
*/
void Database::open()
{
    bool databaseExists = misc::fileExists(DATABASE_NAME);

    if(sqlite3_open(DATABASE_NAME.c_str(), &database))
    {
       throw DatabaseErrorException("It was not possible to open the database. The application will exit");
    }
    else
    {
        std::cout << "The database was successfully opened." << std::endl;
        if(!databaseExists)
        {
            createTables();
        }
    }
}

/**
    Den här funktionen körs endast om det inte redan finns en databas.
    Syftet med den är att skapa de tabeller, som databasen behöver.

**/
void Database::createTables()
{
    std::vector<std::string> sqlQueries;
    sqlQueries.push_back("PRAGMA foreign_keys = ON");
    sqlQueries.push_back("PRAGMA encoding='UTF-16BE'");
    sqlQueries.push_back("create table chessplayers(id int primary key, firstname text not null, lastname text not null, biological_sex text not null, birth_date text not null, federation text not null, chessclub text not null)");
    sqlQueries.push_back("create table tournaments(id text primary key, start_date date not null, end_date date not null, number_of_rounds int not null, pairing_system text not null, started BOOLEAN default 0)");
    sqlQueries.push_back("create table tournament_players(tournament_id text not null, chessplayer_id int not null, player_number int not null, primary key(tournament_id, chessplayer_id), foreign key(tournament_id) references tournaments(id) on delete cascade on update cascade,foreign key(chessplayer_id) references chessplayers(id) on delete cascade on update cascade)");
    sqlQueries.push_back("create table tiebreaks(id text primary key)");
    sqlQueries.push_back("create table tournament_tiebreaks(tournament_id text not null, tiebreak_id text not null, tiebreak_order int not null, primary key(tournament_id, tiebreak_id), foreign key(tournament_id) references tournaments(id) on delete cascade on update cascade, foreign key(tiebreak_id) references tiebreaks(id) on delete cascade on update cascade)");

    sqlQueries.push_back("insert into tiebreaks(id) values('Buchholz')");
    sqlQueries.push_back("insert into tiebreaks(id) values('Median-Buchholz')");
    sqlQueries.push_back("insert into tiebreaks(id) values('Antal vinster')");
    sqlQueries.push_back("insert into tiebreaks(id) values('Antal svarta partier')");
    sqlQueries.push_back("insert into tiebreaks(id) values('Lottning')");
    sqlQueries.push_back("insert into tiebreaks(id) values('Sonneborn-Berger')");

    bool errors = false;
    for(wxString sql : sqlQueries)
    {
        if(sqlite3_exec(database, sql, nullptr, nullptr, nullptr) != SQLITE_OK)
        {
            errors = true;
            break;
        }
    }

    if(errors == true)
    {
        throw DatabaseErrorException("It was not possible to create the tables. The program will exit.");
    }

    std::cout << "The tables were successfully created. " << std::endl;

}

/**
    Den här funktionen används när det finns ett behov av att stänga databasen.
*/
void Database::close()
{
    if(sqlite3_close(database) != SQLITE_OK)
    {
        throw DatabaseErrorException("There was an error while closing the database.");
    }

    std::cout << "The database was succefully closed. " << std::endl;
}
/**
    Den här funktionen fabriksåterställer databasen. Det innebär att databasfilen tas bort från
    filsystemet och en ny databas skapas. All tidigare data kommer att raderas.
*/
void Database::resetDatabase()
{
    try
    {
        this->close();
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }
    if(remove(Database::DATABASE_NAME) == 0)
    {
        this->open();
    }
    else
    {
        throw DatabaseErrorException("Error occurred while trying to remove the database file.");
    }
}

/**
    Den här funktionen används för att göra slagningar i databasen.
    @param sql Den sql-fråga, som skall användas.
*/
void Database::executeSql(const std::string &sql)
{
    dataRecords.clear();
    wxString ss;

    rc = sqlite3_exec(database, sql.c_str(), callback, 0, &errorMessage);
    if(rc != SQLITE_OK)
    {
        ss << errorMessage;
        sqlite3_free(errorMessage);
        throw DatabaseErrorException(ss);
    }
}

/**
    Med hjälp av den här funktionen läggs data från databasen in i 'dataRecords', som sedan kan
    användas av andra klasser via funktionen 'atIndex'.
*/
int Database::callback(void *data, int argc, char **argv, char **azColName)
{
    std::vector<wxString> row;
    int i;
    for(i = 0; i < argc; i++)
    {
        row.push_back(argv[i]);
    }

    dataRecords.push_back(row);
    return 0;
}

/**
    Med hjälp av den här funktionen får man tag på det som har hämtats ur databasen.
    @param i Rad i
    @param j Kolumn j
*/
wxString Database::atIndex(const unsigned int &i, const unsigned int &j) const
{
    return Database::dataRecords[i][j];
}

