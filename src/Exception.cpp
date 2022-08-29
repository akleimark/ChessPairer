#include "Exception.h"


Exception::Exception(const wxString &whatArg):
    errorMessage(whatArg)
{

}

wxString RangeErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "Range Error: " << errorMessage;
    return errorString;
}

wxString DatabaseErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "Database Error: " << errorMessage;
    return errorString;
}

wxString IOErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "IO Error: " << errorMessage;
    return errorString;
}

wxString ModelErrorException::what() const noexcept
{
    wxString errorString;
    errorString << "Model Error: " << errorMessage;
    return errorString;
}

wxString NullpointerException::what() const noexcept
{
    wxString errorString;
    errorString << "Nullpointer: " << errorMessage;
    return errorString;
}


