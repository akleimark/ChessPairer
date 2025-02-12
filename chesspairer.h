#ifndef CHESSPAIRER_H
#define CHESSPAIRER_H

#include <QMainWindow>

class ChessPairer : public QMainWindow
{
    Q_OBJECT

    public:
        ChessPairer(QWidget *parent = nullptr);
        ~ChessPairer();

    private:
        unsigned int window_width;
        unsigned int window_height;
};
#endif // CHESSPAIRER_H
