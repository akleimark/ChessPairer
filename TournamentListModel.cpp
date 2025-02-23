#include "TournamentListModel.h"
#include "Database.h"
#include "Logger.h"
#include <algorithm>
#include "Logger.h"

const unsigned int Tournament::DEFAULT_TOURNAMENT_ID = 0;
const unsigned int Tournament::DEFAULT_NUMBER_OF_ROUNDS = 7;
const QString Tournament::DEFAULT_PAIRING_SYSTEM = "Monrad";
const QString Tournament::DEFAULT_TOURNAMENT_NAME = "Ny turnering";
const QDate Tournament::DEFAULT_START_DATE = QDate::currentDate();
const QDate Tournament::DEFAULT_END_DATE = QDate::currentDate();
const unsigned int Tournament::MINIMUM_NUMBER_OF_ROUNDS = 2;
const unsigned int Tournament::MAXIMUM_NUMBER_OF_ROUNDS = 14;

TournamentPlayer::TournamentPlayer(const unsigned int &fideId, const QString &name, const unsigned int &rating, const unsigned int &playerNumber):
    Player(fideId, name, rating), playerNumber(playerNumber)
{
    if(!Player(fideId, name, rating).isValid())
    {
        Logger::getInstance()->logError("Data otillåten.");
    }
}

bool TournamentPlayer::operator<(const TournamentPlayer &player) const
{
    return playerNumber < player.playerNumber;
}

TournamentPlayer* Tournament::at(const unsigned int &index) const
{
    std::set<TournamentPlayer*>::const_iterator it = std::find_if(players.begin(), players.end(),
    [index](TournamentPlayer *player)
    {
        return player->getPlayerNumber() == index;
    });

    if (it != players.end())
    {
        return *it;
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

    out << QString("Name:").leftJustified(COLUMN_WIDTH) << name << "\n";
    out << QString("Start Date:").leftJustified(COLUMN_WIDTH) << startDate.toString("yyyy-MM-dd") << "\n";
    out << QString("End Date:").leftJustified(COLUMN_WIDTH) << endDate.toString("yyyy-MM-dd") << "\n";
    out << QString("Rounds:").leftJustified(COLUMN_WIDTH) << numberOfRounds << "\n";
    out << QString("Pairing System:").leftJustified(COLUMN_WIDTH) << pairingSystem << "\n";
}

TournamentListModel::TournamentListModel(SettingsModel *settingsModel):
    ListModel<Tournament>(settingsModel)
{

}

unsigned int TournamentListModel::addToDatabase(const Tournament &tournament)
{
    // Förbered SQL-frågan
    QString queryStr = QString("INSERT INTO tournaments (name, start_date, end_date, number_of_rounds, pairing_system) "
                               "VALUES (:name, :start_date, :end_date, :number_of_rounds, :pairing_system)");

    // Skapa och förbered frågan med bind-värden
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":name", tournament.getName());
    query.bindValue(":start_date", tournament.getStartDate().toString("yyyy-MM-dd"));
    query.bindValue(":end_date", tournament.getEndDate().toString("yyyy-MM-dd"));
    query.bindValue(":number_of_rounds", tournament.getNumberOfRounds());
    query.bindValue(":pairing_system", tournament.getPairingSystem());

    // Utför frågan och kontrollera om den lyckas
    if (!query.exec())
    {
        Logger::getInstance()->logError("Misslyckades att lägga till turneringen i databasen: " + query.lastError().text());
        std::exit(EXIT_FAILURE);
    }

    // Hämta det senast insatta ID:t
    QVariant lastId = query.lastInsertId();
    if (!lastId.isValid() || !lastId.canConvert<unsigned int>())
    {
        Logger::getInstance()->logError("Misslyckades att hämta det insatta turnerings-id:et.");
        std::exit(EXIT_FAILURE);
    }

    unsigned int tournamentId = lastId.toUInt();
    Logger::getInstance()->logInfo("Turnering tillagd i databasen med ID: " + QString::number(tournamentId));

    return tournamentId;
}


void TournamentListModel::updateDatabase(const Tournament &tournament)
{

    // Förbered SQL-frågan
    QString queryStr = "UPDATE tournaments SET name = ?, start_date = ?, end_date = ?, number_of_rounds = ?, pairing_system = ? WHERE id = ?";

    // Samla bindvärdena
    QVector<QVariant> bindValues;
    bindValues.append(tournament.getName());
    bindValues.append(tournament.getStartDate().toString("yyyy-MM-dd"));
    bindValues.append(tournament.getEndDate().toString("yyyy-MM-dd"));
    bindValues.append(tournament.getNumberOfRounds());
    bindValues.append(tournament.getPairingSystem());
    bindValues.append(tournament.getId());

    // Anropa Database::executeQuery för att exekvera frågan
    Database::getInstance()->executeQuery(queryStr, bindValues);
}

void TournamentListModel::removeById(const unsigned int &id)
{
    // Förbered SQL-frågan och bind parametern
    QString checkQueryStr = "SELECT COUNT(*) FROM tournaments WHERE id = ?";

    QSqlQuery checkQuery;
    checkQuery.prepare(checkQueryStr);
    checkQuery.addBindValue(id);

    // Kör frågan och kontrollera resultatet
    if (!checkQuery.exec())
    {
        Logger::getInstance()->logError("Misslyckades att kontrollera om turneringen finns i databasen: " + checkQuery.lastError().text());
        std::exit(EXIT_FAILURE);
    }

    // Kontrollera om vi har ett resultat och hämta antalet
    if (!checkQuery.next())
    {
        Logger::getInstance()->logError("Inga rader returnerades vid kontroll av turnerings-ID.");
        std::exit(EXIT_FAILURE);
    }

    int count = checkQuery.value(0).toInt();
    Logger::getInstance()->logInfo("Antal hittade turneringar med id " + QString::number(id) + ": " + QString::number(count));

    if (count == 0)
    {
        Logger::getInstance()->logError("Turneringen med id: " + QString::number(id) + " finns inte i databasen.");
        std::exit(EXIT_FAILURE);
    }

    // Om turneringen finns, fortsätt med borttagningen
    QString queryStr = "DELETE FROM tournaments WHERE id = ?";
    QSqlQuery deleteQuery;
    deleteQuery.prepare(queryStr);
    deleteQuery.addBindValue(id);

    if (!deleteQuery.exec())
    {
        Logger::getInstance()->logError("Misslyckades att ta bort turneringen från databasen: " + deleteQuery.lastError().text());
        std::exit(EXIT_FAILURE);
    }

    Logger::getInstance()->logInfo("Turneringen med id: " + QString::number(id) + " har tagits bort från databasen.");

    // Ta bort turneringen från containern
    container.erase(
        std::remove_if(container.begin(), container.end(),
                       [&](const Tournament &t) { return t.getId() == id; }),
        container.end()
        );

    Logger::getInstance()->logInfo("Turneringen med id: " + QString::number(id) + " har tagits bort från containern.");
}

