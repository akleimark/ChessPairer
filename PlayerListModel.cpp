#include "PlayerListModel.h"
#include "Database.h"
#include <algorithm>
#include "Logger.h"

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
    Database* db = Database::getInstance();

    QString queryStr = "DELETE FROM players WHERE fide_id = ?";
    QVector<QVariant> bindValues = { id };
    db->executeQuery(queryStr, bindValues);

    // Ta bort från container
    auto it = std::remove_if(container.begin(), container.end(),
                             [&](const Player &p)
                             {
                                 return p.getFideId() == id;
                             });

    if (it != container.end())
    {
        container.erase(it, container.end());
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
                Logger::getInstance()->logError("Ogiltigt sorteringskriterium: " + criterion);
            }
        }
        return false; // Behåll ordningen om alla kriterier är lika
    });
}

Player* PlayerListModel::findPlayerById(const unsigned int &fideId)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        Player &p = *it;
        if (p.getFideId() == fideId)
        {
            return &p;
        }
    }
    return nullptr; // Viktigt: om ingen hittas
}
