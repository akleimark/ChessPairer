#ifndef TABLE_H
#define TABLE_H
#include <wx/grid.h>

/**
    Med hj?lp av den h?r klassen blir det enkelt att skapa en tabell. Klassen ?rver xwGrid.

**/
class Table : public wxGrid
{
    public:
        Table(wxWindow *parent, const std::vector<wxString> &columnNames);
        /// Klassen har inga pekare utanf?r basen av wxWidgets, vilket inneb?r att destruktorn ?r tom.
        virtual ~Table() {}
        void setRowCount(const int &rows);

    protected:

    private:
        /// Den h?r klasskonstanten reglerar det f?rvalda antalet rader. Alla instanser av den h?r klassen
        /// anv?nder sig av den h?r konstanten, n?r konstruktorn k?rs.
        const static unsigned int DEFAULT_ROW_COUNT;
        void setColumnName(const unsigned int &columnIndex, const wxString &columName);
        /// Den h?r klasskonstanten reglerar den f?rvalda bakgrundsf?rgen.
        static const wxColor DEFAULT_BACKGROUND_COLOR;
};

#endif // TABLE_H
