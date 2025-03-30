#include "TournamentPlayersController.h"
#include "TournamentPlayersView.h"
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
#include <QTableWidgetItem>
#include <QHeaderView>

TournamentPlayersView::TournamentPlayersView(TournamentPlayersModel *tournamentPlayersModel):
    tournamentPlayersModel(tournamentPlayersModel)
{
    createUI();
}

void TournamentPlayersView::createUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Tillgängliga spelare
    QLabel *availableLabel = new QLabel("Tillgängliga spelare", this);
    availableLabel->setAlignment(Qt::AlignHCenter);
    availablePlayersTable = new QTableWidget(this);
    availablePlayersTable->setColumnCount(2);
    availablePlayersTable->setHorizontalHeaderLabels({"FIDE-Id", "Namn"});
    availablePlayersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    availablePlayersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    QVBoxLayout *availableLayout = new QVBoxLayout;
    availableLayout->addWidget(availableLabel);
    availableLayout->addWidget(availablePlayersTable);

    // Turneringsspelare
    QLabel *tournamentLabel = new QLabel("Turneringsspelare", this);
    tournamentLabel->setAlignment(Qt::AlignHCenter);
    tournamentPlayersTable = new QTableWidget(this);
    tournamentPlayersTable->setColumnCount(2);
    tournamentPlayersTable->setHorizontalHeaderLabels({"FIDE-Id", "Namn"});
    tournamentPlayersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    tournamentPlayersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    QVBoxLayout *tournamentLayout = new QVBoxLayout;
    tournamentLayout->addWidget(tournamentLabel);
    tournamentLayout->addWidget(tournamentPlayersTable);

    // Knappar i mitten
    addButton = new QPushButton(this);
    addButton->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));
    removeButton = new QPushButton(this);
    removeButton->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addStretch();

    // Huvudlayout
    QHBoxLayout *tablesLayout = new QHBoxLayout;
    tablesLayout->addLayout(availableLayout);
    tablesLayout->addLayout(buttonLayout);
    tablesLayout->addLayout(tournamentLayout);

    mainLayout->addLayout(tablesLayout);
}



void TournamentPlayersView::updateView() const
{
    PlayerListModel *pModel = tournamentPlayersModel->getPlayerListModel();
    availablePlayersTable->setRowCount(pModel->size());
    int rowIndex = 0;
    for (std::vector<Player*>::const_iterator it = pModel->cbegin(); it != pModel->cend(); ++it)
    {       
        const Player* player = *it;  // Pekare till spelare i listan
        int columnNumber = 0;

        QTableWidgetItem *fideIdItem = new QTableWidgetItem(QString::number(player->getFideId()));
        fideIdItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); // Inaktivera redigering
        availablePlayersTable->setItem(rowIndex, columnNumber++, fideIdItem);

        QTableWidgetItem *nameItem = new QTableWidgetItem(player->getName());
        nameItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); // Inaktivera redigering
        availablePlayersTable->setItem(rowIndex++, columnNumber++, nameItem);

    }

    availablePlayersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tournamentPlayersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void TournamentPlayersView::addListeners()
{
    TournamentPlayersController* tournamentPlayersController = dynamic_cast<TournamentPlayersController*>(controller);
    connect(addButton, &QPushButton::clicked, tournamentPlayersController, &TournamentPlayersController::onAddTournamentPlayerClicked);
}
