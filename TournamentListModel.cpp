#include "TournamentListModel.h"


const unsigned int Tournament::DEFAULT_NUMBER_OF_ROUNDS = 7;
const QString Tournament::DEFAULT_PAIRING_SYSTEM = "Monrad";
const QString Tournament::DEFAULT_TOURNAMENT_NAME = "Ny turnering";
const QDate Tournament::DEFAULT_START_DATE = QDate::currentDate();
const QDate Tournament::DEFAULT_END_DATE = QDate::currentDate();

Tournament::Tournament(const unsigned &id, const QString &name,
                       const QDate &startDate, const QDate &endDate, const unsigned int &numberOfRounds, const QString &pairingSystem):
    id(id), name(name), startDate(startDate), endDate(endDate), numberOfRounds(numberOfRounds), pairingSystem(pairingSystem) {}

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


TournamentListModel::TournamentListModel(SettingsModel *settingsModel):
    ListModel<Tournament>(settingsModel)
{

}



