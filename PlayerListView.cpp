#include "PlayerListView.h"
#include "PlayerListController.h"
#include "PlayerListModel.h"

PlayerListView::PlayerListView(PlayerListModel *model):
    View(model)
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
    addPlayerButton = new QPushButton("Lägg till spelare", buttonWidget);

    buttonLayout->addWidget(addPlayerButton);
    buttonLayout->addStretch(); // Skapar utrymme efter knappen för att hålla den vänsterjusterad
    buttonWidget->setLayout(buttonLayout);

    layout->addWidget(buttonWidget); // Lägg till widgeten ovanför tabellen
}

void PlayerListView::addListeners()
{
    PlayerListController* playerListController = dynamic_cast<PlayerListController*>(controller); // Ta bort 'const'
    connect(addPlayerButton, &QPushButton::clicked, playerListController, &PlayerListController::onAddPlayerClicked);
}

void PlayerListView::updateView() const
{
    PlayerListModel &playerListModel = *static_cast<PlayerListModel*>(model);
    qDebug() << "Font:" << playerListModel.getSettingsModel()->getSettingByType("font");
    const auto &players = playerListModel.getPlayers();

    tableWidget->setFont(QFont(playerListModel.getSettingsModel()->getSettingByType("font"), 12, 400));

    tableWidget->setRowCount(players.size());

    // Justera tabellens kolumner som proportioner av den totala bredden
    int tableWidth = tableWidget->viewport()->width();

    // Här bestämmer vi hur bred varje kolumn ska vara som procentandel av den totala bredden
    tableWidget->setColumnWidth(0, tableWidth * 0.4);  // 40% för namn
    tableWidget->setColumnWidth(1, tableWidth * 0.3);  // 30% för rating
    tableWidget->setColumnWidth(2, tableWidth * 0.3);  // 30% för FIDE-id

    // Fyll tabellen med data
    for (size_t i = 0; i < players.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(players[i].getName()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(players[i].getRating())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(players[i].getFideId())));
    }

}

void PlayerListView::resizeEvent(QResizeEvent *event)
{
    updateView();
    QWidget::resizeEvent(event);  // Don't forget to call the base class implementation

}
