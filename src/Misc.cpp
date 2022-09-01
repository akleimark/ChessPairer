#include "Misc.h"
#include "Defs.h"
#include "Exception.h"

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

bool Date::validate() const
{
    if(year < MINIMUM_YEAR || year > Date::currentYear())
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
            throw ArgumentErrorException("Felaktigt datum.");
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
