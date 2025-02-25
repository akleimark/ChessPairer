#include "ChessPairer.h"
#include "Logger.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    Logger *logger = Logger::getInstance();
    QApplication a(argc, argv);
    QFile file("styles.qss");  // Filen ska ligga i resurser eller i samma katalog
    if (file.open(QFile::ReadOnly))
    {
        logger->logInfo("CSS-filen laddades.");
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();
    }
    else
    {        
        logger->logWarning("CSS-filen hittades ej.");
    }

    ChessPairer::getInstance()->show();
    return a.exec();
}
