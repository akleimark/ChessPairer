#include "TournamentListModel.h"
#include "Database.h"
#include "Logger.h"
#include <algorithm>
#include "Logger.h"
#include <iostream>
#include <iomanip>

TournamentListModel::TournamentListModel(Tournament &tournament, SettingsModel &settingsModel):
    tournament(tournament), ListModel<Tournament>(settingsModel)
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

    if (!checkQuery.exec())
    {
        Logger::getInstance()->logError("Misslyckades att kontrollera om turneringen finns i databasen: " + checkQuery.lastError().text());
        std::exit(EXIT_FAILURE);
    }

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

    // Ta bort från databasen
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
    auto oldSize = container.size();

    container.erase(
        std::remove_if(container.begin(), container.end(),
                       [&](const Tournament &tournament)
                       {
                           return tournament.getId() == id;
                       }),
        container.end()
        );

    if (container.size() < oldSize)
    {
        Logger::getInstance()->logInfo("Turneringen med id: " + QString::number(id) + " har tagits bort från containern.");
    }
    else
    {
        Logger::getInstance()->logWarning("Ingen turnering med id: " + QString::number(id) + " hittades i containern att ta bort.");
    }
}

Tournament* TournamentListModel::findTournamentById(const unsigned int &id)
{
    for (Tournament &tournament : container)
    {
        if (tournament.getId() == id)
        {
            return &tournament;
        }
    }
    return nullptr; // Viktigt: om ingen turnering hittas
}

void TournamentPlayer::print() const
{
    std::cout << std::left; // Justera vänsterjusterat
    std::cout << std::setw(15) << "FIDE-ID:" << fideId << std::endl;
    std::cout << std::setw(15) << "Namn:" << name.toStdString() << std::endl;
    std::cout << std::setw(15) << "Rating:" << rating << std::endl;
    std::cout << std::setw(15) << "Spelarnummer:" << playerNumber << std::endl;
}

