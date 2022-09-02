#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <wx/string.h>
#include "ChessplayerModel.h"
#include "Misc.h"

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
        /// Klassen använder sig inte av några egna pekare, varpå destruktorn är tom.
        virtual ~TournamentModel() {}
        /// Den här funktionen sätter turneringens unika ID, som är en textsträng.
        void setID(const wxString &tID) {id = tID; }
        /// Med hjälp av den här funktionen ställs antalet ronder i turneringen in.
        void setNumberOfRounds(const unsigned int &nRounds) {numberOfRounds = nRounds; }
        /// Den här funktionen ansvarar för att ställa in namnet på lottningssystemet.
        void setPairingSystem(const wxString &pSystem) {pairingSystem = pSystem; }
        /// Med hjälp av den här funktionen ställs startdatumet för turneringen in.
        void setStartDate(const wxString &date) {startDate.setDateString(date); }
        /// Med hjälp av den här funktionen ställs turneringens slutdatum in.
        void setEndDate(const wxString &date) {endDate.setDateString(date); }

        /// Den här funktionen returnerar turneringens unika ID.
        wxString getId() const { return id; }
        /// Med hjälp av den här funktionen fås antalet ronder som skall spelas i turneringen.
        unsigned int getNumberOfRounds () const { return numberOfRounds; }
        /// Den här funktionen ger namnet på det lottningssystem, som turneringen tillämpar.
        wxString getPairingSystem() const { return pairingSystem; }
        /// Den här funktionen returnerar det startdatum, som turneringen använder sig av (en instans av klassen 'Date').
        Date getStartDate() const { return startDate; }
        /// Den här funktionen returnerar det slutdatum, som turneringen använder sig av (en instans av klassen 'Date').
        Date getEndDate() const { return endDate; }
        /// Den här funktionen används för att hämta alla turneringesspelarna från databasen och sedan placera dem i containern 'tournamentPlayers'.
        void getAllTournamentPlayers();
        /// Den här funktionen returnerar en pekare till den turneringsspelare, som befinner sig på plats 'index' i containern 'tournamentPlayers'.
        TournamentPlayerModel* atIndex(const unsigned int index) const;
        void addTournamentPlayer(TournamentPlayerModel *player);

        /// Den här funktionen returnerar antalet spelare som finns i turneringen.
        unsigned int getNumberOfPlayers() const { return tournamentPlayers.size(); }

        // Funktioner som implementeras via gränssnitt
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
        /// Startdatumet för turneringen.
        Date startDate;
        /// Slutdatumet för turneringen.
        Date endDate;
        /// I den här containern läggs alla turneringsspelarna in.
        std::set<TournamentPlayerModel*> tournamentPlayers;
        /// Med hjälp av den här funktionen kan alla turneringsspelarna raderas och frigöras från minnet.
        void clearTournamentPlayers();

        // Klasskonstanter
        /// Den här konstanten reglerar det minsta antalet ronder i en turnering.
        const static unsigned int MINIMUM_NUMBER_OF_ROUNDS;
        /// Den här konstanten reglerar det maximala antalet ronder i en turnering.
        const static unsigned int MAXIMUM_NUMBER_OF_ROUNDS;
        /// I den här vektorn lagras de lottningssystem, som är möjliga att använda i ChessPairer.
        const static std::vector<wxString> PAIRING_SYSTEMS;
};
/**
    Den här klassen är till för att hantera turneringsspelare.
    Klassen har två privata variabler (chessplayerID och playerNumber). I många lottningssystem
    lottar man med hjälp av ett spelarnummer.
*/
class TournamentPlayerModel : public Model, public Print, public DatabaseInterface
{
    public:
        /// I den förvalda konstruktorn ställs turneringens id, id:et på schackspelaren och det spelarnummer som gäller.
        TournamentPlayerModel(const wxString &tID = "", const unsigned int &cID = 0, const unsigned int &pNumber = 0):
            tournamentID(tID), chessplayerID(cID), playerNumber(pNumber) {}
        /// I klassen finns inga egna pekare, vilket gör att implementationen av destruktorn är tom.
        virtual ~TournamentPlayerModel() {}
        /// Med hjälp av den här funktionen ställs spelarnumret in.
        void setPlayerNumber(const unsigned int &number) {playerNumber = number; }
        /// Den här funktionen används för att ställa in id:et på schackspelaren. Det är identiskt med FIDE:id för schackspelaren.
        void setChessplayerID(const unsigned int &id) {chessplayerID = id; }
        /// Den här funktionen returnerar 'chessplayerID'.
        unsigned int getChessplayerID() const { return chessplayerID; }
        /// Den här funktionen returnerar spelarnumret.
        unsigned int getPlayerNumber() const { return playerNumber; }
        /// Den här funktionen kopierar de gemensamma variablerna mellan ChessplayerModel och TournamentPlayerModel och returnerar en ny instans av klassen.
        static TournamentPlayerModel* clone(ChessplayerModel *chessplayer);
        // Funktioner som implementeras via gränssnitt.
        /// Den här funktionen skriver ut enkla, basala saker om klassen till konsolen.
        virtual void print() const;
        virtual void save() const;

        virtual void addToDatabase() const;
        virtual void removeFromDatabase() const;
        /// Den här funktionen används för att ställa in det turnerings-id som gäller.
        void setTournamentID(const wxString &tID) { tournamentID = tID; }

    private:
        /// Turneringens id.
        wxString tournamentID;
        /// Värdet på den här variabeln är samma som för motsvarande schackspelar-id.
        unsigned int chessplayerID;
        /// Det här är det nummer som spelaren har i turneringen i fråga.
        unsigned int playerNumber;
};

#endif // TOURNAMENT_H
