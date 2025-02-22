#ifndef CHESSPAIRER_H
#define CHESSPAIRER_H
#include <QStackedWidget>
#include "Logger.h"
#include "PlayerListController.h"
#include "PlayerListView.h"
#include <QMainWindow>
#include "PlayerListModel.h"
#include "SettingsView.h"
#include "SettingsController.h"
#include "TournamentListController.h"
#include "TournamentListModel.h"
#include "TournamentListView.h"

/**
 * @class ChessPairer
 * @brief Huvudfönster för schackparningsprogrammet.
 *
 * Denna klass hanterar huvudfönstret och ansvarar för att initiera och hantera
 * de olika vyerna och deras respektive MVC-komponenter.
 */
class ChessPairer : public QMainWindow
{
    Q_OBJECT

public:
    /**
         * @brief Konstruktor för ChessPairer.
         * @param parent Pekare till föräldrawidgeten (nullptr som standard).
         */
    ChessPairer(QWidget *parent = nullptr);

    /**
         * @brief Destruktor för ChessPairer.
         */
    ~ChessPairer();

private:

    Logger *logger;///< Instans av 'Logger'

    // 'Models'
    TournamentListModel *tournamentListModel; ///< Modell för turneringar.
    PlayerListModel *playerListModel; ///< Modell för spelare.
    SettingsModel *settingsModel; ///< Modell för inställningar.

    // 'Views'
    TournamentListView *tournamentListView;///< Vy för turneringar.
    PlayerListView *playerListView; ///< Vy för spelare.
    SettingsView *settingsView; ///< Vy för inställningar.

    // 'Controllers'
    TournamentListController *tournamentListController; ///< Controller för turneringar.
    PlayerListController *playerListController; ///< Controller för spelare.
    SettingsController *settingsController; ///< Controller för inställningar.


    static const unsigned int DEFAULT_WINDOW_WIDTH; ///< Standardbredd för fönstret.
    static const unsigned int DEFAULT_WINDOW_HEIGHT; ///< Standardhöjd för fönstret.

    QWidget *centralWidget; ///< Huvudwidget som håller layouten.
    QStackedWidget *stackedWidget; ///< Stacked widget för att byta mellan vyer.

    /**
         * @brief Skapar programmets menyfält.
         */
    void createMenu();

    /**
         * @brief Skapar användargränssnittet.
         */
    void createUI();

    /**
         * @brief Initierar Model-View-Controller-strukturen.
         */
    void initMVC();

private slots:
    /**
         * @brief Visar vyn med alla spelare.
         */
    void showAllPlayers();

    /**
         * @brief Visar vyn med alla turneringar.
         */
    void showAllTournaments();

    /**
         * @brief Visar inställningsvyn.
         */
    void showSettingsView();
};
#endif // CHESSPAIRER_H
