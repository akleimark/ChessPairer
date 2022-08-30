#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <wx/string.h>
#include "ChessplayerModel.h"

class TournamentModel
{
    public:
        TournamentModel(const wxString &tId);
        ~TournamentModel() {}
        void setNumberOfRounds(const unsigned int &nRounds) {numberOfRounds = nRounds; }
        void setPairingSystem(const wxString &pSystem) {pairingSystem = pSystem; }
        wxString getId() const { return pairingSystem; }
        unsigned int getNumberOfRounds () const { return numberOfRounds; }
        wxString getPairingSystem() const { return pairingSystem; }


    protected:

    private:
        const wxString id;
        unsigned int numberOfRounds;
        wxString pairingSystem;
        ChessplayerListModel tournamentPlayers;


};

#endif // TOURNAMENT_H
