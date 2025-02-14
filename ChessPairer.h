#ifndef CHESSPAIRER_H
#define CHESSPAIRER_H
#include <QStackedWidget>
#include "PlayerController.h"
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

        PlayerController *playerController;
        PlayerListView *playerListView;
        PlayerModel *playerModel;

        unsigned int window_width;
        unsigned int window_height;

        QWidget *centralWidget;   // Huvudwidget som håller layouten
        QStackedWidget *stackedWidget; // Stacked widget för att byta vyer

        void createMenu(); // Skapar menyfältet
        void createUI();


    private slots:
        void showAllPlayers();

};
#endif // CHESSPAIRER_H
