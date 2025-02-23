#include "PlayerListModel.h"
#include "Database.h"
#include <algorithm>
#include "Logger.h"

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

unsigned int PlayerListModel::addToDatabase(const Player &player)
{
    // Definiera den parametiserade SQL.
    QString queryStr = "INSERT INTO players (name, rating, fide_id) VALUES (?, ?, ?)";

    // Skapa SQL-frågan
    QSqlQuery query;
    query.prepare(queryStr);

    // Binda värden till frågan
    query.bindValue(0, player.getName());
    query.bindValue(1, player.getRating());
    query.bindValue(2, player.getFideId());

    // Kör SQL-frågan och kontrollera om den lyckas
    if (!query.exec())
    {
        Logger::getInstance()->logError("Misslyckades att lägga till spelaren i databasen: " + query.lastError().text());
        std::exit(EXIT_FAILURE);
    }

    // Hämta det insatta fide_id:t (detta antas vara unikt och användas som primärnyckel)
    QVariant lastId = query.lastInsertId();
    if (!lastId.isValid() || !lastId.canConvert<unsigned int>())
    {
        Logger::getInstance()->logError("Misslyckades att hämta det insatta spelare-id:et.");
        std::exit(EXIT_FAILURE);
    }

    unsigned int playerId = lastId.toUInt();
    Logger::getInstance()->logInfo("Spelare tillagd i databasen med FIDE-ID: " + QString::number(playerId));

    return playerId;
}


void PlayerListModel::updateDatabase(const Player &player)
{
    Database* db = Database::getInstance();
    QString queryStr = "UPDATE players SET name = ?, rating = ? WHERE fide_id = ?";
    QVector<QVariant> bindValues = { player.getName(), player.getRating(), player.getFideId() };
    db->executeQuery(queryStr, bindValues);
}

void PlayerListModel::removeById(const unsigned int &id)
{
    // Hämta databasinstansen
    Database* db = Database::getInstance();

    // Definiera den parameteriserade frågan för att ta bort spelaren
    QString queryStr = "DELETE FROM players WHERE fide_id = ?";

    // Skapa en vektor för bindvärdena (id)
    QVector<QVariant> bindValues = { id };

    // Utför frågan via executeQuery-metoden
    db->executeQuery(queryStr, bindValues);

    // Ta bort spelaren från vektorn
    std::vector<Player>::const_iterator it = std::remove_if(container.begin(), container.end(), [&](const Player &p)
    {
        return p.getFideId() == id; // Matcha på FIDE-ID
    });

    // Om spelaren hittades i vektorn, ta bort den
    if (it != container.end())
    {
        container.erase(it, container.end()); // Faktiskt ta bort objektet från vektorn
    }
}

void PlayerListModel::doSort(const QStringList &sortCriteria)
{
    std::sort(container.begin(), container.end(), [&](const Player &a, const Player &b) {
        for (const QString &criterion : sortCriteria)
        {
            if (criterion == "Name")
            {
                if (a.getName() != b.getName())
                    return a.getName() < b.getName();
            }
            else if (criterion == "Rating")
            {
                if (a.getRating() != b.getRating())
                    return a.getRating() < b.getRating();
            }
            else if (criterion == "FideId")
            {
                if (a.getFideId() != b.getFideId())
                    return a.getFideId() < b.getFideId();
            }
            else
            {
                Logger::getInstance()->logError("Ogiltigt sorteringskriterium:" + criterion);
            }
        }
        return false; // Behåll ordningen om alla kriterier är lika
    });
}


