#include "TournamentListModel.h"
#include "Database.h"

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
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());
    query.prepare("INSERT INTO tournaments (name, start_date, end_date, number_of_rounds, pairing_system) "
                  "VALUES (:name, :start_date, :end_date, :number_of_rounds, :pairing_system)");

    // Bind alla värden till SQL-frågan
    query.bindValue(":name", tournament.getName());
    query.bindValue(":start_date", tournament.getStartDate().toString("yyyy-MM-dd"));
    query.bindValue(":end_date", tournament.getEndDate().toString("yyyy-MM-dd"));
    query.bindValue(":number_of_rounds", tournament.getNumberOfRounds());
    query.bindValue(":pairing_system", tournament.getPairingSystem());

    // Utför frågan
    if (!query.exec())
    {
        qDebug() << "Insertion failed:" << query.lastError().text();
    }

}
void TournamentListModel::updateDatabase(const Tournament &tournament)
{
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());

    query.prepare("UPDATE tournaments SET name = ?, start_date = ?, end_date = ?, number_of_rounds = ?, pairing_system = ? WHERE id = ?");
    query.addBindValue(tournament.getName());
    query.addBindValue(tournament.getStartDate().toString("yyyy-MM-dd"));
    query.addBindValue(tournament.getEndDate().toString("yyyy-MM-dd"));
    query.addBindValue(tournament.getNumberOfRounds());
    query.addBindValue(tournament.getPairingSystem());
    query.addBindValue(tournament.getId());

    if (!query.exec())
    {
        qWarning() << "Misslyckades att uppdatera turnering i databasen:" << query.lastError().text();
    }
}

void TournamentListModel::removeById(const unsigned int &id)
{
    // Ta bort turneringen från databasen
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());

    query.prepare("DELETE FROM tournaments WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qWarning() << "Misslyckades att ta bort turneringen från databasen:" << query.lastError().text();
    }

    // Ta bort turneringen från vektorn
    std::vector<Tournament>::const_iterator it = std::remove_if(container.begin(), container.end(), [&](const Tournament &t)
    {
        return t.getId() == id; // Matcha på turnerings-ID
    });

    if (it != container.end())
    {
        container.erase(it, container.end()); // Faktiskt ta bort objektet från vektorn
    }
}


