#include "Table.h"
#include "Exception.h"


/**
    Varje instans av klassen kommer att skapa en tabell med antalet rader satt till den här variabeln.
**/
const unsigned int Table::DEFAULT_ROW_COUNT = 2;

/**
    Den här konstruktorn skapar en tabell med hjälp av en pekare till en instans av wxWindow och en vektor som håller
    namnet på kolumnerna. Varje tabell som skapas med hjälp av den här kontruktorn är oredigerbar och användaren har
    endast möjlighet att välja celler rad för rad. Texten i varje cell är centrerad.
**/
Table::Table(wxWindow *parent, std::vector<wxString> &columnNames):
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
}

Table::~Table()
{

}

/**
    Med hjälp av den här funktionen sätts namnet på kolumnen med ett visst index.
**/
void Table::setColumnName(const unsigned int &columnIndex, const wxString &columName)
{
    this->SetColLabelValue(columnIndex, columName);
}

/**
    Med hjälp av den här funktionen ändras antalet rader i tabellen.
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


