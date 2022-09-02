#ifndef TABLE_H
#define TABLE_H
#include <wx/grid.h>

/**
    Med hjälp av den här klassen blir det enkelt att skapa en tabell. Klassen ärver xwGrid.

**/
class Table : public wxGrid
{
    public:
        Table(wxWindow *parent, const std::vector<wxString> &columnNames);
        /// Klassen har inga pekare utanför basen av wxWidgets, vilket innebär att destruktorn är tom.
        virtual ~Table() {}
        void setRowCount(const int &rows);

    protected:

    private:
        /// Den här klasskonstanten reglerar det förvalda antalet rader. Alla instanser av den här klassen
        /// använder sig av den här konstanten, när konstruktorn körs.
        const static unsigned int DEFAULT_ROW_COUNT;
        void setColumnName(const unsigned int &columnIndex, const wxString &columName);
        /// Den här klasskonstanten reglerar den förvalda bakgrundsfärgen.
        static const wxColor DEFAULT_BACKGROUND_COLOR;
};

#endif // TABLE_H
