#include "TournamentListView.h"
#include "TournamentListController.h"

TournamentListView::TournamentListView(TournamentListModel *model):
    View(model), tournamentListModel(model)
{
    createUI();
}

void TournamentListView::createUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Skapar tabellen och dess design
    tableWidget = new QTableWidget(this);
    layout->addWidget(tableWidget);
    setLayout(layout);

    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels({"Id", "Namn", "Startdatum", "Slutdatum", "Antal ronder", "Lottningssystem"});

    // Skapa en separat widget för knappen
    buttonWidget = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);

    // Skapa knapparna
    addTournamentButton = new QPushButton("Lägg till en turnering", buttonWidget);
    removeTournamentButton = new QPushButton("Ta bort turneringen", buttonWidget);
    removeTournamentButton->setVisible(false);
    buttonLayout->addWidget(addTournamentButton);
    buttonLayout->addWidget(removeTournamentButton);
    buttonLayout->addStretch(); // Skapar utrymme efter knappen för att hålla den vänsterjusterad
    buttonWidget->setLayout(buttonLayout);

    layout->addWidget(buttonWidget); // Lägg till widgeten ovanför tabellen
}

void TournamentListView::addListeners()
{
    TournamentListController* tournamentListController = dynamic_cast<TournamentListController*>(controller);
    connect(addTournamentButton, &QPushButton::clicked, tournamentListController, &TournamentListController::onAddTournamentClicked);

    // Kopplar QTableWidget:s inbyggda cellChanged till vår onCellChanged
    connect(tableWidget, &QTableWidget::cellChanged, this, &TournamentListView::onCellChanged);

    // Kopplar borttagningsknappen till onRemovePlayerClicked
    connect(removeTournamentButton, &QPushButton::clicked,
            this, &TournamentListView::onRemoveTournamentClicked);

    connect(tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TournamentListView::onSelectionChanged);

    // Koppla signalen från PlayerListView till PlayerListController
    connect(this, &TournamentListView::removeTournamentRequested,
            tournamentListController, &TournamentListController::onRemoveTournamentRequested);
}

void TournamentListView::updateView() const
{
    tableWidget->blockSignals(true); // Blockera signaler för att undvika onCellChanged-loop
    tableWidget->setFont(QFont(tournamentListModel->getSettingsModel()->getSettingByType("font"), 12, 400));
    tableWidget->setRowCount(tournamentListModel->size());

    // Justera tabellens kolumner som proportioner av den totala bredden
    const unsigned int TABLE_WIDTH = tableWidget->viewport()->width();
    tableWidget->setColumnWidth(0, TABLE_WIDTH * 0.05);  // 5% för 'id'
    tableWidget->setColumnWidth(1, TABLE_WIDTH * 0.30);  // 30% för 'name'
    tableWidget->setColumnWidth(2, TABLE_WIDTH * 0.15);  // 15% för 'startDate'
    tableWidget->setColumnWidth(3, TABLE_WIDTH * 0.15);  // 15% för 'endDate'
    tableWidget->setColumnWidth(4, TABLE_WIDTH * 0.15);  // 15% för 'numberOfRounds'
    tableWidget->setColumnWidth(5, TABLE_WIDTH * 0.2);   // 20% för 'pairingSystem'

    // Fyll tabellen med data
    int rowIndex = 0;
    for (std::vector<Tournament>::const_iterator it = tournamentListModel->cbegin(); it != tournamentListModel->cend(); ++it)
    {
        const Tournament& tournament = *it;  // Referens till turneringen i vektorn
        int columnNumber = 0;

        // Id (Icke-redigerbar)
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(tournament.getId()));
        idItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); // Inaktivera redigering
        tableWidget->setItem(rowIndex, columnNumber++, idItem);

        // Namn (redigerbar)
        tableWidget->setItem(rowIndex, columnNumber++, new QTableWidgetItem(tournament.getName()));

        // Startdatum (redigerbar, konverterat till QString)
        tableWidget->setItem(rowIndex, columnNumber++, new QTableWidgetItem(tournament.getStartDate().toString("yyyy-MM-dd")));

        // Slutdatum (redigerbar, konverterat till QString)
        tableWidget->setItem(rowIndex, columnNumber++, new QTableWidgetItem(tournament.getEndDate().toString("yyyy-MM-dd")));

        // Antal ronder (redigerbar, konverterat till QString)
        tableWidget->setItem(rowIndex, columnNumber++, new QTableWidgetItem(QString::number(tournament.getNumberOfRounds())));

        // Lottningssystem (redigerbar)
        tableWidget->setItem(rowIndex, columnNumber++, new QTableWidgetItem(tournament.getPairingSystem()));
    }

    tableWidget->blockSignals(false); // Slå på signaler igen
}


void TournamentListView::onCellChanged(int row, int column)
{
    QTableWidgetItem *item = tableWidget->item(row, column);
    if (item)
    {
        emit cellChanged(row, column, item->text());
    }
}

void TournamentListView::onSelectionChanged()
{
    bool hasSelection = !tableWidget->selectedItems().isEmpty();
    removeTournamentButton->setVisible(hasSelection);
}

// Uppdaterad metod för att hantera borttagning
void TournamentListView::onRemoveTournamentClicked()
{
    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
    if (selectedItems.isEmpty()) return;

    int row = selectedItems.first()->row();
    unsigned int id = tableWidget->item(row, 0)->text().toUInt();

    // Skicka signalen till controllern
    emit this->removeTournamentRequested(id);
}
