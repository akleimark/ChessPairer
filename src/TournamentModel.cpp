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


    return true;
}

void TournamentModel::save() const
{

}

void TournamentModel::addToDatabase() const
{
    wxString ss;
    ss << "insert into tournaments(id, number_of_rounds, pairing_system) values('";
    ss << id << "', " << numberOfRounds << ",'" << pairingSystem << "')";

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

}

void TournamentModel::reset()
{
    id = "";
    numberOfRounds = 0;
    pairingSystem = "";
}

void TournamentModel::print() const
{
    std::cout << "Id: " << id << std::endl
        << "Antal ronder: " << numberOfRounds << std::endl
        << "Lottningssystem: " << pairingSystem << std::endl
        << "----------------------------------------------------" << std::endl;
}
