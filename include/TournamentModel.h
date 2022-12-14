#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <wx/string.h>
#include "ChessplayerModel.h"
#include "Misc.h"
#include "TiebreakModel.h"

/**
    Den h?r klassen har hand om alla data, som r?r turneringar. Varje turnering har bland annat ett unikt ID. Andra data som
    lagras ?r antalet ronder och namnet p? lottningssystemet. Vidare finns det naturligtvis information om vilka spelare som ing?r
    i turneringen och de resultat som dessa spelare har uppn?tt i turneringen.
*/
class TournamentPlayerModel;
class TournamentModel : public Model, public Reset, public Validate, public DatabaseInterface, public Print
{
    public:
        TournamentModel();
        virtual ~TournamentModel();
        /// Den h?r funktionen s?tter turneringens unika ID, som ?r en textstr?ng.
        void setID(const wxString &tID) {id = tID; }
        /// Med hj?lp av den h?r funktionen st?lls antalet ronder i turneringen in.
        void setNumberOfRounds(const unsigned int &nRounds) {numberOfRounds = nRounds; }
        /// Den h?r funktionen ansvarar f?r att st?lla in namnet p? lottningssystemet.
        void setPairingSystem(const wxString &pSystem) {pairingSystem = pSystem; }
        /// Med hj?lp av den h?r funktionen st?lls startdatumet f?r turneringen in.
        void setStartDate(const wxString &date) {startDate.setDateString(date); }
        /// Med hj?lp av den h?r funktionen st?lls turneringens slutdatum in.
        void setEndDate(const wxString &date) {endDate.setDateString(date); }

        /// Den h?r funktionen returnerar turneringens unika ID.
        wxString getId() const { return id; }
        /// Med hj?lp av den h?r funktionen f?s antalet ronder som skall spelas i turneringen.
        unsigned int getNumberOfRounds () const { return numberOfRounds; }
        /// Den h?r funktionen ger namnet p? det lottningssystem, som turneringen till?mpar.
        wxString getPairingSystem() const { return pairingSystem; }
        /// Den h?r funktionen returnerar det startdatum, som turneringen anv?nder sig av (en instans av klassen 'Date').
        Date getStartDate() const { return startDate; }
        /// Den h?r funktionen returnerar det slutdatum, som turneringen anv?nder sig av (en instans av klassen 'Date').
        Date getEndDate() const { return endDate; }
        /// Den h?r funktionen anv?nds f?r att h?mta alla turneringesspelarna fr?n databasen och sedan placera dem i containern 'tournamentPlayers'.
        void getAllTournamentPlayers();
        void getAllTiebreaks();
        /// Den h?r funktionen returnerar en pekare till den turneringsspelare, som befinner sig p? plats 'index' i containern 'tournamentPlayers'.
        TournamentPlayerModel* atIndex(const unsigned int &index) const;
        TiebreakModel* getTiebreak(const unsigned int &index) const;
        unsigned int getNumberOfTiebreaks() const { return tiebreaks.size(); }
        void addTournamentPlayer(TournamentPlayerModel *player);
        void removeTournamentPlayer(TournamentPlayerModel *player);
        /// Den h?r funktionen returnerar antalet spelare som finns i turneringen.
        unsigned int getNumberOfPlayers() const { return tournamentPlayers.size(); }
        /// Den h?r funktionen skapar nya inlottningsnummer f?r spelarna i turneringen.
        void generatePlayerNumbers();
        void addTiebreakSystem(TiebreakModel *tiebreakModel);
        void removeTiebreakSystem(TiebreakModel *tiebreakModel);

        // Funktioner som implementeras via gr?nssnitt
        virtual bool validate() const;
        virtual void save() const;
        virtual void addToDatabase() const;
        virtual void removeFromDatabase() const;
        virtual void reset();
        virtual void print() const;

    protected:

