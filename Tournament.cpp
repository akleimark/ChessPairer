#include "Tournament.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <iostream>
#include "Database.h"

const unsigned int Tournament::DEFAULT_TOURNAMENT_ID = 0;
const unsigned int Tournament::DEFAULT_NUMBER_OF_ROUNDS = 7;
const QString Tournament::DEFAULT_PAIRING_SYSTEM = "Monrad";
const QString Tournament::DEFAULT_TOURNAMENT_NAME = "Ny turnering";
const QDate Tournament::DEFAULT_START_DATE = QDate::currentDate();
const QDate Tournament::DEFAULT_END_DATE = QDate::currentDate();
const unsigned int Tournament::MINIMUM_NUMBER_OF_ROUNDS = 2;
const unsigned int Tournament::MAXIMUM_NUMBER_OF_ROUNDS = 14;

TournamentPlayer& Tournament::at(const unsigned int &index)
{
    auto it = std::find_if(players.begin(), players.end(),
   [index](const TournamentPlayer &player)
   {
       return player.getPlayerNumber() == index;
   });

    if (it != players.end())
    {
        return const_cast<TournamentPlayer&>(*it); // OBS, diskuteras nedan
    }

    Logger::getInstance()->logError("Spelare med angivet index hittades inte.");
    std::exit(EXIT_FAILURE);
}


Tournament::Tournament(const QString &name, const QDate &startDate, const QDate &endDate,
                       const unsigned int &numberOfRounds, const QString &pairingSystem, const unsigned int &id):
    name(name), startDate(startDate), endDate(endDate), numberOfRounds(numberOfRounds), pairingSystem(pairingSystem), id(id)
{

}

bool Tournament::isValid() const
{
    return checkName() && checkStartDate() && checkEndDate() && checkPairingSystem() && checkNumberOfRounds();
}

bool Tournament::checkName() const
{
    if(name.isEmpty())
    {
        return false;
    }

    const QString illegalChars = "!#¤%&/()=?\"'";

    // Gå igenom varje del av namnet och kontrollera tecken
    for (const QString &cName : name)
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

bool Tournament::checkStartDate() const
{
    return startDate.isValid();
}
bool Tournament::checkEndDate() const
{
    return (endDate.isValid() && endDate >= startDate);
}
bool Tournament::checkNumberOfRounds() const
{
    return (Tournament::MINIMUM_NUMBER_OF_ROUNDS <= numberOfRounds && numberOfRounds <= Tournament::MAXIMUM_NUMBER_OF_ROUNDS);
}

bool Tournament::checkPairingSystem() const
{
    const QStringList list({"Monrad", "Berger"});
    return std::any_of(list.cbegin(), list.cend(),
                       [this](const QString &p)
                       {
                           return p == pairingSystem;
                       });
}

void Tournament::print() const
{
    QTextStream out(stdout);
    const int COLUMN_WIDTH = 20;

    out << QString("Id:").leftJustified(COLUMN_WIDTH) << id << "\n";
    out << QString("Name:").leftJustified(COLUMN_WIDTH) << name << "\n";
    out << QString("Start Date:").leftJustified(COLUMN_WIDTH) << startDate.toString("yyyy-MM-dd") << "\n";
    out << QString("End Date:").leftJustified(COLUMN_WIDTH) << endDate.toString("yyyy-MM-dd") << "\n";
    out << QString("Rounds:").leftJustified(COLUMN_WIDTH) << numberOfRounds << "\n";
    out << QString("Pairing System:").leftJustified(COLUMN_WIDTH) << pairingSystem << "\n";
}

void Tournament::addTournamentPlayer(const TournamentPlayer &player)
{
    // Försök lägga till i set:et
    auto result = players.insert(player);

    if (!result.second)
    {
        Logger::getInstance()->logWarning("TournamentPlayer med FIDE-ID " + QString::number(player.getFideId()) + " finns redan i turneringen.");
        return;
    }

    // Starta en transaktion
    QSqlDatabase db = QSqlDatabase::database(); // Antar standardanslutning
    if (!db.transaction())
    {
        Logger::getInstance()->logError("Kunde inte starta databastransaktion: " + db.lastError().text());
        return;
    }

    // Förbered och bind INSERT
    QSqlQuery query;
    query.prepare("INSERT INTO tournament_players (tournament_id, player_id, player_number) "
                  "VALUES (:tournament_id, :player_id, :player_number)");

    query.bindValue(":tournament_id", this->id);
    query.bindValue(":player_id", player.getFideId());
    query.bindValue(":player_number", player.getPlayerNumber());

    if (!query.exec())
    {
        Logger::getInstance()->logError("Kunde inte lägga till TournamentPlayer i databasen: " + query.lastError().text());

        // Rollback om något gick fel
        if (!db.rollback())
        {
            Logger::getInstance()->logError("Kunde inte rulla tillbaka transaktionen: " + db.lastError().text());
        }
        return;
    }

    // Allt lyckades: commit
    if (!db.commit())
    {
        Logger::getInstance()->logError("Kunde inte genomföra commit av transaktionen: " + db.lastError().text());
    }
}

void Tournament::getTournamentDataFromDatabase()
{
    // Töm containern om den innehåller gamla spelare
    players.clear();

    Database* db = Database::getInstance();

    QString queryStr =
        "SELECT tp.player_id, tp.player_number, p.name, p.rating "
        "FROM tournament_players tp "
        "JOIN players p ON tp.player_id = p.fide_id "
        "WHERE tp.tournament_id = ?";    

    QSqlQuery query;
    query.prepare(queryStr);
    query.addBindValue(this->id);

    if (!query.exec())
    {
        Logger::getInstance()->logError("Kunde inte hämta tournament_players från databasen: " + query.lastError().text());
        return;
    }

    while (query.next())
    {
        unsigned int playerId = query.value(0).toUInt();
        unsigned int playerNumber = query.value(1).toUInt();
        QString name = query.value(2).toString();
        unsigned int rating = query.value(3).toUInt();

        // Skapa TournamentPlayer och sätt data
        TournamentPlayer player;
        player.setFideId(playerId);
        player.setPlayerNumber(playerNumber);
        player.setName(name);
        player.setRating(rating);

        players.insert(player);
    }
}
