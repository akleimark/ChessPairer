#include "ChessPairer.h"
#include <QMenuBar>
#include <QApplication>
#include <qsqlquery.h>
#include "PlayerListController.h"
#include "Database.h"

ChessPairer::ChessPairer(QWidget *parent)
    : QMainWindow(parent), window_width(700), window_height(500)
{
    this->resize(window_width, window_height);

    // Initiera MVC

    settingsModel = new SettingsModel;
    settingsView = new SettingsView(settingsModel);
    settingsController = new SettingsController(settingsModel, settingsView);
    settingsView->addListeners();

    playerListModel = new PlayerListModel(settingsModel);
    playerListView = new PlayerListView(playerListModel);
    playerListController = new PlayerListController(playerListModel, playerListView);
    playerListView->addListeners();

    loadSettingsFromDatabase();

    createUI();
}

ChessPairer::~ChessPairer()
{
    delete playerListController;
    delete playerListView;
    delete playerListModel;
    delete settingsView;
    delete settingsModel;
    delete settingsController;
}

void ChessPairer::loadPlayersFromDatabase()
{
    playerListModel->reset();
    QSqlQuery query = Database::getInstance()->selectQuery("SELECT name, rating, fide_id FROM players");

    while (query.next())
    {
        QString name = query.value(0).toString();
        int rating = query.value(1).toInt();
        int fideId = query.value(2).toInt();
        playerListModel->addPlayerToContainer(Player(name, rating, fideId));  // Lägg till spelare i MVC
    }
}

void ChessPairer::loadSettingsFromDatabase()
{
    settingsModel->reset();
    QSqlQuery query = Database::getInstance()->selectQuery("SELECT type, value FROM settings");

    while (query.next())
    {
        QString type = query.value(0).toString();
        QString value = query.value(1).toString();
        settingsModel->addSettingToContainer(Setting(type, value));  // Lägg till inställning i MVC
    }
}

void ChessPairer::createUI()
{
    // Skapar meny-systemet
    createMenu();

    // Skapa central widget och layout
    centralWidget = new QWidget(this);
    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(playerListView); // Lägg till spelarfönstret

    // Exempel på en annan vy (kan vara en annan QWidget)
    QWidget *anotherView = new QWidget();
    anotherView->setStyleSheet("background-color: lightgray;");
    stackedWidget->addWidget(anotherView); // Lägg till en extra vy

    stackedWidget->addWidget(settingsView);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(stackedWidget);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    stackedWidget->setCurrentWidget(anotherView);
}


void ChessPairer::createMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Arkiv-menyn
    QMenu *fileMenu = menuBar->addMenu("Arkiv");
    QAction *exitAction = new QAction("Avsluta", this);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(exitAction);

    // Verktygs-menyn
    QMenu *toolsMenu = menuBar->addMenu("Verktyg");
    QAction *showPlayersAction = new QAction("Visa alla spelare", this);
    connect(showPlayersAction, &QAction::triggered, this, &ChessPairer::showAllPlayers);
    toolsMenu->addAction(showPlayersAction);

    // Menyn 'Övrigt'
    QMenu *miscMenu = menuBar->addMenu("Övrigt");
    QAction *showSettingsAction = new QAction("Inställningar", this);
    connect(showSettingsAction, &QAction::triggered, this, &ChessPairer::showSettingsView);
    miscMenu->addAction(showSettingsAction);
}

void ChessPairer::showAllPlayers()
{
    loadSettingsFromDatabase(); // Hämta inställningarna från databasen
    loadPlayersFromDatabase();  // Hämta alla spelare från databasen
    stackedWidget->setCurrentWidget(playerListView);
    playerListModel->notifyAllViews();
}

void ChessPairer::showSettingsView()
{
    loadSettingsFromDatabase(); // Hämta inställningarna från databasen
    stackedWidget->setCurrentWidget(settingsView);
    settingsModel->notifyAllViews();
}
