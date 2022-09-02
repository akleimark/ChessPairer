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
class Date : public Validate, public Reset
{
    public:
        // Konstruktorer och destruktorer
        Date();
        Date(const unsigned int &_year, const unsigned int &_month, const unsigned int &_day);
        virtual ~Date() {}
        // Klassfunktioner och medlemsfunktioner
        static unsigned int currentYear();
        bool isLeapYear() const;
        void setDateString(const wxString &dateString);
        wxString getDateString() const;

        // Operatoröverlagringar.
        bool operator>(const Date &date) const;

        // Implementerade funktioner som härrör till gränssnitt.
        virtual bool validate() const;
        virtual void reset();

    private:
        /// Den här variabeln håller reda på årtalet.
        unsigned int year;
        /// Den här variabeln håller reda på månaden [1, 12].
        unsigned int month;
        /// Den här variabeln håller reda på dagen i månaden [1, 31].
        unsigned int day;
        /// Den här klasskonstanten anger värdet på det tidigaste året som kan användas i en turnering.
        const static unsigned int MINIMUM_YEAR;
        /// Den här klasskonstanten anger värdet på det senaste året som kan användas i en turnering.
        const static unsigned int MAXIMUM_YEAR;
};

#endif // MISC_H_INCLUDED
