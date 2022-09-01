#include "TournamentModel.h"
#include "Database.h"
#include "Exception.h"
#include "Defs.h"
#include <iostream>

const unsigned int TournamentModel::MINIMUM_NUMBER_OF_ROUNDS = 1;
const unsigned int TournamentModel::MAXIMUM_NUMBER_OF_ROUNDS = 100;
const std::vector<wxString> TournamentModel::PAIRING_SYSTEMS = {"Monrad", "Berger"};

TournamentModel::TournamentModel():
    id(""), numberOfRounds(0), pairingSystem("")
{

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
    wxString ss;
    ss << "insert into tournaments(id, start_date, end_date, number_of_rounds, pairing_system) values('";
    ss << id << "','" << startDate.getDateString() << "', '" << endDate.getDateString() << "', "
        << numberOfRounds << ",'" << pairingSystem << "')";

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

void TournamentModel::removeFromDatabase() const
{
    wxString ss;
    ss << "delete from tournaments where id='" << id << "'";

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

TournamentPlayerModel& TournamentModel::operator[](const unsigned int &index) const
{
    if(index >= tournamentPlayers.size())
    {
        throw ArgumentErrorException("Illegalt index.");
    }

    return *tournamentPlayers[index];
}


