#include "PlayerListView.h"
#include "PlayerModel.h"

PlayerListView::PlayerListView(PlayerModel *model):
    View(model)
{
    createUI();
}

void PlayerListView::createUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    layout->addWidget(tableWidget);
    setLayout(layout);

    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"Namn", "Rating", "FIDE-ID"});
}

void PlayerListView::updateView()
{
    PlayerModel &playerModel = *static_cast<PlayerModel*>(model);
    const auto &players = playerModel.getPlayers();

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
