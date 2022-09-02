#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <wx/string.h>
#include <stdexcept>

/**
    Det här är basklassen för alla typer av undantagstillstånd i den här applikationen. Klassen
    har en variabel för att sätta och lagra ett felmeddelande. Tanken är att man skapar underklasser, som implementerar
    ett specifikt felmeddelande i funktionen 'what'.
*/
class Exception
{
    public:
        Exception(const wxString &whatArg);
        virtual ~Exception() {}
        /// Den här funktionen måste implementeras av alla klasser som ärver 'Exception'.
        virtual wxString what() const noexcept = 0;
        /// Den här funktionen används för att erhålla felmeddelandet.
        const wxString getErrorMessage() const { return errorMessage; }

    protected:
        /// I den här variabeln lagras felmeddelandet.
        const wxString errorMessage;

    private:
};

/**
    Den här klassen av typen 'Exception' används för alla typer av
    undantagstillstånd, där ett visst värde har erhållit ett för lågt eller för högt värde.
*/
class ArgumentErrorException : public Exception
{
    public:
        ArgumentErrorException(const wxString &whatArg):
            Exception(whatArg) {}
        virtual ~ArgumentErrorException() {}
        virtual wxString what() const noexcept;

    protected:

    private:
};

/**
    Den här klassen av typen 'Exception' behandlar alla typer av undantagstillstånd, där
    någon form av databasfel inträffar.
*/
class DatabaseErrorException : public Exception
{
    public:
        DatabaseErrorException(const wxString &whatArg):
            Exception(whatArg) {}
        virtual ~DatabaseErrorException() {}
        virtual wxString what() const noexcept;

    protected:

    private:
};

/**
    Den här klassen av typen 'Exception' hanterar alla fel som rör läsning av filer med mera.
*/
class IOErrorException : public Exception
{
    public:
        IOErrorException(const wxString &whatArg):
            Exception(whatArg) {}
        virtual ~IOErrorException() {}
        virtual wxString what() const noexcept;

    protected:

    private:
};


#endif // EXCEPTION_H
