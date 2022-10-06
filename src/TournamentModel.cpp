#include "TournamentModel.h"
#include "Database.h"
#include "Exception.h"
#include "Defs.h"
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

const unsigned int TournamentModel::MINIMUM_NUMBER_OF_ROUNDS = 1;
const unsigned int TournamentModel::MAXIMUM_NUMBER_OF_ROUNDS = 100;
const std::vector<wxString> TournamentModel::PAIRING_SYSTEMS = {"Monrad", "Berger"};

/**
    I den förvalda konstruktorn sätts turneringens id till "", antalet ronder till 0, samt lottningssystemet till "".
*/
TournamentModel::TournamentModel():
    id(""), numberOfRounds(0), pairingSystem("")
{
    startDate.reset();
    endDate.reset();
}
/**
    I destruktorn rensas turneringsspelarna och särskiljningssystemen. Dessa finns lagrade i containrarna
    'tournaments', respektive 'tiebreaks'.
*/
TournamentModel:: ~TournamentModel()
{
    this->clearTournamentPlayers();
    this->clearTournamentTiebreaks();
    std::cout << "Destructor TournamentModel::~TournamentModel() called." << std::endl;
}

bool TournamentModel::validate() const
{
    if(id.length() < MINIMUM_LENGTH)
    {
        return false;
    }

    if(!(MINIMUM_NUMBER_OF_ROUNDS <= numberOfRounds && numberOfRounds <= MAXIMUM_NUMBER_OF_ROUNDS))
    {
        return false;
    }
    bool validPairingSystem = false;
    for(wxString pSystem : PAIRING_SYSTEMS)
    {
        if(pSystem == pairingSystem)
        {
            validPairingSystem = true;
            break;
        }
    }

    if(validPairingSystem == false)
    {
        return false;
    }

    if(startDate.validate() == false || endDate.validate() == false || startDate > endDate)
    {
        return false;
    }

    if(startDate > endDate)
    {
        return false;
    }

    return true;
}

void TournamentModel::save() const
{

}

void TournamentModel::addToDatabase() const
{
    std::stringstream ss;
    ss << "insert into tournaments(id, start_date, end_date, number_of_rounds, pairing_system) values('";
    ss << id << "','" << startDate.getDateString() << "', '" << endDate.getDateString() << "', "
        << numberOfRounds << ",'" << pairingSystem << "')";

    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
}

void TournamentModel::removeFromDatabase() const
{
    std::stringstream ss;
    ss << "delete from tournaments where id='" << id << "'";

    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
}

void TournamentModel::reset()
{
    id = "";
    numberOfRounds = 0;
    pairingSystem = "";
    startDate.reset();
    endDate.reset();
}

void TournamentModel::print() const
{
    std::cout << "Id: " << id << std::endl
        << "Startdatum: " << startDate.getDateString() << std::endl
        << "Slutdatum: " << endDate.getDateString() << std::endl
        << "Antal ronder: " << numberOfRounds << std::endl
        << "Lottningssystem: " << pairingSystem << std::endl
        << "----------------------------------------------------" << std::endl;
}

/**
    Med hjälp av den här funktionen hämtas alla turneringsspelarna i turneringen från databasen och
    läggs i vektorn 'tournamentPlayers'.
*/

void TournamentModel::getAllTournamentPlayers()
{
    clearTournamentPlayers();
    Database *database = Database::getInstance();
    std::stringstream ss;
    ss << "select chessplayer_id, player_number from tournament_players ";
    ss << "where tournament_id='" << id << "' order by player_number";

    try
    {
        database->executeSql(ss.str());

        for(unsigned int index = 0; index < database->getSize(); index++)
        {
            TournamentPlayerModel *tournamentPlayerModel = new TournamentPlayerModel(id, wxAtoi(database->atIndex(index, 0)), wxAtoi(database->atIndex(index, 1)));
            tournamentPlayers.insert(tournamentPlayerModel);
        }
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }
}

