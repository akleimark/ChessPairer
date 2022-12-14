#include "Table.h"
#include "Exception.h"

const wxColor Table::DEFAULT_BACKGROUND_COLOR = wxColor("Darkblue");

/**
    Varje instans av klassen kommer att skapa en tabell med antalet rader satt till den h?r variabeln.
**/
const unsigned int Table::DEFAULT_ROW_COUNT = 2;

/**
    Den h?r konstruktorn skapar en tabell med hj?lp av en pekare till en instans av wxWindow och en vektor som h?ller
    namnet p? kolumnerna. Varje tabell som skapas med hj?lp av den h?r kontruktorn ?r oredigerbar och anv?ndaren har
    endast m?jlighet att v?lja celler rad f?r rad. Texten i varje cell ?r centrerad.
**/
Table::Table(wxWindow *parent, const std::vector<wxString> &columnNames):
    wxGrid(parent, wxID_ANY)
{
    this->CreateGrid(DEFAULT_ROW_COUNT, columnNames.size());
    for(unsigned int index = 0; index < columnNames.size(); index++)
    {
         this->setColumnName(index, columnNames[index]);
    }

    this->EnableEditing(false);
    for(unsigned int row = 0; row < DEFAULT_ROW_COUNT; row++)
    {
        for(unsigned int col = 0; col < columnNames.size(); col++)
        {
            this->SetCellAlignment(row, col, wxALIGN_CENTER, wxALIGN_CENTER);
        }
    }

    this->SetSelectionMode(wxGrid::wxGridSelectRows);
    this->SetSelectionBackground(DEFAULT_BACKGROUND_COLOR);
}

/**
    Med hj?lp av den h?r funktionen s?tts namnet p? kolumnen med ett visst index.
**/
void Table::setColumnName(const unsigned int &columnIndex, const wxString &columName)
{
    this->SetColLabelValue(columnIndex, columName);
}

/**
    Med hj?lp av den h?r funktionen ?ndras antalet rader i tabellen.
*/
void Table::setRowCount(const int &rows)
{
    if(rows < 0)
    {
        throw ArgumentErrorException("Felaktigt radnummer. ");
    }

    while(this->GetNumberRows() < rows)
    {
        this->AppendRows();
    }

    for(unsigned int row = 0; row < this->GetNumberRows(); row++)
    {
        for(unsigned int col = 0; col < this->GetNumberCols(); col++)
        {
            this->SetCellAlignment(row, col, wxALIGN_CENTER, wxALIGN_CENTER);
        }
    }
}
