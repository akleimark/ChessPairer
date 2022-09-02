#include "Misc.h"
#include "Defs.h"
#include "Exception.h"
#include <wx/wxchar.h>

const unsigned int Date::MINIMUM_YEAR = 1900;
const unsigned int Date::MAXIMUM_YEAR = 2100;

/**
    Den förvalda konstruktorn skapar en instans av klassen med hjälp
    av dagens datum. De privata variablerna ställs in därefter.
*/
Date::Date()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
}

/**
    Den här konstruktorn tar argument för år, månad och dag.
*/
Date::Date(const unsigned int &_year, const unsigned int &_month, const unsigned int &_day):
    year(_year), month(_month), day(_day)
{

}

/**
    Den här funktionen returnerar ett heltal med det nuvarande året.
*/
unsigned int Date::currentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}

/**
    Den här funktionen returnerar huruvida ett givet år är skottår eller ej.
    Exempelvis ger isLeapYear(1905) false, medan isLeapYear(2020) true.
*/
bool Date::isLeapYear() const
{
    if(year % 100 != 0)
    {
        if(year % 4 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(year % 400 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
    Den här funktionen kontrollerar, huruvida datumet är korrekt eller ej.
    Om det är korrekt, returneras 'true'.
*/
bool Date::validate() const
{
    if(year < Date::MINIMUM_YEAR || year > Date::MAXIMUM_YEAR)
    {
        return false;
    }

    if(month < 1 || month > 12)
    {
        return false;
    }

    unsigned int maxDay;
    switch(month)
    {
        case 1:
        {
            maxDay = 31;
            break;
        }
        case 2:
        {
            maxDay = 28;
            break;
        }
        case 3:
        {
            maxDay = 31;
            break;
        }
        case 4:
        {
            maxDay = 30;
            break;
        }
        case 5:
        {
            maxDay = 31;
            break;
        }
        case 6:
        {
            maxDay = 30;
            break;
        }
        case 7:
        {
            maxDay = 31;
            break;
        }
        case 8:
        {
            maxDay = 31;
            break;
        }
        case 9:
        {
            maxDay = 30;
            break;
        }
        case 10:
        {
            maxDay = 31;
            break;
        }
        case 11:
        {
            maxDay = 30;
            break;
        }
        case 12:
        {
            maxDay = 31;
            break;
        }
        default:
            return false;
    }
    if(month == 2 && this->isLeapYear())
    {
        maxDay = 29;
    }

    if(day > maxDay || day < 1)
    {
       return false;
    }
    return true;
}

/**
    Med hjälp av den här funktionen kan man enkelt ställa in variablerna 'year', 'month' och 'day' med hjälp
    av en textsträng.
*/
void Date::setDateString(const wxString &dateString)
{
    std::vector<wxString> vector_split;
    misc::split(dateString, '-', vector_split);
    if(vector_split.size() == 3)
    {
        year = wxAtoi(vector_split[0]);
        month = wxAtoi(vector_split[1]);
        day = wxAtoi(vector_split[2]);
    }
    else
    {
        year = 0;
        month = 0;
        day = 0;
    }
}

/**
    Den här funktionen returnerar datumet enligt formatet YYYY-MM-DD.
*/
wxString Date::getDateString() const
{
    wxString dateString;
    dateString << year << "-";
    if(month < 10)
    {
        dateString << "0";
    }
    dateString << month << "-";
    if(day < 10)
    {
        dateString << "0";
    }

    dateString << day;

    return dateString;
}

/**
    Den här operatoröverlagringen jämför två instanser av klassen. Om
    det första datumet inträffar efter det andra datumet, returneras 'true'.
*/
bool Date::operator>(const Date &date) const
{
    if(year > date.year)
    {
        return true;
    }
    if(year == date.year && month > date.month)
    {
        return true;
    }
    if(year == date.year && month == date.month && day > date.day)
    {
        return true;
    }

    return false;
}

void Date::reset()
{
    year = 0;
    month = 0;
    day = 0;
}

/**
    Den här funktionen delar upp en textsträng i mindre textstränger.
*/
void misc::split(const wxString &textstring, const wxChar &delim, std::vector<wxString> &vector_split)
{
    std::stringstream ss;

    for(unsigned int index = 0; index < textstring.length(); index++)
    {
        if(textstring[index] == delim)
        {
            ss.flush();
            vector_split.push_back(ss.str());
            ss.str("");
            continue;
        }

        wxChar wxchar = textstring[index];
        wxString wxstring(wxchar);

        ss << std::string(wxstring.mb_str());
    }
    vector_split.push_back(ss.str());
}

/**
    Den här funktionen tar reda på huruvida en viss fil existerar eller ej.
*/
bool misc::fileExists(const wxString &fileName)
{
    std::ifstream ifile;
    ifile.open(fileName);
    if(ifile)
    {
        return true;
    }
    return false;
}