/**
    Den här funktionen tar fram alla turneringens särskiljningssystem ur databasen.
*/
void TournamentModel::getAllTiebreaks()
{
    clearTournamentTiebreaks();
    Database *database = Database::getInstance();
    std::stringstream ss;
    ss << "select tiebreak_id from tournament_tiebreaks ";
    ss << "where tournament_id='" << id << "' order by tiebreak_order";

    try
    {
        database->executeSql(ss.str());

        for(unsigned int index = 0; index < database->getSize(); index++)
        {
            TiebreakModel *tiebreak = new TiebreakModel(database->atIndex(index, 0));
            tiebreaks.push_back(tiebreak);
        }
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }
}

void TournamentModel::clearTournamentPlayers()
{
    for(TournamentPlayerModel *player : tournamentPlayers)
    {
        if(player != nullptr)
        {
            delete player;
            player = nullptr;
        }
    }

    tournamentPlayers.clear();

}

void TournamentModel::clearTournamentTiebreaks()
{
    for(TiebreakModel *tiebreak : tiebreaks)
    {
        if(tiebreak != nullptr)
        {
            delete tiebreak;
            tiebreak = nullptr;
        }
    }

    tiebreaks.clear();
}

void TournamentModel::addTournamentPlayer(TournamentPlayerModel *player)
{
    if(player == nullptr)
    {
        throw ArgumentErrorException(L"V\u00E4rdet p\u00E5 'player' \u00E4r 'null'");
    }

    tournamentPlayers.insert(player);
}

/**
    Den här funktionen tar bort en viss turneringsspelare från turneringen.
    Spelaren tas först bort ur containern, där turneringsspelarna lagras ('tournamentPlayers'),
    för att sedermera raderas ur databasen.
*/
void TournamentModel::removeTournamentPlayer(TournamentPlayerModel *player)
{
    tournamentPlayers.erase(player);
    try
    {
        player->removeFromDatabase();
    }
    catch(const Exception &)
    {
        throw;
    }

    delete player;
    player = nullptr;
}

void TournamentModel::generatePlayerNumbers()
{
    bool taken[tournamentPlayers.size()];
    std::set<TournamentPlayerModel*>::iterator it;
    unsigned int index = 0;

    for(it = tournamentPlayers.begin(); it !=tournamentPlayers.end(); ++it)
    {
        taken[index++] = false;
        (*it)->setPlayerNumber(0);
    }

    std::srand (time (nullptr));
    for(it = tournamentPlayers.begin(); it !=tournamentPlayers.end(); ++it)
    {
        do
        {
            unsigned int number = rand() % tournamentPlayers.size();
            if(taken[number] == false)
            {
                (*it)->setPlayerNumber(number);
                taken[number] = true;
                break;
            }
        }
        while(true);
    }

    Database *database = Database::getInstance();
    std::stringstream ss;
    ss << "delete from tournament_players where tournament_id='"
        << id << "'";

    try
    {
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &error)
    {
        throw;
    }

    index = 0;
    for(it = tournamentPlayers.begin(); it !=tournamentPlayers.end(); ++it)
    {
        unsigned int number = (*it)->getPlayerNumber() + 1;
        (*it)->setPlayerNumber(number);
        try
        {
            (*it)->addToDatabase();
        }
        catch(DatabaseErrorException &error)
        {
            throw;
        }

    }

}

