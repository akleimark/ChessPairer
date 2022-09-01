#include "Defs.h"
#include "Misc.h"
#include <iomanip>
#include <iostream>
#include "Database.h"
#include "ChessplayerModel.h"
#include "Exception.h"

const unsigned int ChessplayerModel::MINIMUM_FIDE_ID = 100000;

/**
    I den här konstruktorn initieras de privata variablerna.
*/
ChessplayerModel::ChessplayerModel():
    id(0), firstname(""), lastname(""), biologicalSex(""), birthDate(""), federation(""), chessclub("")
{

}
/**
    Det här är ytterligare en konstruktor, som kan användas om man redan vet värdet på alla de privata variablerna, såsom
    'id', 'firstname', lastname' med mera.
*/
ChessplayerModel::ChessplayerModel(const unsigned int &p_id, const wxString &p_firstname, const wxString &p_lastname, const wxString &p_biologicalSex, const wxString &p_birthDate,
            const wxString &p_federation, const wxString &p_chessclub):
            id(p_id), firstname(p_firstname), lastname(p_lastname), biologicalSex(p_biologicalSex), birthDate(p_birthDate), federation(p_federation), chessclub(p_chessclub)
{

}

/**
    Den här funktionen används för att kontrollera huruvida schackspelarens data är korrekt. Om de inte är korrekta
    kan inte schackspelaren sparas till databasen.
*/
bool ChessplayerModel::validate() const
{
    if(id < MINIMUM_FIDE_ID)
    {
        return false;
    }

    if(firstname.length() < MINIMUM_LENGTH || lastname.length() < MINIMUM_LENGTH)
    {
        return false;
    }

    if(!(biologicalSex == "man" || biologicalSex == "kvinna"))
    {
        return false;
    }

    if(federation.length() < MINIMUM_LENGTH)
    {
        return false;
    }

    if(chessclub.length() < MINIMUM_LENGTH)
    {
        return false;
    }

    if(birthDate.length() != 10)
    {
        return false;
    }

    std::vector<wxString> vector_split;
    misc::split(birthDate, '-', vector_split);

    if(vector_split.size() != 3)
    {
        return false;
    }
    Date date(wxAtoi(vector_split[0]), wxAtoi(vector_split[1]), wxAtoi(vector_split[2]));
    return (date.validate());

}

/**
    Den här funktionen används för att få fram schackspelarens födelseår. Det kan vara aktuellt,
    om man vill få fram om en schackspelare är junior eller veteran.
*/
unsigned int ChessplayerModel::getBirthYear() const
{
    std::vector<wxString> vector_split;
    misc::split(birthDate, '-', vector_split);

    if(vector_split.size() < 1)
    {
        return 0;
    }
    return wxAtoi(vector_split[0]);
}

/**
    Den här funktionen används för att kontrollera huruvida två schackspelare är identiska.
*/
bool ChessplayerModel::operator==(const ChessplayerModel &chessplayer)
{
    if(id == chessplayer.id)
    {
        if(id != 0)
        {
            return true;
        }
        if(firstname == chessplayer.firstname && lastname == chessplayer.lastname && birthDate == chessplayer.birthDate)
        {
            return true;
        }
        return false;
    }

    return false;

}

/**
    Den här operatoröverlagringen kontrollerar hurvida en schackspelare är mindre än en annan schackspelare.
    Funktionen behövs för att kunna stoppa in schackspelare i en std::set, eftersom alla schackspelare i en sådan
    container är unika, vilket innebär att två schackspelare alltid är olika i en sådan container.
*/
bool ChessplayerModel::operator<(const ChessplayerModel &chessplayer) const
{
    if(id < chessplayer.id)
    {
        return true;
    }
    if(firstname < chessplayer.firstname)
    {
        return true;
    }
    if(lastname < chessplayer.lastname)
    {
        return true;
    }
    if(birthDate < chessplayer.birthDate)
    {
        return true;
    }

    return false;
}

/**
    Den här funktionen används för att skriva ut schackspelarens data till konsolen.
*/
void ChessplayerModel::print() const
{
    const unsigned int GAP = 25;

    std::cout << "Id:" << std::setw(GAP) << id << std::endl
        << "Namn: " << std::setw(GAP) << firstname << " " << lastname << std::endl
        << L"Biologiskt k\u00F6n: " << std::setw(GAP) << biologicalSex << std::endl
        << L"F\u00F6delsedatum: " << std::setw(GAP) << birthDate << std::endl
        << "Nation: " << std::setw(GAP) << federation << std::endl
        << "Schackkklubb: " << std::setw(GAP) << chessclub << std::endl
        << "--------------------------------------------------------------" << std::endl;
}

/**
    Den här funktionen sparar aktuell instans av "Chessplayer" till databasen. Innan den här funktionen körs kontrolleras
    att alla värden är korrekta och att det kommer att gå att spara. Det innebär att den här funktionen bara sätter in värdena och vet att
    alla förberedelser är genomförda.
*/
void ChessplayerModel::addToDatabase() const
{
    wxString ss;
    ss << "insert into chessplayers(id, firstname, lastname, biological_sex, birth_date, federation, chessclub) values(";
    ss << id << ", '" << firstname << "','" << lastname << "', '" << biologicalSex << "', '" << birthDate << "', '" << federation << "', '" << chessclub << "')";

    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss);
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
}

/**
    Den här funktionen används för att radera schackspelaren ur databasen.
*/
void ChessplayerModel::removeFromDatabase() const
{
    wxString ss;
    ss << "delete from chessplayers where id=" << id;

    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss);
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
}

/**
    Den här funktionens uppgift består i att uppdatera en schackspelare, som redan finns inlagd i databasen.
*/
void ChessplayerModel::save() const
{

}


/**
    Den här funktionen återställer alla schackspelarens datamedlemmar till de värden som gällde från början.
*/
void ChessplayerModel::reset()
{
    id = 0;
    firstname = "";
    lastname = "";
    biologicalSex = "";
    birthDate = "";
    federation = "";
    chessclub = "";
}
