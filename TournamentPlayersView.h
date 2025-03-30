#ifndef TOURNAMENTPLAYERSVIEW_H
#define TOURNAMENTPLAYERSVIEW_H

#include <QTableWidget>
#include <QPushButton>
#include "MVC.h"
#include "TournamentPlayersModel.h"

class TournamentPlayersView : public View
{
public:
    TournamentPlayersView(TournamentPlayersModel *tournamentPlayersModel);
    virtual void updateView() const override;
    virtual void addListeners() override;

private:
    TournamentPlayersModel *tournamentPlayersModel;
    void createUI();
    QTableWidget *availablePlayersTable;
    QTableWidget *tournamentPlayersTable;
    QPushButton *addButton;
    QPushButton *removeButton;
};

#endif // TOURNAMENTPLAYERSVIEW_H
