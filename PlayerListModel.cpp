#include "PlayerListModel.h"
#include "Database.h"
#include <algorithm>

void PlayerListModel::addToDatabase(const Player &player)
{
    // Lägg till spelaren i databasen
    Database* db = Database::getInstance();  // Hämta databasinstansen
    QString query = QString("INSERT INTO players (name, rating, fide_id) VALUES ('%1', %2, %3)")
                        .arg(player.getName())
                        .arg(player.getRating())
                        .arg(player.getFideId());
    db->executeQuery(query);  // Kör SQL-frågan för att lägga till spelaren i databasen
}

void PlayerListModel::updateDatabase(const Player &player)
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

void PlayerListModel::removeById(const unsigned int &id)
{
    // Ta bort spelaren från databasen
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());

    query.prepare("DELETE FROM players WHERE fide_id = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qWarning() << "Misslyckades att ta bort spelare från databasen:" << query.lastError().text();
    }

    // Ta bort spelaren från vektorn
    std::vector<Player>::const_iterator it = std::remove_if(container.begin(), container.end(), [&](const Player &p)
     {
         return p.getFideId() == id; // Matcha på FIDE-ID
     });

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
                qWarning() << "Ogiltigt sorteringskriterium:" << criterion;
            }
        }
        return false; // Behåll ordningen om alla kriterier är lika
    });

    // Notifiera UI om förändringen
    notifyAllViews();
}


