#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <string>
#include "Interfaces.h"
#include <vector>
#include "ModelViewController.h"
/**
    Klassen 'Chessplayer' är en modellklass. Den hanterar alla data om schackspelarna. Det rör sig
    exempelvis om id, förnamn, efternamn och klubbtillhörighet. Klassen implementerar gränssnitten Validate, Print och DatabaseInterface.
*/
class ChessplayerModel : public Model, public Validate, public Print, public DatabaseInterface, public Reset
{
    public:
        ChessplayerModel();
        ChessplayerModel(const unsigned int &p_id, const wxString &p_firstname, const wxString &p_lastname, const wxString &p_biologicalSex, const wxString &p_birthDate, const wxString &p_federation, const wxString &p_chessclub);

        virtual bool validate() const;
        virtual void print() const;
        /// Med hjälp av den här funktionen ställs id:et in på schackspelaren.
        void setID(const unsigned int &p_id) { id = p_id; }
        /// Den här funktionen används för att ställa in förnamnet på schackspelaren.
        void setFirstname(const wxString &p_firstname) { firstname = p_firstname; }
        /// Den här funktionen används för att ställa in efternamnet på schackspelaren.
        void setLastname(const wxString &p_lastname) { lastname = p_lastname; }
        /// Den här funktionen ställer in schackspelarens biologiska kön. Med biologiska kön menas antingen man eller kvinna.
        void setBiologicalSex(const wxString &p_sex) { biologicalSex = p_sex; }
        /// Med hjälp av den här funktionen ställa schackspelarens födelsedata in.
        void setBirthDate(const wxString &p_birthDate) { birthDate = p_birthDate; }
        /// Den här här funktionen ställer in schackspelarens landstillhörighet.
        void setFederation(const wxString &p_federation) { federation = p_federation; }
        /// Med hjälp av den här funktionen ställs schackspelarens klubbtillhörighet in.
        void setChessclub(const wxString &p_chessclub) { chessclub = p_chessclub; }

        /// Den här funktionen returnerar schackspelarens id.
        unsigned int getId() const { return id; }
        /// Den här funktionen returnerar schackspelarens förnamn.
        wxString getFirstname() const { return firstname; }
        /// Den här funktionen returnerar schackspelarens efternamn.
        wxString getLastname() const { return lastname; }
        /// Den här funktionen returnerar schackspelarens fullständiga namn.
        wxString getName() const { return firstname + " " + lastname; }
        /// Den här funktionen returnerar schackspelarens biologiska kön.
        wxString getBiologicalSex() const { return biologicalSex; }
        /// Den här funktionen returnerar schackspelarens födelsedata.
        wxString getBirthDate() const { return birthDate; }
        /// Den här funktionen returnerar schackspelarens landstillhörighet.
        wxString getFederation() const { return federation; }
        /// Den här funktionen returnerar schackspelarens klubbtillhörighet.
        wxString getChessclub() const { return chessclub; }

        unsigned int getBirthYear() const;

        // Operatoröverlagringar
        bool operator==(const ChessplayerModel &chessplayer);
        bool operator<(const ChessplayerModel &chessplayer) const;

        // Funktioner som implementeras via gränssnitten.
        virtual void addToDatabase() const;
        virtual void removeFromDatabase() const;
        virtual void save() const;
        virtual void reset();
        static ChessplayerModel* findById(const unsigned int &playerID);

    protected:

    private:
        /// Den här klasskonstanten anger det minsta värdet på spelarens ID.
        const static unsigned int MINIMUM_FIDE_ID;
        /// Den här variabeln håller reda på schackspelarens id.
        unsigned int id;
        /// I den här variabeln lagras schackspelarens förnamn.
        wxString firstname;
        /// I den här variabeln lagras schackspelarens efternamn.
        wxString lastname;
        /// I den här variabeln lagras schackspelarens biologiska kön.
        wxString biologicalSex;
        /// I den här variablen lagras schackspelarens födelsedata.
        wxString birthDate;
        /// I den här variabeln lagras schackspelarens landstillhörighet.
        wxString federation;
        /// I den här variabeln lagras schackspelarens klubbtillhörighet.
        wxString chessclub;
};

#endif // CHESSPLAYER_H
