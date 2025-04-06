#ifndef TOURNAMENTPLAYERSVIEW_H
#define TOURNAMENTPLAYERSVIEW_H

#include <QTableWidget>
#include <QPushButton>
#include "MVC.h"
#include "TournamentPlayersModel.h"

class TournamentPlayersController;

class TournamentPlayersView : public View
{
public:
    TournamentPlayersView(TournamentPlayersModel &tournamentPlayersModel);
    virtual void updateView() override;
    virtual void addListeners() override;

private:
    TournamentPlayersModel &tournamentPlayersModel;
    TournamentPlayersController *tournamentPlayersController;
    void createUI();
    QTableWidget *availablePlayersTable;
    QTableWidget *tournamentPlayersTable;
    QPushButton *addButton;
    QPushButton *removeButton;

signals:
    void addTournamentPlayerRequested(int fideId);
};

#endif // TOURNAMENTPLAYERSVIEW_H
