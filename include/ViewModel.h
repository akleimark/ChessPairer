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
        void setTournament(TournamentModel *model) { tournamentModel = model; }
        TournamentPlayerModel* getTournamentPlayerModel() const { return tournamentPlayerModel; }
        void setTournamentPlayer(TournamentPlayerModel *model) { tournamentPlayerModel = model; }

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
        ManageTiebreaksViewModel(ListModel<TournamentModel*>*p_tournaments, ListModel<TiebreakModel*> *p_tiebreaks, TournamentModel *tModel, TiebreakModel *tiModel1, TiebreakModel *tiModel2):
            tournaments(p_tournaments), tiebreaks(p_tiebreaks), tournamentModel(tModel), tiebreakModel1(tiModel1), tiebreakModel2(tiModel2) {}
        virtual ~ManageTiebreaksViewModel() {}
        ListModel<TournamentModel*> *getTournaments() const { return tournaments; }
        TournamentModel* getTournament() const { return tournamentModel; }
        ListModel<TiebreakModel*> *getTiebreaks() const { return tiebreaks; }
        TiebreakModel* getFirstTiebreakModel() const { return tiebreakModel1; }
        TiebreakModel* getSecondTiebreakModel() const { return tiebreakModel2; }
        void setTournament(TournamentModel *model) { tournamentModel = model; }
        void setFirstTiebreakModel(TiebreakModel *model) {tiebreakModel1 = model; }
        void setSecondTiebreakModel(TiebreakModel *model) {tiebreakModel2 = model; }

    private:
        ListModel<TournamentModel*>*tournaments;
        ListModel<TiebreakModel*> *tiebreaks;
        TournamentModel *tournamentModel;
        TiebreakModel *tiebreakModel1;
        TiebreakModel *tiebreakModel2;
};


#endif // VIEWMODEL_H
