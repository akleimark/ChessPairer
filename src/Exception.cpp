#include "Exception.h"


Exception::Exception(const wxString &whatArg):
    errorMessage(whatArg)
{

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






