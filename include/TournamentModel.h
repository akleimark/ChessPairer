#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <wx/string.h>
#include "ChessplayerModel.h"

/**
    Den h�r klassen har hand om alla data, som r�r turneringar. Varje turnering har bland annat ett unikt ID. Andra data som
    lagras �r antalet ronder och namnet p� lottningssystemet. Vidare finns det naturligtvis information om vilka spelare som ing�r
    i turneringen och de resultat som dessa spelare har uppn�tt i turneringen.
*/
class TournamentModel
{
    public:
        TournamentModel();
        ~TournamentModel() {}
        /// Den h�r funktionen s�tter turneringens unika ID, som �r en textstr�ng.
        void setID(const wxString &tID) {id = tID; }
        /// Med hj�lp av den h�r funktionen st�lls antalet ronder i turneringen in.
        void setNumberOfRounds(const unsigned int &nRounds) {numberOfRounds = nRounds; }
        /// Den h�r funktionen ansvarar f�r att st�lla in namnet p� lottningssystemet.
        void setPairingSystem(const wxString &pSystem) {pairingSystem = pSystem; }
        /// Den h�r funktionen returnerar turneringens unika ID.
        wxString getId() const { return pairingSystem; }
        /// Med hj�lp av den h�r funktionen f�s antalet ronder som skall spelas i turneringen.
        unsigned int getNumberOfRounds () const { return numberOfRounds; }
        /// Den h�r funktionen ger namnet p� det lottningssystem, som turneringen till�mpar.
        wxString getPairingSystem() const { return pairingSystem; }


    protected:

    private:
        /// Den h�r variabeln lagrar turneringens unika ID (en textstr�ng).
        wxString id;
        /// Den h�r variabeln lagrar antalet ronder i turneringen.
        unsigned int numberOfRounds;
        /// Den h�r variabeln agrar namnet p� det lottningssystem, som turneringen till�mpar.
        wxString pairingSystem;
};



#endif // TOURNAMENT_H