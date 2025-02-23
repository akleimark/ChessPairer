#include "Logger.h"

Logger* Logger::instance = nullptr;
const QString Logger::FILE_NAME = "logfile.log";
const QString Logger::WARNING = "WARNING";
const QString Logger::INFO = "INFO";
const QString Logger::ERROR = "ERROR";

// Privat konstruktor
Logger::Logger()
{
    logFile.setFileName("application.log");
    if (!logFile.open(QIODevice::Append | QIODevice::Text))
    {
        qCritical() << "Failed to open log file!";
        std::exit(EXIT_FAILURE);
    }
}

// Destruktor
Logger::~Logger()
{
    if (logFile.isOpen())
    {
        logFile.close();
    }    
}

// Get the singleton instance
Logger *Logger::getInstance()
{
    if(Logger::instance == nullptr)
    {
        instance = new Logger;
    }

    return instance;
}

// Generisk logg-method
void Logger::log(const QString &level, const QString &message)
{
    QMutexLocker locker(&logMutex);

    const QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH.mm.ss");
    const QString logMessage = QString("%1 [%2] %3").arg(timestamp, level, message);

    // Logga till konsolen
    qDebug().noquote() << logMessage;

    // Logga till loggfilen.
    if (logFile.isOpen())
    {
        QTextStream out(&logFile);
        out << logMessage << Qt::endl;
    }
}

void Logger::logInfo(const QString &message)
{
    log(Logger::INFO, message);
}

void Logger::logWarning(const QString &message)
{
    log(Logger::WARNING, message);
}

void Logger::logError(const QString &message)
{
    log(Logger::ERROR, message);
    std::exit(EXIT_FAILURE);
}
