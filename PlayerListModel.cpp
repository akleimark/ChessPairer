#include "PlayerListModel.h"
#include "Database.h"

void PlayerListModel::addPlayerToContainer(const Player &player)
{
    // Lägg till spelaren i den lokala listan
    players.push_back(player);

    // Uppdatera alla vyer (observermönster)
    notifyAllViews();
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
