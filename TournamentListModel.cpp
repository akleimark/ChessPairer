#include "TournamentListModel.h"
#include "Database.h"
#include "Logger.h"

const unsigned int Tournament::DEFAULT_TOURNAMENT_ID = 0;
const unsigned int Tournament::DEFAULT_NUMBER_OF_ROUNDS = 7;
const QString Tournament::DEFAULT_PAIRING_SYSTEM = "Monrad";
const QString Tournament::DEFAULT_TOURNAMENT_NAME = "Ny turnering";
const QDate Tournament::DEFAULT_START_DATE = QDate::currentDate();
const QDate Tournament::DEFAULT_END_DATE = QDate::currentDate();

Tournament::Tournament(const QString &name, const QDate &startDate, const QDate &endDate,
           const unsigned int &numberOfRounds, const QString &pairingSystem, const unsigned int &id):
    name(name), startDate(startDate), endDate(endDate), numberOfRounds(numberOfRounds), pairingSystem(pairingSystem), id(id)
{

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

void TournamentListModel::addToDatabase(const Tournament &tournament)
{
    try
    {
        Database* db = Database::getInstance();

        // Förbered SQL-frågan
        QString queryStr = QString("INSERT INTO tournaments (name, start_date, end_date, number_of_rounds, pairing_system) "
                                   "VALUES (:name, :start_date, :end_date, :number_of_rounds, :pairing_system)");

        // Bind värdena till en QVector
        QVector<QVariant> bindValues;
        bindValues.append(tournament.getName());
        bindValues.append(tournament.getStartDate().toString("yyyy-MM-dd"));
        bindValues.append(tournament.getEndDate().toString("yyyy-MM-dd"));
        bindValues.append(tournament.getNumberOfRounds());
        bindValues.append(tournament.getPairingSystem());

        // Anropa executeQuery för att köra SQL-frågan
        db->executeQuery(queryStr, bindValues);

        Logger::getInstance()->logInfo("Turneringen lades till i databasen.");
    }
    catch (const std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void TournamentListModel::updateDatabase(const Tournament &tournament)
{
    try
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

        Logger::getInstance()->logInfo("Turneringen uppdaterades i databasen utan problem.");
    }
    catch (const std::runtime_error &error)
    {
        Logger::getInstance()->logError(error.what());
        std::exit(EXIT_FAILURE);
    }
}

void TournamentListModel::removeById(const unsigned int &id)
{
    try
    {
        // Kontrollera om turneringen finns i databasen innan borttagning
        QString checkQueryStr = "SELECT COUNT(*) FROM tournaments WHERE id = ?";

        QVector<QVariant> checkBindValues;
        checkBindValues.append(id);

        // Använd Database::executeQuery för att kontrollera om id finns
        QSqlQuery checkQuery;
        if(!Database::getInstance()->executeQueryWithResult(checkQueryStr, checkBindValues, checkQuery))
        {
            Logger::getInstance()->logError("Misslyckades att kontrollera om turneringen finns i databasen.");
            std::exit(EXIT_FAILURE);
        }

        // Om inga rader hittades, logga och returnera
        checkQuery.next(); // Flytta till den första (och enda) raden i resultatet
        int count = checkQuery.value(0).toInt();
        if (count == 0)
        {
            Logger::getInstance()->logError("Turneringen med id: " + QString::number(id) + " finns inte i databasen.");
            std::exit(EXIT_FAILURE);
        }

        // Om turneringen finns, fortsätt med borttagningen
        QString queryStr = "DELETE FROM tournaments WHERE id = ?";
        QVector<QVariant> bindValues;
        bindValues.append(id);

        // Utför borttagningen från databasen
        Database::getInstance()->executeQuery(queryStr, bindValues);

        Logger::getInstance()->logInfo("Turneringen med id: " + QString::number(id) + " togs bort från databasen.");

        // Ta bort turneringen från vektorn
        auto it = std::remove_if(container.begin(), container.end(), [&](const Tournament &t)
                                 {
                                     return t.getId() == id;
                                 });

        if (it != container.end())
        {
            container.erase(it, container.end());
        }
    }
    catch (const std::runtime_error &error)
    {
        Logger::getInstance()->logError("Misslyckades att ta bort turneringen från databasen: " + QString::fromStdString(error.what()));
        std::exit(EXIT_FAILURE);
    }
}



