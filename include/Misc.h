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
    bool isLeapYear(const unsigned int &year);
    void split(const wxString &textstring, const wxChar &delim, std::vector<wxString> &vector_split);
    bool fileExists(const wxString &fileName);
}

class Date : public Validate
{
    public:
        Date(const unsigned int &_year, const unsigned int &_month = 1, const unsigned int &_day = 1);
        static unsigned int currentYear();
        bool isLeapYear() const;
        virtual bool validate() const;


    private:
        const unsigned int year;
        const unsigned int month;
        const unsigned int day;


};


#endif // MISC_H_INCLUDED
