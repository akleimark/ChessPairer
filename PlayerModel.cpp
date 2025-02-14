#include "PlayerModel.h"
#include "Database.h"

void PlayerModel::addPlayerToContainer(const Player &player)
{
    // Lägg till spelaren i den lokala listan
    players.push_back(player);

    // Uppdatera alla vyer (observermönster)
    notifyAllViews();
}

void PlayerModel::addPlayerToDatabase(const Player &player)
{
    // Lägg till spelaren i databasen
    Database* db = Database::getInstance();  // Hämta databasinstansen
    QString query = QString("INSERT INTO players (name, rating, fide_id) VALUES ('%1', %2, %3)")
                        .arg(player.getName())
                        .arg(player.getRating())
                        .arg(player.getFideId());
    db->executeQuery(query);  // Kör SQL-frågan för att lägga till spelaren i databasen
}
