#ifndef TOURNAMENTLISTMODEL_H
#define TOURNAMENTLISTMODEL_H

#include <QString>
#include <QDate>
#include "Interfaces.h"
#include "ListModel.h"
#include "MVC.h"
#include "SettingsModel.h"

class Tournament : public PrintInterface
{
public:
    Tournament();
    explicit Tournament(const unsigned &id, const QString &name = DEFAULT_TOURNAMENT_NAME,
                        const QDate &startDate = Tournament::DEFAULT_START_DATE, const QDate &endDate = Tournament::DEFAULT_END_DATE,
                        const unsigned int &numberOfRounds = Tournament::DEFAULT_NUMBER_OF_ROUNDS, const QString &pairingSystem = Tournament::DEFAULT_PAIRING_SYSTEM);
    virtual void print() const override;

private:
    const unsigned int id;
    QString name;
    QDate startDate;
    QDate endDate;
    unsigned int numberOfRounds;
    QString pairingSystem;
    const static unsigned int DEFAULT_NUMBER_OF_ROUNDS;
    const static QString DEFAULT_PAIRING_SYSTEM;
    const static QString DEFAULT_TOURNAMENT_NAME;
    const static QDate DEFAULT_START_DATE;
    const static QDate DEFAULT_END_DATE;
};

class TournamentListModel : public ListModel<Tournament>
{
public:
    explicit TournamentListModel(SettingsModel *settingsModel);

};

#endif // TOURNAMENTLISTMODEL_H
