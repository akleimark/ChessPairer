#include "chesspairer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessPairer w;
    w.show();
    return a.exec();
}
