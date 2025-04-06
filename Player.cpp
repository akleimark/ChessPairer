#include "Player.h"
#include <QStringList>

const unsigned int Player::MINIMUM_RATING = 1400;
const unsigned int Player::MAXIMUM_RATING = 4000;

bool Player::isValid() const
{
    return (checkRating() && checkName() && checkFideId());
}

bool Player::checkName() const
{
    // Dela upp namnet i delar baserat på mellanslag
    const QStringList nameArray = name.split(" ", Qt::SkipEmptyParts);
    const QString illegalChars = "0123456789!#¤%&/()=?\"'";

    // Kontrollera om namnet är tomt eller om det har för få eller för många delar
    if (name.trimmed().isEmpty() || nameArray.length() == 1 || nameArray.length() > 3)
    {
        return false;
    }

    // Gå igenom varje del av namnet och kontrollera tecken
    for (const QString &cName : nameArray)
    {
        for (const QChar &ch : cName)
        {
            if (illegalChars.contains(ch))
            {
                return false; // Returnera false om ett olagligt tecken hittas
            }
        }
    }

    return true; // Alla kontroller klarade, namnet är giltigt
}

bool Player::checkRating() const
{
    return (MINIMUM_RATING <= rating && rating <= MAXIMUM_RATING);
}

bool Player::checkFideId() const
{
    // Kontrollera of FIDE-ID är inom ett rimligt intervall
    return fideId >= 100000 && fideId <= 999999999;
}
