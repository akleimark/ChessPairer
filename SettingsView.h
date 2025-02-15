#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "MVC.h"
#include "SettingsModel.h"
#include <QFontComboBox>

/**
 * @class SettingsView
 * @brief Visningsklass för inställningar.
 *
 * Denna klass är ansvarig för att presentera inställningarna i användargränssnittet.
 * Den interagerar med `SettingsModel` för att hämta och visa data samt uppdaterar
 * vyn när användaren ändrar inställningar.
 *
 * @inherits View
 */
class SettingsView : public View
{
public:
    /**
     * @brief Konstruktor för `SettingsView`.
     *
     * Skapar en instans av `SettingsView` och kopplar modellen som innehåller
     * inställningsdatan.
     *
     * @param model Pekare till en `SettingsModel`-instans som representerar
     *              inställningsdatan.
     */
    SettingsView(SettingsModel *model);

    /**
     * @brief Uppdaterar vyn baserat på de senaste inställningarna.
     *
     * Denna metod uppdaterar användargränssnittet med de senaste värdena från
     * inställningsmodellen, t.ex. ändring av font eller andra användarinställningar.
     */
    virtual void updateView() const override;

    /**
     * @brief Lägger till lyssnare för användarinteraktioner.
     *
     * Denna metod registrerar lyssnare för händelser som kan påverka vyn,
     * t.ex. när användaren ändrar inställningar genom GUI-komponenter.
     */
    virtual void addListeners() override;

private:
    QVBoxLayout *layout;           /**< Layout som används för att arrangera GUI-komponenter. */
    QFontComboBox *fontComboBox;   /**< Kombinationsruta för att välja font. */

    /**
     * @brief Skapar användargränssnittet.
     *
     * Denna metod ansvarar för att skapa och arrangera alla grafiska komponenter
     * i användargränssnittet, t.ex. fontkombinationsrutan och andra widgets.
     */
    void createUI();

    SettingsModel *model; /**< Pekare till `SettingsModel` som lagrar och hanterar inställningarna. */
};


#endif // SETTINGSVIEW_H
