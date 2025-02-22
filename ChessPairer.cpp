#include "ChessPairer.h"
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <qsqlquery.h>
#include "PlayerListController.h"
#include "Database.h"

const unsigned int ChessPairer::DEFAULT_WINDOW_WIDTH = 700;
const unsigned int ChessPairer::DEFAULT_WINDOW_HEIGHT = 500;

ChessPairer::ChessPairer(QWidget *parent)
    : QMainWindow(parent)
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
}

void ChessPairer::initMVC()
{
    try
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

        tournamentListModel = new TournamentListModel(settingsModel);
        tournamentListView = new TournamentListView(tournamentListModel);
        tournamentListController = new TournamentListController(tournamentListModel, tournamentListView);
        tournamentListView->addListeners();

        logger->logInfo("MVC initierades utan problem.");
    }
    catch (const std::bad_alloc &error)
    {
        logger->logError(QString("Memory allocation failed: %1").arg(error.what()));
        QMessageBox::critical(nullptr, "Error", "Memory allocation failed. The application will close.");
        std::exit(EXIT_FAILURE);
    }
    catch (const std::runtime_error &error)
    {
        logger->logError(QString("Runtime error: %1").arg(error.what()));
        QMessageBox::critical(nullptr, "Error", QString("Runtime error occurred: %1").arg(error.what()));
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception &error)
    {
        logger->logError(QString("Standard exception: %1").arg(error.what()));
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(error.what()));
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        logger->logError("Unknown error occurred.");
        QMessageBox::critical(nullptr, "Error", "An unknown error occurred. The application will close.");
        std::exit(EXIT_FAILURE);
    }
}

void ChessPairer::createUI()
{
    try
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
    }
    catch (const std::bad_alloc &error)
    {
        logger->logError(QString("Memory allocation failed: %1").arg(error.what()));
        QMessageBox::critical(nullptr, "Error", "Memory allocation failed. The application will close.");
        std::exit(EXIT_FAILURE);
    }
    catch (const std::runtime_error &error)
    {
        logger->logError(QString("Runtime error: %1").arg(error.what()));
        QMessageBox::critical(nullptr, "Error", QString("Runtime error occurred: %1").arg(error.what()));
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception &error)
    {
        logger->logError(QString("Standard exception: %1").arg(error.what()));
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(error.what()));
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        logger->logError("Unknown error occurred.");
        QMessageBox::critical(nullptr, "Error", "An unknown error occurred. The application will close.");
        std::exit(EXIT_FAILURE);
    }
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

    QAction *showTournamentsAction = new QAction("Visa alla turneringar", this);
    connect(showTournamentsAction, &QAction::triggered, this, &ChessPairer::showAllTournaments);
    toolsMenu->addAction(showTournamentsAction);

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

void ChessPairer::showAllTournaments()
{

    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    Database::getInstance()->loadTournamentsFromDatabase(tournamentListModel);  // Hämta alla turneringar från databasen
    stackedWidget->setCurrentWidget(tournamentListView);
    tournamentListModel->notifyAllViews();
}

void ChessPairer::showSettingsView()
{
    Database::getInstance()->loadSettingsFromDatabase(settingsModel); // Hämta inställningarna från databasen
    stackedWidget->setCurrentWidget(settingsView);
    settingsModel->notifyAllViews();
}
