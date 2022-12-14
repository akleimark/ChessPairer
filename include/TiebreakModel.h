#ifndef TIEBREAKMODEL_H
#define TIEBREAKMODEL_H

#include "ModelViewController.h"
/**
    Den h?r modellen hanterar data om ett s?rskiljningssystem.
*/
class TiebreakModel : public Model
{
    public:
        TiebreakModel(const wxString &pID);
        /// Klassen skapar inga objekt med hj?lp av 'new'. Det inneb?r att destruktorn ?r tom.
        virtual ~TiebreakModel() {}
        /// Den h?r funktionen returnerar namnet p? s?rskiljningssystemet.
        wxString getID() const { return id; }
        bool operator==(const TiebreakModel &tiebreakModel);

    protected:

    private:
        /// Namnet p? s?rskiljningssystemet. Det kan exempelvis vara 'Sonneborn-Berger'.
        wxString id;
};

#endif // TIEBREAKMODEL_H
