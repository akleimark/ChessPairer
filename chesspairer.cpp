#include "chesspairer.h"

ChessPairer::ChessPairer(QWidget *parent)
    : QMainWindow(parent), window_width(700), window_height(500)
{
    this->resize(window_width, window_height);
}

ChessPairer::~ChessPairer() {}