    private:
        /// Den h?r variabeln lagrar turneringens unika ID (en textstr?ng).
        wxString id;
        /// Den h?r variabeln lagrar antalet ronder i turneringen.
        unsigned int numberOfRounds;
        /// Den h?r variabeln agrar namnet p? det lottningssystem, som turneringen till?mpar.
        wxString pairingSystem;
        /// Startdatumet f?r turneringen.
        Date startDate;
        /// Slutdatumet f?r turneringen.
        Date endDate;
        /// I den h?r containern l?ggs alla turneringsspelarna in.
        std::set<TournamentPlayerModel*> tournamentPlayers;
        /// I den h?r containern l?ggs alla s?rkiljningssystem som turneringen anv?nder sig av in.
        /// Containern ?r sorterad efter den ordning som s?rskiljningssystemen anv?nds.
        std::vector<TiebreakModel*> tiebreaks;

        /// Med hj?lp av den h?r funktionen kan alla turneringsspelarna raderas och frig?ras fr?n minnet.
        void clearTournamentPlayers();
        /// Med hj?lp av den h?r funktionen kan alla turneringens s?rskiljningssystem raderas och frig?ras fr?n minnet.
        void clearTournamentTiebreaks();
        void resetTiebreaksOrder() const;

        // Klasskonstanter
        /// Den h?r konstanten reglerar det minsta antalet ronder i en turnering.
        const static unsigned int MINIMUM_NUMBER_OF_ROUNDS;
        /// Den h?r konstanten reglerar det maximala antalet ronder i en turnering.
        const static unsigned int MAXIMUM_NUMBER_OF_ROUNDS;
        /// I den h?r vektorn lagras de lottningssystem, som ?r m?jliga att anv?nda i ChessPairer.
        const static std::vector<wxString> PAIRING_SYSTEMS;
};
/**
    Den h?r klassen ?r till f?r att hantera turneringsspelare.
    Klassen har tv? privata variabler (chessplayerID och playerNumber). I m?nga lottningssystem
    lottar man med hj?lp av ett spelarnummer.
*/
class TournamentPlayerModel : public Model, public Print, public DatabaseInterface
{
    public:
        /// I den f?rvalda konstruktorn st?lls turneringens id, id:et p? schackspelaren och det spelarnummer som g?ller.
        TournamentPlayerModel(const wxString &tID = "", const unsigned int &cID = 0, const unsigned int &pNumber = 0):
            tournamentID(tID), chessplayerID(cID), playerNumber(pNumber) {}
        /// I klassen finns inga egna pekare, vilket g?r att implementationen av destruktorn ?r tom.
        virtual ~TournamentPlayerModel() {}
        /// Med hj?lp av den h?r funktionen st?lls spelarnumret in.
        void setPlayerNumber(const unsigned int &number) {playerNumber = number; }
        /// Den h?r funktionen anv?nds f?r att st?lla in id:et p? schackspelaren. Det ?r identiskt med FIDE:id f?r schackspelaren.
        void setChessplayerID(const unsigned int &id) {chessplayerID = id; }
        /// Den h?r funktionen returnerar 'chessplayerID'.
        unsigned int getChessplayerID() const { return chessplayerID; }
        /// Den h?r funktionen returnerar spelarnumret.
        unsigned int getPlayerNumber() const { return playerNumber; }
        /// Den h?r funktionen kopierar de gemensamma variablerna mellan ChessplayerModel och TournamentPlayerModel och returnerar en ny instans av klassen.
        static TournamentPlayerModel* clone(ChessplayerModel *chessplayer);
        // Funktioner som implementeras via gr?nssnitt.
        /// Den h?r funktionen skriver ut enkla, basala saker om klassen till konsolen.
        virtual void print() const;
        virtual void save() const;

        virtual void addToDatabase() const;
        virtual void removeFromDatabase() const;
        /// Den h?r funktionen anv?nds f?r att st?lla in det turnerings-id som g?ller.
        void setTournamentID(const wxString &tID) { tournamentID = tID; }

    private:
        /// Turneringens id.
        wxString tournamentID;
        /// V?rdet p? den h?r variabeln ?r samma som f?r motsvarande schackspelar-id.
        unsigned int chessplayerID;
        /// Det h?r ?r det nummer som spelaren har i turneringen i fr?ga.
        unsigned int playerNumber;
};

#endif // TOURNAMENT_H
