#ifndef TABLE_H
#define TABLE_H
#include <wx/grid.h>

/**
    Med hjälp av den här klassen blir det enkelt att skapa en tabell. Klassen ärver xwGrid.

**/
class Table : public wxGrid
{
    public:
        Table(wxWindow *parent, std::vector<wxString> &columnNames);
        virtual ~Table();
        void setRowCount(const int &rows);

    protected:

    private:
        const static unsigned int DEFAULT_ROW_COUNT;
        void setColumnName(const unsigned int &columnIndex, const wxString &columName);
        int rowCount;

};

#endif // TABLE_H
