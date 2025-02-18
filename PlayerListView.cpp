#include "PlayerListView.h"
#include "PlayerListController.h"
#include "PlayerListModel.h"

PlayerListView::PlayerListView(PlayerListModel *model):
    View(model), playerListModel(model)
{
    createUI();
}

void PlayerListView::createUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Skapar tabellen och dess design
    tableWidget = new QTableWidget(this);
    layout->addWidget(tableWidget);
    setLayout(layout);

    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"Namn", "Rating", "FIDE-ID"});

    // Skapa en separat widget för knappen
    buttonWidget = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);

    // Skapa knapparna
    addPlayerButton = new QPushButton("Lägg till en spelare", buttonWidget);
    removePlayerButton = new QPushButton("Ta bort spelaren", buttonWidget);
    removePlayerButton->setVisible(false);
    buttonLayout->addWidget(addPlayerButton);
    buttonLayout->addWidget(removePlayerButton);
    buttonLayout->addStretch(); // Skapar utrymme efter knappen för att hålla den vänsterjusterad
    buttonWidget->setLayout(buttonLayout);

    layout->addWidget(buttonWidget); // Lägg till widgeten ovanför tabellen
}

void PlayerListView::addListeners()
{
    PlayerListController* playerListController = dynamic_cast<PlayerListController*>(controller);
    connect(addPlayerButton, &QPushButton::clicked, playerListController, &PlayerListController::onAddPlayerClicked);

    // Kopplar QTableWidget:s inbyggda cellChanged till vår onCellChanged
    connect(tableWidget, &QTableWidget::cellChanged, this, &PlayerListView::onCellChanged);

    // Kopplar borttagningsknappen till onRemovePlayerClicked
    connect(removePlayerButton, &QPushButton::clicked,
            this, &PlayerListView::onRemovePlayerClicked);

    connect(tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &PlayerListView::onSelectionChanged);

    // Koppla signalen från PlayerListView till PlayerListController
    connect(this, &PlayerListView::removePlayerRequested,
            playerListController, &PlayerListController::onRemovePlayerRequested);
}

void PlayerListView::updateView() const
{
    tableWidget->blockSignals(true); // Blockera signaler för att undvika onCellChanged-loop
    tableWidget->setFont(QFont(playerListModel->getSettingsModel()->getSettingByType("font"), 12, 400));
    tableWidget->setRowCount(playerListModel->size());

    // Justera tabellens kolumner som proportioner av den totala bredden
    const unsigned int TABLE_WIDTH = tableWidget->viewport()->width();

    // Här bestämmer vi hur bred varje kolumn ska vara som procentandel av den totala bredden
    tableWidget->setColumnWidth(0, TABLE_WIDTH * 0.4);  // 40% för namn
    tableWidget->setColumnWidth(1, TABLE_WIDTH * 0.3);  // 30% för rating
    tableWidget->setColumnWidth(2, TABLE_WIDTH * 0.3);  // 30% för FIDE-id

    // Fyll tabellen med data
    for (std::vector<Player>::const_iterator it = playerListModel->cbegin(); it != playerListModel->cend(); ++it)
    {
        const Player& player = *it;  // Referens till spelaren i vektorn

        // Namn (redigerbar)
        tableWidget->setItem(std::distance(playerListModel->cbegin(), it), 0, new QTableWidgetItem(player.getName()));

        // Rating (redigerbar)
        tableWidget->setItem(std::distance(playerListModel->cbegin(), it), 1, new QTableWidgetItem(QString::number(player.getRating())));

        // FIDE-ID (icke-redigerbar)
        QTableWidgetItem *fideItem = new QTableWidgetItem(QString::number(player.getFideId()));
        fideItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); // Inaktivera redigering
        tableWidget->setItem(std::distance(playerListModel->cbegin(), it), 2, fideItem);
    }

    tableWidget->blockSignals(false); // Slå på signaler igen
}


void PlayerListView::onCellChanged(int row, int column)
{
    QTableWidgetItem *item = tableWidget->item(row, column);
    if (item)
    {
        emit cellChanged(row, column, item->text());
    }
}

void PlayerListView::onSelectionChanged()
{
    bool hasSelection = !tableWidget->selectedItems().isEmpty();
    removePlayerButton->setVisible(hasSelection);
}

// Uppdaterad metod för att hantera borttagning
void PlayerListView::onRemovePlayerClicked()
{
    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
    if (selectedItems.isEmpty()) return;

    int row = selectedItems.first()->row();
    unsigned int fideId = tableWidget->item(row, 2)->text().toUInt();

    // Skicka signalen till controllern
    emit removePlayerRequested(fideId);
}
