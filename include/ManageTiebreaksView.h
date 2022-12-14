#ifndef MANAGETIEBREAKSVIEW_H
#define MANAGETIEBREAKSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>
#include "Table.h"
#include "TiebreakModel.h"
#include "ListModel.h"
#include <wx/listbox.h>
#include <wx/button.h>

/**
    I den h?r vyn hanteras alla turneringarnas s?rskiljningssystem.
*/

class ManageTiebreaksView : public View
{
    public:
        ManageTiebreaksView(wxWindow *p_parent);
        virtual ~ManageTiebreaksView() {}
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);

    protected:

    private:
        /// I den h?r instansen av 'wxBoxSizer' visas en comboBox, d?r anv?ndaren v?ljer vilken
        /// av turneringarna som han eller hon vill ?ndra s?rskiljningssytem p?.
        wxBoxSizer *tournamentBox;
        /// Den h?r comboboxen visar alla turneringarna, d?r anv?ndaren kan v?lja bland dessa.
        wxComboBox *tournamentComboBox;
        /// Den h?r instansen av 'wxBoxSizer' visar tv? tabeller med alla tillg?ngliga s?rskiljningssystem,
        /// respektive de s?rskiljningssystem som turneringen till?mpar, samt knappar f?r att l?gga till, respektive
        /// ta bort s?rskiljningssystem fr?n vald turnering.
        wxBoxSizer *bottomSizer;
        /// I den h?r instansen av 'wxBoxSizer' visas tabellen med alla tillg?ngliga s?rskiljningssystem,
        /// samt en knapp f?r att l?gga till valt s?rskiljningssystem till turneringen som f?r n?rvarande ?r vald.
        wxBoxSizer *leftSizer;
        /// I den h?r instansen av 'wxBoxSizer' visas tabellen med de s?rskiljningssystem som ?r aktuella f?r vald turnering,
        /// samt en knapp f?r att ta bort valt s?rskiljningssystem fr?n turneringen som f?r n?rvarande ?r vald.
        wxBoxSizer *rightSizer;
        /// Den h?r tabellen visar alla tillg?ngliga s?rskiljningssystem.
        Table *tiebreaksTable;
        /// Den h?r tabellen visar de s?rskiljningssystem, som f?r n?rvarande g?ller f?r den valda turneringen.
        Table *selectedTiebreaksTable;
        /// Den h?r etiketten visar texten "Tillg?ngliga s?rskiljningssystem'.
        wxStaticText *tiebreaksTableHeader;
        /// Den h?r etiketten visar texten "Valda s?rskiljningssystem'.
        wxStaticText *selectedTiebreaksHeader;
        /// Med hj?lp av den h?r knappen l?gger man till ett s?rskiljningssystem till den valda turneringen.
        wxButton *addButton;
        /// Med hj?lp av den h?r knappen tar man bort ett s?rskiljningssystem fr?n den valda turneringen.
        wxButton *removeButton;
        /// Den h?r funktionen ansvarar f?r att uppdatera tabellen med de tillg?ngliga s?rskiljningssystemen.
        void updateAvailableTiebreaks(ListModel<TiebreakModel*> *model);
        /// Den h?r funktionen ansvarar f?r att uppdatera tabellen med turneringens valda s?rskiljningssystem.
        void updateSelectedTiebreaks(TournamentModel *tournament);
};

#endif // MANAGETIEBREAKSVIEW_H
