#include "PlayerListModel.h"
#include "Database.h"
#include <algorithm>


const Player& PlayerListModel::at(const unsigned int &index) const
{
    if(index >= players.size())
    {
        throw std::runtime_error("Index out of bounds");
    }
    return players[index];
}

Player& PlayerListModel::at(const unsigned int &index)
{
    if(index >= players.size())
    {
        throw std::runtime_error("Index out of bounds");
    }

    return players[index];
}

void PlayerListModel::addPlayerToContainer(const Player &player)
{
    // Lägg till spelaren i den lokala listan
    players.push_back(player);
}

void PlayerListModel::addPlayerToDatabase(const Player &player)
{
    // Lägg till spelaren i databasen
    Database* db = Database::getInstance();  // Hämta databasinstansen
    QString query = QString("INSERT INTO players (name, rating, fide_id) VALUES ('%1', %2, %3)")
                        .arg(player.getName())
                        .arg(player.getRating())
                        .arg(player.getFideId());
    db->executeQuery(query);  // Kör SQL-frågan för att lägga till spelaren i databasen
}

void PlayerListModel::updatePlayerInDatabase(const Player &player)
{
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());

    query.prepare("UPDATE players SET name = ?, rating = ? WHERE fide_id = ?");
    query.addBindValue(player.getName());
    query.addBindValue(player.getRating());
    query.addBindValue(player.getFideId());

    if (!query.exec())
    {
        qWarning() << "Misslyckades att uppdatera spelare i databasen:" << query.lastError().text();
    }
}

void PlayerListModel::removePlayerById(const unsigned int &fideId)
{
    // Ta bort spelaren från databasen
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());

    query.prepare("DELETE FROM players WHERE fide_id = ?");
    query.addBindValue(fideId);

    if (!query.exec())
    {
        qWarning() << "Misslyckades att ta bort spelare från databasen:" << query.lastError().text();
    }

    // Ta bort spelaren från vektorn
    std::vector<Player>::const_iterator it = std::remove_if(players.begin(), players.end(), [&](const Player &p)
     {
         return p.getFideId() == fideId; // Matcha på FIDE-ID
     });

    if (it != players.end())
    {
        players.erase(it, players.end()); // Faktiskt ta bort objektet från vektorn
    }

    // Notifiera UI om förändringen
    notifyAllViews();
}

void PlayerListModel::doSort(const QStringList &sortCriteria)
{
    std::sort(players.begin(), players.end(), [&](const Player &a, const Player &b) {
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
                qWarning() << "Ogiltigt sorteringskriterium:" << criterion;
            }
        }
        return false; // Behåll ordningen om alla kriterier är lika
    });

    // Notifiera UI om förändringen
    notifyAllViews();
}


