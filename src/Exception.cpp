#include "Exception.h"
#include "Defs.h"
#include <wx/msgdlg.h>

Exception::Exception(const wxString &whatArg):
    errorMessage(whatArg)
{

}

void Exception::showDialog() const
{
    wxMessageBox(this->what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
}

wxString ArgumentErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "Argument-fel: " << errorMessage;
    return errorString;
}

wxString DatabaseErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "Databasfel: " << errorMessage;
    return errorString;
}

wxString IOErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "I/O-fel: " << errorMessage;
    return errorString;
}

