#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

/**
    Det här gränssnittet används för att kontrollera att klassen som implementerar det
    har korrekta värden.
*/
class Validate
{
    public:
        virtual bool validate() const = 0;
};

/**
    Det här gränssnittet används för att skriva ut uppgifter om klassen som implementerar det.
*/
class Print
{
    public:
        virtual void print() const = 0;
};

/**
    Det här gränssnittet används för att spara en instans av klassen som implementerar det till databasen.
    Det rör sig uteslutande om klasser av typen 'Modell'.
*/
class DatabaseInterface
{
    public:
        /// Den här funktionen uppdaterar data om en viss modell, som redan är inlagd i databasen.
        virtual void save() const = 0;
        /// Den här funktionen lägger till en ny modell till databasen.
        virtual void addToDatabase() const = 0;
        /// Den här funktionen tar bort en modell ur databasen.
        virtual void removeFromDatabase() const = 0;
};
/**
    Det här gränssnittet används för att nollställa en modell.
*/
class Reset
{
    public:
        virtual void reset() = 0;
};

/**
    Det här gränssnittet används för att kunna implementera designmönstret 'Strategy'.
*/
class Strategy
{
    public:
        virtual void execute() = 0;
};

#endif // INTERFACES_H_INCLUDED
