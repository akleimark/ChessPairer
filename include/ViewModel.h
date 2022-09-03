#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "ListModel.h"
#include "TournamentModel.h"
#include "TiebreakModel.h"

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

class ManageTiebreaksViewModel : public Model
{
    public:
        ManageTiebreaksViewModel(ListModel<TournamentModel*>*p_tournaments, ListModel<TiebreakModel*> *p_tiebreaks, TournamentModel *tModel):
            tournaments(p_tournaments), tiebreaks(p_tiebreaks), tournamentModel(tModel) {}
        virtual ~ManageTiebreaksViewModel() {}
        ListModel<TournamentModel*> *getListModel() const { return tournaments; }
        TournamentModel* getTournament() const { return tournamentModel; }
        ListModel<TiebreakModel*> *getTiebreaks() const { return tiebreaks; }



    private:
        ListModel<TournamentModel*>*tournaments;
        ListModel<TiebreakModel*> *tiebreaks;
        TournamentModel *tournamentModel;



};


#endif // VIEWMODEL_H
