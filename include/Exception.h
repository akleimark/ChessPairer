#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <wx/string.h>
#include <stdexcept>

/**
    Det h?r ?r basklassen f?r alla typer av undantagstillst?nd i den h?r applikationen. Klassen
    har en variabel f?r att s?tta och lagra ett felmeddelande. Tanken ?r att man skapar underklasser, som implementerar
    ett specifikt felmeddelande i funktionen 'what'.
*/
class Exception
{
    public:
        Exception(const wxString &whatArg);
        virtual ~Exception() {}
        /// Den h?r funktionen m?ste implementeras av alla klasser som ?rver 'Exception'.
        virtual wxString what() const noexcept = 0;
        /// Den h?r funktionen anv?nds f?r att erh?lla felmeddelandet.
        const wxString getErrorMessage() const { return errorMessage; }
        /// Den h?r funktionen kan anv?ndas f?r att visa felmeddelandet i en dialogruta.
        void showDialog() const;

    protected:
        /// I den h?r variabeln lagras felmeddelandet.
        const wxString errorMessage;

    private:
};

/**
    Den h?r klassen av typen 'Exception' anv?nds f?r alla typer av
    undantagstillst?nd, d?r ett visst v?rde har erh?llit ett f?r l?gt eller f?r h?gt v?rde.
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
    Den h?r klassen av typen 'Exception' behandlar alla typer av undantagstillst?nd, d?r
    n?gon form av databasfel intr?ffar.
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
    Den h?r klassen av typen 'Exception' hanterar alla fel som r?r l?sning av filer med mera.
*/
class IOErrorException : public Exception
{
    public:
        IOErrorException(const wxString &whatArg):
            Exception(whatArg) {}
        virtual ~IOErrorException() {}
        /// Den h?r funktionen returnerar str?ngen 'I/O-fel:', f?ljt av en mer precis f?rklaring av vad som gick fel.
        virtual wxString what() const noexcept;

    protected:

    private:
};

/**
    Den h?r klassen av typen 'Exception' hanterar fel som uppst?r n?r en pekare ?r 'null', n?r den beh?ver anv?ndas.
*/
class NullpointerException : public Exception
{
    public:
        NullpointerException(const wxString &whatArg):
            Exception(whatArg) {}
        virtual ~NullpointerException() {}
        /// Den h?r funktionen returnerar str?ngen 'I/O-fel:', f?ljt av en mer precis f?rklaring av vad som gick fel.
        virtual wxString what() const noexcept;

    protected:

    private:
};


#endif // EXCEPTION_H
