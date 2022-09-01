#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <fstream>
#include <wx/string.h>
#include "Interfaces.h"

namespace misc
{
    void split(const wxString &textstring, const wxChar &delim, std::vector<wxString> &vector_split);
    bool fileExists(const wxString &fileName);
}

/**
    Den här klassen är till för att hantera datum.
*/
class Date : public Validate
{
    public:
        Date();
        Date(const unsigned int &_year, const unsigned int &_month, const unsigned int &_day);
        static unsigned int currentYear();
        bool isLeapYear() const;
        virtual bool validate() const;
        void setDateString(const wxString &dateString);
        wxString getDateString() const;

    private:
        /// Den här variabeln håller reda på årtalet.
        unsigned int year;
        /// Den här variabeln håller reda på månaden [1, 12].
        unsigned int month;
        /// Den här variabeln håller reda på dagen i månaden [1, 31].
        unsigned int day;


};


#endif // MISC_H_INCLUDED
