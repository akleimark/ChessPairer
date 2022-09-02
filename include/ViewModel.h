#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "ListModel.h"
#include "TournamentModel.h"

class ManageTournamentPlayersViewModel : public Model
{
    public:
        ManageTournamentPlayersViewModel(ListModel<TournamentModel*> *_tournaments, ListModel<ChessplayerModel*> *players, TournamentModel *tModel, TournamentPlayerModel *tpModel):
            tournaments(_tournaments), chessplayers(players), tournamentModel(tModel), tournamentPlayerModel(tpModel) {}
        virtual ~ManageTournamentPlayersViewModel() {}
        ListModel<TournamentModel*> *getTournaments() const { return tournaments; }
        ListModel<ChessplayerModel*> *getChessplayerList() const { return chessplayers; }
        TournamentModel* getTournamentModel() const { return tournamentModel; }
        void tournament(TournamentModel *model) { tournamentModel = model; }
        TournamentPlayerModel* getTournamentPlayerModel() const { return tournamentPlayerModel; }
        void tournamentPlayer(TournamentPlayerModel *model) { tournamentPlayerModel = model; }

    protected:

    private:
        ListModel<TournamentModel*> *tournaments;
        ListModel<ChessplayerModel*> *chessplayers;
        TournamentModel *tournamentModel;
        TournamentPlayerModel *tournamentPlayerModel;

};

#endif // VIEWMODEL_H
