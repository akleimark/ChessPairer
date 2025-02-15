#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include "MVC.h"
#include "SettingsModel.h"
#include "SettingsView.h"

/**
 * @class SettingsController
 * @brief Hanterar logiken för inställningar i applikationen.
 *
 * Denna klass är ansvarig för att interagera med både `SettingsModel` och
 * `SettingsView` för att uppdatera och hantera användarens inställningar.
 * Den fungerar som en mellanhand mellan modellen och vyn genom att tillhandahålla
 * slots för att reagera på användarens interaktioner, såsom att ändra font.
 *
 * @inherits Controller
 */
class SettingsController : public Controller
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor för `SettingsController`.
     *
     * Skapar en instans av `SettingsController` och kopplar samman modellen och
     * vyn som ska användas för att hantera inställningarna.
     *
     * @param model Pekare till en `SettingsModel`-instans som representerar
     *              inställningsdata.
     * @param view Pekare till en `SettingsView`-instans som ansvarar för att visa
     *             inställningarna.
     */
    SettingsController(SettingsModel *model, SettingsView *view);

private:
    SettingsModel *settingsModel; /**< Pekare till inställningsmodellen. */
    SettingsView *settingsView;   /**< Pekare till inställningsvyn. */

public slots:
    /**
     * @brief Hanterar förändringar av fonten.
     *
     * Denna slot anropas när användaren ändrar fonten i inställningarna.
     * Den uppdaterar inställningsmodellen och vyn för att spegla den nya fonten.
     *
     * @param font Den nya fonten som användaren valt.
     */
    void onFontChanged(const QFont &font);
};


#endif // SETTINGSCONTROLLER_H
