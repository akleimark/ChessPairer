#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <fstream>
#include <wx/string.h>

namespace misc
{
    unsigned int getCurrentYear();
    bool isLeapYear(const unsigned int &year);
    void split(const wxString &textstring, const wxChar &delim, std::vector<wxString> &vector_split);
    bool fileExists(const wxString &fileName);

}


#endif // MISC_H_INCLUDED
