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
    I den här vyn hanteras alla turneringarnas särskiljningssystem.
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
        /// I den här instansen av 'wxBoxSizer' visas en comboBox, där användaren väljer vilken
        /// av turneringarna som han eller hon vill ändra särskiljningssytem på.
        wxBoxSizer *tournamentBox;
        /// Den här comboboxen visar alla turneringarna, där användaren kan välja bland dessa.
        wxComboBox *tournamentComboBox;
        /// Den här instansen av 'wxBoxSizer' visar två tabeller med alla tillgängliga särskiljningssystem,
        /// respektive de särskiljningssystem som turneringen tillämpar, samt knappar för att lägga till, respektive
        /// ta bort särskiljningssystem från vald turnering.
        wxBoxSizer *bottomSizer;
        /// I den här instansen av 'wxBoxSizer' visas tabellen med alla tillgängliga särskiljningssystem,
        /// samt en knapp för att lägga till valt särskiljningssystem till turneringen som för närvarande är vald.
        wxBoxSizer *leftSizer;
        /// I den här instansen av 'wxBoxSizer' visas tabellen med de särskiljningssystem som är aktuella för vald turnering,
        /// samt en knapp för att ta bort valt särskiljningssystem från turneringen som för närvarande är vald.
        wxBoxSizer *rightSizer;
        /// Den här tabellen visar alla tillgängliga särskiljningssystem.
        Table *tiebreaksTable;
        /// Den här tabellen visar de särskiljningssystem, som för närvarande gäller för den valda turneringen.
        Table *selectedTiebreaksTable;
        /// Den här etiketten visar texten "Tillgängliga särskiljningssystem'.
        wxStaticText *tiebreaksTableHeader;
        /// Den här etiketten visar texten "Valda särskiljningssystem'.
        wxStaticText *selectedTiebreaksHeader;
        /// Med hjälp av den här knappen lägger man till ett särskiljningssystem till den valda turneringen.
        wxButton *addButton;
        /// Med hjälp av den här knappen tar man bort ett särskiljningssystem från den valda turneringen.
        wxButton *removeButton;
        void updateTiebreaks(ListModel<TiebreakModel*> *model);
};

#endif // MANAGETIEBREAKSVIEW_H
