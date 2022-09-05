#ifndef TIEBREAKMODEL_H
#define TIEBREAKMODEL_H

#include "ModelViewController.h"
/**
    Den här modellen hanterar data om ett särskiljningssystem.
*/
class TiebreakModel : public Model
{
    public:
        TiebreakModel(const wxString &pID);
        /// Klassen skapar inga objekt med hjälp av 'new'. Det innebär att destruktorn är tom.
        virtual ~TiebreakModel() {}
        /// Den här funktionen returnerar namnet på särskiljningssystemet.
        wxString getID() const { return id; }
        bool operator==(const TiebreakModel &tiebreakModel);

    protected:

    private:
        /// Namnet på särskiljningssystemet. Det kan exempelvis vara 'Sonneborn-Berger'.
        wxString id;
};

#endif // TIEBREAKMODEL_H
