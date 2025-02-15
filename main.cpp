#include "ChessPairer.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    QFile file("styles.qss");  // Filen ska ligga i resurser eller i samma katalog
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();
    }
    else
    {
        qDebug() << "Filen hittades ej.";
    }
    ChessPairer chessPairer;
    chessPairer.show();
    return a.exec();
}
