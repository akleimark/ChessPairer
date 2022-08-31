#ifndef TOURNAMENTRESULTMODEL_H
#define TOURNAMENTRESULTMODEL_H

#include "ModelViewController.h"
#include "ChessplayerModel.h"
#include "Defs.h"
#include "TournamentModel.h"

class TournamentResultModel : public Model, public Validate
{
    public:
        TournamentResultModel();
        virtual ~TournamentResultModel();
        TournamentPlayerModel* getWhite() const {return white; }
        TournamentPlayerModel* getBlack() const {return black; }
        wxString getResult() const { return result; }
        void setWhite(TournamentPlayerModel *player) { white = player; }
        void setBlack(TournamentPlayerModel *player) {black = player; }
        virtual bool validate() const;

    protected:

    private:
        TournamentPlayerModel *white;
        TournamentPlayerModel *black;
        wxString result;
};

#endif // TOURNAMENTRESULTMODEL_H