/**
    Den här funktionen lägger till ett särskiljningssystem till turneringen.
    Särskiljningssystemet läggs sist i listan. Om särskiljningssystemet redan finns i listan
    händer ingenting.
*/
void TournamentModel::addTiebreakSystem(TiebreakModel *tiebreakModel)
{
    for(unsigned int index = 0; index < tiebreaks.size(); index++)
    {
        if(*tiebreaks[index] == *tiebreakModel)
        {
            return;
        }
    }

    tiebreaks.push_back(tiebreakModel);

    try
    {
        std::stringstream ss;
        ss << "insert into tournament_tiebreaks(tournament_id, tiebreak_id, tiebreak_order)"
            << " values('" << id << "', '" << tiebreakModel->getID() << "', " << tiebreaks.size()
            << ")";
        Database *database = Database::getInstance();
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
}

/**
    Den här funktionen tar bort ett visst särskiljningssystem från turneringen.
*/
void TournamentModel::removeTiebreakSystem(TiebreakModel *tiebreakModel)
{
    unsigned int index;
    for(index = 0; index < tiebreaks.size(); index++)
    {
        if(tiebreakModel == tiebreaks[index])
        {
            break;
        }
    }
    tiebreaks.erase(tiebreaks.begin() + index);

    try
    {
        Database *database = Database::getInstance();
        std::stringstream deleteSQLSS;
        deleteSQLSS << "delete from tournament_tiebreaks where tournament_id='"
            << this->id.c_str() << "' and tiebreak_id='" << tiebreakModel->getID()
            << "'";
        database->executeSql(deleteSQLSS.str());
        resetTiebreaksOrder();

    }
    catch(const Exception &)
    {
        throw;
    }
}

/**
    Den här funktionen återställer ordningen på turneringens särskiljningssystem.
    Den kan med fördel användas, när ett särskiljningssystem har tagits bort ur containern 'tiebreaks',
    eftersom ordningsnumret i databasen inte längre stämmer.
*/
void TournamentModel::resetTiebreaksOrder() const
{
    try
    {
        Database *database = Database::getInstance();
        for(unsigned int index = 0; index < tiebreaks.size(); index++)
        {
            const unsigned int ORDER_NUMBER = index + 1;
            std::stringstream ss;
            ss << "update tournament_tiebreaks set tiebreak_order=" << ORDER_NUMBER
                << " where tournament_id='" << id << "' and tiebreak_id='" << tiebreaks[index]
                << "'";
            database->executeSql(ss.str());
        }
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }
}

/**
    Den här funktionen returnerar det särskiljningssystem som finns på plats 'index' i listan över
    turneringens särskiljningssystem.
*/
TiebreakModel* TournamentModel::getTiebreak(const unsigned int &index) const
{
    return tiebreaks[index];
}

TournamentPlayerModel* TournamentModel::atIndex(const unsigned int &index) const
{
    unsigned int i = 0;
    for(TournamentPlayerModel *player : tournamentPlayers)
    {
        if(index == i)
        {
            return player;
        }
        i++;
    }

    return nullptr;
}

TournamentPlayerModel* TournamentPlayerModel::clone(ChessplayerModel *chessplayer)
{
    if(chessplayer == nullptr)
    {
        return nullptr;
    }

    TournamentPlayerModel *tournamentPlayer = new TournamentPlayerModel;
    tournamentPlayer->setChessplayerID(chessplayer->getId());
    tournamentPlayer->setPlayerNumber(0);
    return tournamentPlayer;
}

void TournamentPlayerModel::print() const
{
    std::cout << "Id: " << chessplayerID << std::endl
        << "Playernumber: " << playerNumber << std::endl;
}

void TournamentPlayerModel::save() const
{
    std::stringstream ss;
    ss << "update tournament_players set tournament_id='" << tournamentID << "', chessplayer_id="
        << chessplayerID << ", player_number=" << playerNumber;

    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss.str());
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }


}

void TournamentPlayerModel::addToDatabase() const
{
    std::stringstream ss;
    ss << "insert into tournament_players(tournament_id, chessplayer_id, player_number) values('";
    ss << tournamentID << "', " << chessplayerID << ", " << playerNumber << ")";

    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss.str());
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }
}

void TournamentPlayerModel::removeFromDatabase() const
{
    std::stringstream ss;
    ss << "delete from tournament_players where tournament_id='" << tournamentID << "' and "
        << "chessplayer_id='" << chessplayerID << "'";
    try
    {
        Database *database = Database::getInstance();
        database->executeSql(ss.str());
    }
    catch(const DatabaseErrorException &)
    {
        throw;
    }
}

