#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>

class Tournament
{
    public:
        Tournament(const std::string &tournamentName);
        ~Tournament() {}

    protected:

    private:
        const std::string name;

};

#endif // TOURNAMENT_H
