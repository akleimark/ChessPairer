#include "ListModel.h"
#include "TiebreakModel.h"

template <>
void ListModel<ChessplayerModel*>::addToContainer()
{
    Database *database = Database::getInstance();
    data.clear();
    for(unsigned int index = 0; index < database->getSize(); index++)
    {
        ChessplayerModel *chessplayer = new ChessplayerModel;
        chessplayer->setID(wxAtoi(database->atIndex(index, 0)));
        chessplayer->setFirstname(database->atIndex(index, 1));
        chessplayer->setLastname(database->atIndex(index, 2));
        chessplayer->setBiologicalSex(database->atIndex(index, 3));
        chessplayer->setBirthDate(database->atIndex(index, 4));
        chessplayer->setFederation(database->atIndex(index, 5));
        chessplayer->setChessclub(database->atIndex(index, 6));

        data.push_back(chessplayer);
    }
}

template <>
void ListModel<TournamentModel*>::addToContainer()
{
    Database *database = Database::getInstance();
    data.clear();
    for(unsigned int index = 0; index < database->getSize(); index++)
    {
        TournamentModel *tournamentModel = new TournamentModel;
        tournamentModel->setID(database->atIndex(index, 0));
        tournamentModel->setStartDate(database->atIndex(index, 1));
        tournamentModel->setEndDate(database->atIndex(index, 2));
        tournamentModel->setNumberOfRounds(wxAtoi(database->atIndex(index, 3)));
        tournamentModel->setPairingSystem(database->atIndex(index, 4));

        data.push_back(tournamentModel);
    }
}

template <>
void ListModel<TiebreakModel*>::addToContainer()
{
    Database *database = Database::getInstance();
    data.clear();
    for(unsigned int index = 0; index < database->getSize(); index++)
    {
        TiebreakModel *tiebreak = new TiebreakModel(database->atIndex(index, 0));
        data.push_back(tiebreak);
    }
}


template <>
void ListModel<ChessplayerModel*>::getAll()
{
    Database *database = Database::getInstance();
    std::stringstream ss;
    ss << "select * from chessplayers order by id";

    try
    {
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
     addToContainer();
}

template <>
void ListModel<TournamentModel*>::getAll()
{
    Database *database = Database::getInstance();
    std::stringstream ss;
    ss << "select * from tournaments order by id";

    try
    {
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
     addToContainer();
}

template <>
void ListModel<TiebreakModel*>::getAll()
{
    Database *database = Database::getInstance();
    std::stringstream ss;
    ss << "select * from tiebreaks order by id";

    try
    {
        database->executeSql(ss.str());
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }
     addToContainer();
}


