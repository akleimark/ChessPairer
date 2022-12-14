#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

/**
    Det h?r gr?nssnittet anv?nds f?r att kontrollera att klassen som implementerar det
    har korrekta v?rden.
*/
class Validate
{
    public:
        virtual bool validate() const = 0;
};

/**
    Det h?r gr?nssnittet anv?nds f?r att skriva ut uppgifter om klassen som implementerar det.
*/
class Print
{
    public:
        virtual void print() const = 0;
};

/**
    Det h?r gr?nssnittet anv?nds f?r att spara en instans av klassen som implementerar det till databasen.
    Det r?r sig uteslutande om klasser av typen 'Modell'.
*/
class DatabaseInterface
{
    public:
        /// Den h?r funktionen uppdaterar data om en viss modell, som redan ?r inlagd i databasen.
        virtual void save() const = 0;
        /// Den h?r funktionen l?gger till en ny modell till databasen.
        virtual void addToDatabase() const = 0;
        /// Den h?r funktionen tar bort en modell ur databasen.
        virtual void removeFromDatabase() const = 0;
};
/**
    Det h?r gr?nssnittet anv?nds f?r att nollst?lla en modell.
*/
class Reset
{
    public:
        virtual void reset() = 0;
};

/**
    Det h?r gr?nssnittet anv?nds f?r att kunna implementera designm?nstret 'Strategy'.
*/
class Strategy
{
    public:
        virtual void execute() = 0;
};

#endif // INTERFACES_H_INCLUDED
