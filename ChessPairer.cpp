#include "ChessPairer.h"
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <qsqlquery.h>
#include "PlayerListController.h"
#include "Database.h"

const unsigned int ChessPairer::DEFAULT_WINDOW_WIDTH = 700;
const unsigned int ChessPairer::DEFAULT_WINDOW_HEIGHT = 500;
ChessPairer* ChessPairer::instance = nullptr;

ChessPairer::ChessPairer()
    : QMainWindow(nullptr)
{
    logger = Logger::getInstance();
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
    delete tournamentListView;
    delete tournamentListModel;
    delete tournament;
}

ChessPairer* ChessPairer::getInstance()
{
    if (!instance)
    {
        instance = new ChessPairer();
    }
    return instance;
}

void ChessPairer::initMVC()
{
    // Initiera MVC

    tournament = nullptr;

    settingsModel = new SettingsModel;
    settingsView = new SettingsView(settingsModel);
    settingsController = new SettingsController(settingsModel, settingsView);
    settingsView->addListeners();

    playerListModel = new PlayerListModel(settingsModel);
    playerListView = new PlayerListView(playerListModel);
    playerListController = new PlayerListController(playerListModel, playerListView);
    playerListView->addListeners();

    tournamentListModel = new TournamentListModel(tournament, settingsModel);
    tournamentListView = new TournamentListView(tournamentListModel);
    tournamentListController = new TournamentListController(tournamentListModel, tournamentListView);
    tournamentListView->addListeners();

    logger->logInfo("MVC initierades utan problem.");
}

void ChessPairer::createUI()
{
    // Skapar meny-systemet
    createMenu();

    // Skapa central widget och layout
    centralWidget = new QWidget(this);
    stackedWidget = new QStackedWidget();

    // Vi initierar en startvy
    QWidget *startView = new QWidget();
    startView->setStyleSheet("background-color: lightblue;");

    // Alla vyerna läggs till till layouten
    stackedWidget->addWidget(startView);
    stackedWidget->addWidget(settingsView);
    stackedWidget->addWidget(playerListView);
    stackedWidget->addWidget(tournamentListView);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(stackedWidget);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    stackedWidget->setCurrentWidget(startView);
    logger->logInfo("Layouten sattes upp utan problem.");
    populateMenu();
}

void ChessPairer::createMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Arkiv-menyn
    QMenu *fileMenu = menuBar->addMenu("Arkiv");
    exitAction = new QAction("Avsluta", this);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(exitAction);

    // Verktygs-menyn
    QMenu *toolsMenu = menuBar->addMenu("Verktyg");
    showPlayersAction = new QAction("Visa alla spelare", this);
    connect(showPlayersAction, &QAction::triggered, this, &ChessPairer::showAllPlayers);
    toolsMenu->addAction(showPlayersAction);

    showTournamentsAction = new QAction("Visa alla turneringar", this);
    connect(showTournamentsAction, &QAction::triggered, this, &ChessPairer::showAllTournaments);
    toolsMenu->addAction(showTournamentsAction);

    // Turneringsmenyn
    QMenu *tournamentMenu = menuBar->addMenu("#");
    tournamentPlayersAction = new QAction("Turneringsspelare", this);
    connect(tournamentPlayersAction, &QAction::triggered, this, &ChessPairer::showTournamentPlayers);
    tournamentMenu->addAction(tournamentPlayersAction);

    // Menyn 'Övrigt'
    QMenu *miscMenu = menuBar->addMenu("Övrigt");
    showSettingsAction = new QAction("Inställningar", this);
    connect(showSettingsAction, &QAction::triggered, this, &ChessPairer::showSettingsView);
    miscMenu->addAction(showSettingsAction);
}

void ChessPairer::populateMenu()
{
    tournament = tournamentListModel->getTournament();
    tournamentPlayersAction->setEnabled(tournament != nullptr);
}

void ChessPairer::showAllPlayers()
{
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    Database::getInstance()->loadPlayersFromDatabase(playerListModel);  // Hämta alla spelare från databasen
    stackedWidget->setCurrentWidget(playerListView);
    playerListModel->notifyAllViews();
}

void ChessPairer::showAllTournaments()
{
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    Database::getInstance()->loadTournamentsFromDatabase(tournamentListModel);  // Hämta alla turneringar från databasen
    stackedWidget->setCurrentWidget(tournamentListView);
    tournamentListModel->notifyAllViews();
}

void ChessPairer::showTournamentPlayers()
{

}

void ChessPairer::showSettingsView()
{
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    stackedWidget->setCurrentWidget(settingsView);
    settingsModel->notifyAllViews();
}
