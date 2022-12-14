#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <string>
#include "Interfaces.h"
#include <vector>
#include "ModelViewController.h"
/**
    Klassen 'Chessplayer' ?r en modellklass. Den hanterar alla data om schackspelarna. Det r?r sig
    exempelvis om id, f?rnamn, efternamn och klubbtillh?righet. Klassen implementerar gr?nssnitten Validate, Print och DatabaseInterface.
*/
class ChessplayerModel : public Model, public Validate, public Print, public DatabaseInterface, public Reset
{
    public:
        ChessplayerModel();
        ChessplayerModel(const unsigned int &p_id, const wxString &p_firstname, const wxString &p_lastname, const wxString &p_biologicalSex, const wxString &p_birthDate, const wxString &p_federation, const wxString &p_chessclub);

        virtual bool validate() const;
        virtual void print() const;
        /// Med hj?lp av den h?r funktionen st?lls id:et in p? schackspelaren.
        void setID(const unsigned int &p_id) { id = p_id; }
        /// Den h?r funktionen anv?nds f?r att st?lla in f?rnamnet p? schackspelaren.
        void setFirstname(const wxString &p_firstname) { firstname = p_firstname; }
        /// Den h?r funktionen anv?nds f?r att st?lla in efternamnet p? schackspelaren.
        void setLastname(const wxString &p_lastname) { lastname = p_lastname; }
        /// Den h?r funktionen st?ller in schackspelarens biologiska k?n. Med biologiska k?n menas antingen man eller kvinna.
        void setBiologicalSex(const wxString &p_sex) { biologicalSex = p_sex; }
        /// Med hj?lp av den h?r funktionen st?lla schackspelarens f?delsedata in.
        void setBirthDate(const wxString &p_birthDate) { birthDate = p_birthDate; }
        /// Den h?r h?r funktionen st?ller in schackspelarens landstillh?righet.
        void setFederation(const wxString &p_federation) { federation = p_federation; }
        /// Med hj?lp av den h?r funktionen st?lls schackspelarens klubbtillh?righet in.
        void setChessclub(const wxString &p_chessclub) { chessclub = p_chessclub; }

        /// Den h?r funktionen returnerar schackspelarens id.
        unsigned int getId() const { return id; }
        /// Den h?r funktionen returnerar schackspelarens f?rnamn.
        wxString getFirstname() const { return firstname; }
        /// Den h?r funktionen returnerar schackspelarens efternamn.
        wxString getLastname() const { return lastname; }
        /// Den h?r funktionen returnerar schackspelarens fullst?ndiga namn.
        wxString getName() const { return firstname + " " + lastname; }
        /// Den h?r funktionen returnerar schackspelarens biologiska k?n.
        wxString getBiologicalSex() const { return biologicalSex; }
        /// Den h?r funktionen returnerar schackspelarens f?delsedata.
        wxString getBirthDate() const { return birthDate; }
        /// Den h?r funktionen returnerar schackspelarens landstillh?righet.
        wxString getFederation() const { return federation; }
        /// Den h?r funktionen returnerar schackspelarens klubbtillh?righet.
        wxString getChessclub() const { return chessclub; }
        /// Den h?r funktionen returneras schackspelarens f?delse?r.
        unsigned int getBirthYear() const;
        /// Den h?r funktionen returnerar hur m?nga turneringar schackspelaren ?r deltagare i.
        /// En schackspelare kan endast raderas, om denne inte ?r deltagare i n?gon turnering.
        unsigned int getNumberOfTournaments() const;
        // Operator?verlagringar
        bool operator==(const ChessplayerModel &chessplayer);
        bool operator<(const ChessplayerModel &chessplayer) const;

        // Funktioner som implementeras via gr?nssnitten.
        virtual void addToDatabase() const;
        virtual void removeFromDatabase() const;
        virtual void save() const;
        virtual void reset();
        static ChessplayerModel* findById(const unsigned int &playerID);

    protected:

    private:
        /// Den h?r klasskonstanten anger det minsta v?rdet p? spelarens ID.
        const static unsigned int MINIMUM_ID;
        /// Den h?r variabeln h?ller reda p? schackspelarens id.
        unsigned int id;
        /// I den h?r variabeln lagras schackspelarens f?rnamn.
        wxString firstname;
        /// I den h?r variabeln lagras schackspelarens efternamn.
        wxString lastname;
        /// I den h?r variabeln lagras schackspelarens biologiska k?n.
        wxString biologicalSex;
        /// I den h?r variablen lagras schackspelarens f?delsedata.
        wxString birthDate;
        /// I den h?r variabeln lagras schackspelarens landstillh?righet.
        wxString federation;
        /// I den h?r variabeln lagras schackspelarens klubbtillh?righet.
        wxString chessclub;
};

#endif // CHESSPLAYER_H
