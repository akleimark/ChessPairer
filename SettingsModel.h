#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QString>
#include <QList>
#include "MVC.h"

/**
 * @class Setting
 * @brief Representerar en enskild inställning.
 *
 * Denna klass lagrar information om en inställning, inklusive dess typ och värde.
 * Det används för att hantera individuella inställningar i systemet.
 */
class Setting
{
public:
    /**
     * @brief Konstruktor för `Setting`.
     *
     * Skapar en instans av `Setting` med specificerad typ och värde.
     *
     * @param type Typen av inställningen (t.ex. "font", "theme").
     * @param value Värdet för inställningen (t.ex. "Arial", "Dark").
     */
    Setting(const QString &type, const QString &value) :
        type(type), value(value) {}

    /**
     * @brief Hämtar typen av inställningen.
     *
     * Denna metod returnerar typen för inställningen, t.ex. "font" eller "theme".
     *
     * @return Typen av inställningen.
     */
    QString getType() const { return type; }

    /**
     * @brief Hämtar värdet av inställningen.
     *
     * Denna metod returnerar värdet för inställningen, t.ex. "Arial" eller "Dark".
     *
     * @return Värdet av inställningen.
     */
    QString getValue() const { return value; }

private:
    QString type;  /**< Typen av inställningen. */
    QString value; /**< Värdet av inställningen. */
};

/**
 * @class SettingsModel
 * @brief Modellklass för hantering av inställningar.
 *
 * Denna klass är ansvarig för att lagra och hantera en samling av inställningar.
 * Den innehåller metoder för att lägga till inställningar, hämta inställningar och
 * återställa inställningarna. Den fungerar som en mellanhand mellan datalagring och
 * användargränssnittet.
 *
 * @inherits Model
 */
class SettingsModel : public Model
{
public:
    /**
     * @brief Standardkonstruktor för `SettingsModel`.
     *
     * Skapar en instans av `SettingsModel`. Initierar eventuell intern data om
     * nödvändigt.
     */
    SettingsModel() {}

    /**
     * @brief Destruktor för `SettingsModel`.
     *
     * Zerar alla resurser som allokerats för `SettingsModel` vid objektets livscykel.
     */
    virtual ~SettingsModel() {}

    /**
     * @brief Lägger till en inställning i containern.
     *
     * Denna metod lägger till en inställning i den interna containern (t.ex. en lista).
     *
     * @param setting Inställningen som ska läggas till.
     */
    void addSettingToContainer(const Setting &setting);

    /**
     * @brief Lägger till en inställning i databasen.
     *
     * Denna metod lägger till en inställning i en databas eller annan permanent lagring.
     *
     * @param setting Inställningen som ska sparas.
     */
    void addSettingToDatabase(const Setting &setting);

    /**
     * @brief Hämtar inställningens värde baserat på dess typ.
     *
     * Denna metod söker efter en inställning med en specifik typ och returnerar dess värde.
     *
     * @param type Typen av inställningen som ska hämtas.
     * @return Värdet för inställningen som matchar den angivna typen.
     */
    QString getSettingByType(const QString &type) const;

    /**
     * @brief Återställer inställningarna.
     *
     * Denna metod återställer inställningarna genom att tömma containern som lagrar dem.
     * Den används för att återställa inställningar till ett standardläge.
     */
    virtual void reset() override { settingsContainer.clear(); }

private:
    QVector<Setting> settingsContainer; /**< Container för att lagra inställningarna. */
};


#endif // SETTINGSMODEL_H
