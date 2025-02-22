#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>
#include <QDebug>

/**
 * @class Logger
 * @brief Singleton-klass för loggning av meddelanden med olika loggnivåer.
 *
 * Denna klass hanterar loggning av meddelanden på olika nivåer, som info, varning och fel.
 * Den använder sig av en loggfil för att lagra meddelandena och implementerar en Singleton-design för att garantera
 * att endast en instans av Logger finns i hela applikationen.
 */
class Logger
{
public:
    /**
     * @brief Förhindrar kopiering av Logger-instansen.
     */
    Logger(const Logger &) = delete;

    /**
     * @brief Förhindrar tilldelning av en annan Logger-instans.
     * @return En referens till den nuvarande Logger-instansen.
     */
    Logger &operator=(const Logger &) = delete;

    /**
     * @brief Hämtar den enda instansen av Logger.
     * @return En pekare till Logger-instansen.
     */
    static Logger *getInstance();

    /**
     * @brief Loggar ett informationsmeddelande.
     * @param message Meddelandet att logga.
     */
    void logInfo(const QString &message);

    /**
     * @brief Loggar ett varningsmeddelande.
     * @param message Meddelandet att logga.
     */
    void logWarning(const QString &message);

    /**
     * @brief Loggar ett felmeddelande.
     * @param message Meddelandet att logga.
     */
    void logError(const QString &message);

private:
    /**
     * @brief Privat konstruktor för Logger.
     * Förhindrar skapandet av objekt utanför klassen.
     */
    Logger();

    /**
     * @brief Privat destruktor för Logger.
     */
    ~Logger();

    /**
     * @brief Filnamnet för loggfilen.
     */
    const static QString FILE_NAME;

    /**
     * @brief Sträng för loggnivån "warning".
     */
    const static QString WARNING;

    /**
     * @brief Sträng för loggnivån "info".
     */
    const static QString INFO;

    /**
     * @brief Sträng för loggnivån "error".
     */
    const static QString ERROR;

    /**
     * @brief Hjälpmetod för att logga meddelanden med specificerad loggnivå.
     * @param level Loggnivån (info, warning, error).
     * @param message Meddelandet att logga.
     */
    void log(const QString &level, const QString &message);

    /**
     * @brief Loggfilen som meddelanden skrivs till.
     */
    QFile logFile;

    /**
     * @brief Mutex för att säkerställa trådsäker loggning.
     */
    QMutex logMutex;

    /**
     * @brief Singleton-instansen av Logger.
     */
    static Logger* instance;
};


#endif // LOGGER_H
