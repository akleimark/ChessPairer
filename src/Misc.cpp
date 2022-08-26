#include "Misc.h"

/**
    Den här funktionen returnerar ett heltal med det nuvarande året.
*/
unsigned int misc::getCurrentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}

/**
    Den här funktionen returnerar huruvida ett givet år är skottår eller ej.
    Exempelvis ger isLeapYear(1905) false, medan isLeapYear(2020) true.
*/
bool misc::isLeapYear(const unsigned int &year)
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
