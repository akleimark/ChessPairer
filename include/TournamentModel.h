#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <wx/string.h>
#include "ChessplayerModel.h"

/**
    Den här klassen har hand om alla data, som rör turneringar. Varje turnering har bland annat ett unikt ID. Andra data som
    lagras är antalet ronder och namnet på lottningssystemet. Vidare finns det naturligtvis information om vilka spelare som ingår
    i turneringen och de resultat som dessa spelare har uppnått i turneringen.
*/
class TournamentPlayerModel;
class TournamentModel : public Model, public Reset, public Validate, public DatabaseInterface, public Print
{
    public:
        TournamentModel();
        ~TournamentModel() {}
        /// Den här funktionen sätter turneringens unika ID, som är en textsträng.
        void setID(const wxString &tID) {id = tID; }
        /// Med hjälp av den här funktionen ställs antalet ronder i turneringen in.
        void setNumberOfRounds(const unsigned int &nRounds) {numberOfRounds = nRounds; }
        /// Den här funktionen ansvarar för att ställa in namnet på lottningssystemet.
        void setPairingSystem(const wxString &pSystem) {pairingSystem = pSystem; }
        /// Den här funktionen returnerar turneringens unika ID.
        wxString getId() const { return id; }
        /// Med hjälp av den här funktionen fås antalet ronder som skall spelas i turneringen.
        unsigned int getNumberOfRounds () const { return numberOfRounds; }
        /// Den här funktionen ger namnet på det lottningssystem, som turneringen tillämpar.
        wxString getPairingSystem() const { return pairingSystem; }
        // Gränssnitt
        virtual bool validate() const;
        virtual void save() const;
        virtual void addToDatabase() const;
        virtual void removeFromDatabase() const;
        virtual void reset();
        virtual void print() const;

    protected:

    private:
        /// Den här variabeln lagrar turneringens unika ID (en textsträng).
        wxString id;
        /// Den här variabeln lagrar antalet ronder i turneringen.
        unsigned int numberOfRounds;
        /// Den här variabeln agrar namnet på det lottningssystem, som turneringen tillämpar.
        wxString pairingSystem;

        std::vector<TournamentPlayerModel*> tournamentPlayers;

        // Klasskonstanter
        const static unsigned int MINIMUM_NUMBER_OF_ROUNDS;
        const static unsigned int MAXIMUM_NUMBER_OF_ROUNDS;
        const static std::vector<wxString> PAIRING_SYSTEMS;

        //Operatoröverlagringar
        TournamentPlayerModel& operator[](const unsigned int &index) const;
};
/**
    Den här klassen är till för att hantera turneringsspelare.
    Klassen har två privata variabler (chessplayerID och playerNumber). I många lottningssystem
    lottar man med hjälp av ett spelarnummer.
*/
class TournamentPlayerModel : public Model
{
    public:
        TournamentPlayerModel():
            chessplayerID(0), playerNumber(0) {}
        virtual ~TournamentPlayerModel() {}
        void setPlayerNumber(const unsigned int &number) {playerNumber = number; }
        void setChessplayerID(const unsigned int &id) {chessplayerID = id; }
        /// Den här funktionen returnerar 'chessplayerID'.
        unsigned int getChessplayerID() const { return chessplayerID; }
        /// Den här funktionen returnerar spelarnumret.
        unsigned int getPlayerNumber() const { return playerNumber; }

    private:
        /// Värdet på den här variabeln är samma som för motsvarande schackspelar-id.
        unsigned int chessplayerID;
        /// Det här är det nummer som spelaren har i turneringen i fråga.
        unsigned int playerNumber;
};


#endif // TOURNAMENT_H
