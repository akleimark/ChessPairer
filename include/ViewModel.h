#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "ListModel.h"
#include "TournamentModel.h"

class ManageTournamentPlayersViewModel : public Model
{
    public:
        ManageTournamentPlayersViewModel(ListModel<TournamentModel> &_tournaments, ListModel<ChessplayerModel> &players):
            tournaments(_tournaments), chessplayers(players) {}
        virtual ~ManageTournamentPlayersViewModel() {}
        ListModel<TournamentModel>& getTournaments() const { return tournaments; }
        ListModel<ChessplayerModel>& getChessplayerList() const { return chessplayers; }


    protected:

    private:
        ListModel<TournamentModel> &tournaments;
        ListModel<ChessplayerModel> &chessplayers;

};

#endif // VIEWMODEL_H
