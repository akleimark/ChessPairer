#include "ListModel.h"

template <>
void ListModel<ChessplayerModel>::addToContainer()
{
    Database *database = Database::getInstance();
    data.clear();
    for(unsigned int index = 0; index < database->getSize(); index++)
    {
        ChessplayerModel chessplayer;
        chessplayer.setID(wxAtoi(database->atIndex(index, 0)));
        chessplayer.setFirstname(database->atIndex(index, 1));
        chessplayer.setLastname(database->atIndex(index, 2));
        chessplayer.setBiologicalSex(database->atIndex(index, 3));
        chessplayer.setBirthDate(database->atIndex(index, 4));
        chessplayer.setFederation(database->atIndex(index, 5));
        chessplayer.setChessclub(database->atIndex(index, 6));

        data.push_back(chessplayer);
    }
}

template <>
void ListModel<TournamentModel>::addToContainer()
{
    Database *database = Database::getInstance();
    data.clear();
    for(unsigned int index = 0; index < database->getSize(); index++)
    {
        TournamentModel tournamentModel;
        tournamentModel.setID(database->atIndex(index, 0));
        tournamentModel.setNumberOfRounds(wxAtoi(database->atIndex(index, 1)));
        tournamentModel.setPairingSystem(database->atIndex(index, 2));

        data.push_back(tournamentModel);
    }
}