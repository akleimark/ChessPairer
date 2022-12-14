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
    Den h?r klassen ?r till f?r att hantera datum.
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

        // Operator?verlagringar.
        bool operator>(const Date &date) const;

        // Implementerade funktioner som h?rr?r till gr?nssnitt.
        virtual bool validate() const;
        virtual void reset();

    private:
        /// Den h?r variabeln h?ller reda p? ?rtalet.
        unsigned int year;
        /// Den h?r variabeln h?ller reda p? m?naden [1, 12].
        unsigned int month;
        /// Den h?r variabeln h?ller reda p? dagen i m?naden [1, 31].
        unsigned int day;
        /// Den h?r klasskonstanten anger v?rdet p? det tidigaste ?ret som kan anv?ndas i en turnering.
        const static unsigned int MINIMUM_YEAR;
        /// Den h?r klasskonstanten anger v?rdet p? det senaste ?ret som kan anv?ndas i en turnering.
        const static unsigned int MAXIMUM_YEAR;
};

#endif // MISC_H_INCLUDED
