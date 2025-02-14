#include "ChessPairer.h"
#include <QMenuBar>
#include <QApplication>
#include "PlayerController.h"

ChessPairer::ChessPairer(QWidget *parent)
    : QMainWindow(parent), window_width(700), window_height(500)
{
    this->resize(window_width, window_height);    

    //Initiera MVC
    playerModel = new PlayerModel;
    playerListView = new PlayerListView(playerModel);
    playerController = new PlayerController(playerModel, playerListView);

    // Lägg till exempelspelare
    playerController->addPlayer("Magnus Carlsen", 2847, 1503014);
    playerController->addPlayer("Hikaru Nakamura", 2785, 2016192);

    setCentralWidget(playerListView);
    playerModel->notifyAllViews();

    createUI();
}

ChessPairer::~ChessPairer()
{
    delete playerController;
    delete playerListView;
    delete playerModel;
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

    //Arkiv-menyn
    QMenu *fileMenu = menuBar->addMenu("Arkiv");
    QAction *exitAction = new QAction("Avsluta", this);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(exitAction);

    //Verktygs-menyn
    QMenu *toolsMenu = menuBar->addMenu("Verktyg");
    QAction *showPlayersAction = new QAction("Visa alla spelare", this);
    connect(showPlayersAction, &QAction::triggered, this, &ChessPairer::showAllPlayers);
    toolsMenu->addAction(showPlayersAction);
}

void ChessPairer::showAllPlayers()
{
    stackedWidget->setCurrentWidget(playerListView);
    playerModel->notifyAllViews();
}

