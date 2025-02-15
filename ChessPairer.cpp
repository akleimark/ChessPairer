#include "ChessPairer.h"
#include <QMenuBar>
#include <QApplication>
#include <qsqlquery.h>
#include "PlayerListController.h"
#include "Database.h"

const unsigned int ChessPairer::DEFAULT_WINDOW_WIDTH = 700;
const unsigned int ChessPairer::DEFAULT_WINDOW_HEIGHT = 500;

ChessPairer::ChessPairer(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(ChessPairer::DEFAULT_WINDOW_WIDTH, ChessPairer::DEFAULT_WINDOW_HEIGHT);
    initMVC();
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
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

void ChessPairer::initMVC()
{
    // Initiera MVC

    settingsModel = new SettingsModel;
    settingsView = new SettingsView(settingsModel);
    settingsController = new SettingsController(settingsModel, settingsView);
    settingsView->addListeners();

    playerListModel = new PlayerListModel(settingsModel);
    playerListView = new PlayerListView(playerListModel);
    playerListController = new PlayerListController(playerListModel, playerListView);
    playerListView->addListeners();
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
    anotherView->setStyleSheet("background-color: lightblue;");
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
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    Database::getInstance()->loadPlayersFromDatabase(playerListModel);  // Hämta alla spelare från databasen
    stackedWidget->setCurrentWidget(playerListView);
    playerListModel->notifyAllViews();
}

void ChessPairer::showSettingsView()
{
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    stackedWidget->setCurrentWidget(settingsView);
    settingsModel->notifyAllViews();
}
