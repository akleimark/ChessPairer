#include "PlayerListModel.h"
#include "Database.h"
#include <algorithm>
#include "Logger.h"

void PlayerListModel::addToDatabase(const Player &player)
{
    try
    {
        // Få tag i databasinstansen
        Database* db = Database::getInstance();

        // Definiera den parametiserade SQL.
        QString queryStr = "INSERT INTO players (name, rating, fide_id) VALUES (?, ?, ?)";

        QVector<QVariant> bindValues = { player.getName(), player.getRating(), player.getFideId() };

        // Kör SQL med korrekt parametisering.
        db->executeQuery(queryStr, bindValues);

        Logger::getInstance()->logInfo("Spelaren lades in i databasen utan problem.");
    }
    catch(const std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void PlayerListModel::updateDatabase(const Player &player)
{
    try
    {
        Database* db = Database::getInstance();
        QString queryStr = "UPDATE players SET name = ?, rating = ? WHERE fide_id = ?";
        QVector<QVariant> bindValues = { player.getName(), player.getRating(), player.getFideId() };

        db->executeQuery(queryStr, bindValues);

    }
    catch(const std::runtime_error &error)
    {
       // Logga felet.
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void PlayerListModel::removeById(const unsigned int &id)
{
    try
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
    catch (const std::runtime_error &error)
    {
        // Logga fel om det inträffar
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void PlayerListModel::doSort(const QStringList &sortCriteria)
{
    try
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
                    throw std::runtime_error("Ogiltigt sorteringskriterium:" + criterion.toStdString());
                }
            }
            return false; // Behåll ordningen om alla kriterier är lika
        });

        // Notifiera UI om förändringen
        notifyAllViews();
    }
    catch(std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}


