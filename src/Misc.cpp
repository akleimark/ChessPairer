#include "Misc.h"
#include "Defs.h"
#include "Exception.h"
#include <wx/wxchar.h>

const unsigned int Date::MINIMUM_YEAR = 1900;
const unsigned int Date::MAXIMUM_YEAR = 2100;

/**
    Den f?rvalda konstruktorn skapar en instans av klassen med hj?lp
    av dagens datum. De privata variablerna st?lls in d?refter.
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
    Den h?r konstruktorn tar argument f?r ?r, m?nad och dag.
*/
Date::Date(const unsigned int &_year, const unsigned int &_month, const unsigned int &_day):
    year(_year), month(_month), day(_day)
{

}


/**
    Den h?r funktionen returnerar ett heltal med det nuvarande ?ret.
*/
unsigned int Date::currentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}

/**
    Den h?r funktionen returnerar huruvida ett givet ?r ?r skott?r eller ej.
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
    Den h?r funktionen kontrollerar, huruvida datumet ?r korrekt eller ej.
    Om det ?r korrekt, returneras 'true'.
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
    Med hj?lp av den h?r funktionen kan man enkelt st?lla in variablerna 'year', 'month' och 'day' med hj?lp
    av en textstr?ng.
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
    Den h?r funktionen returnerar datumet enligt formatet YYYY-MM-DD.
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
    Den h?r operator?verlagringen j?mf?r tv? instanser av klassen. Om
    det f?rsta datumet intr?ffar efter det andra datumet, returneras 'true'.
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
    Den h?r funktionen delar upp en textstr?ng i mindre textstr?nger.
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
    Den h?r funktionen tar reda p? huruvida en viss fil existerar eller ej.
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
