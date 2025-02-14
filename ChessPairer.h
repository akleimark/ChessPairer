#ifndef CHESSPAIRER_H
#define CHESSPAIRER_H
#include <QStackedWidget>
#include "PlayerListController.h"
#include "PlayerListView.h"
#include <QMainWindow>
#include "PlayerModel.h"

class ChessPairer : public QMainWindow
{
    Q_OBJECT

    public:
        ChessPairer(QWidget *parent = nullptr);
        ~ChessPairer();

    private:

        PlayerListController *playerListController;
        PlayerListView *playerListView;
        PlayerModel *playerModel;

        unsigned int window_width;
        unsigned int window_height;

        QWidget *centralWidget;   // Huvudwidget som håller layouten
        QStackedWidget *stackedWidget; // Stacked widget för att byta vyer

        void createMenu(); // Skapar menyfältet
        void createUI();
        void loadPlayersFromDatabase();

    private slots:
        void showAllPlayers();

};
#endif // CHESSPAIRER_H
