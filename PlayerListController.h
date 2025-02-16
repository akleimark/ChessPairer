#ifndef PLAYERLISTCONTROLLER_H
#define PLAYERLISTCONTROLLER_H

#include "MVC.h"
#include "PlayerListModel.h"
#include "PlayerListView.h"

/**
 * @class PlayerListController
 * @brief Hanterar interaktionen mellan PlayerListModel och PlayerListView.
 *
 * PlayerListController tar emot användaråtgärder från vyn och uppdaterar modellen vid behov.
 * Den ansvarar för att synkronisera användarens input med datamodellen och se till att vyn
 * återspeglar förändringarna i modellen.
 */
class PlayerListController : public Controller
{
public:
    /**
     * @brief Skapar en PlayerListController-instans.
     *
     * Konstruktorn tar emot pekare till både modellen och vyn som denna controller kommer att hantera.
     *
     * @param model Pekare till PlayerListModel som hanterar spelarlistan.
     * @param view Pekare till PlayerListView som visar spelarlistan.
     */
    PlayerListController(PlayerListModel *model, PlayerListView *view);

public slots:
    /**
     * @brief Slot som hanterar klick på "Lägg till spelare"-knappen.
     *
     * När användaren klickar på knappen, öppnas en dialogruta där användaren kan ange en ny spelares
     * information, som sedan läggs till i modellen.
     */
    void onAddPlayerClicked();

    /**
     * @brief Hanterar ändringar i tabellen och uppdaterar modellen.
     *
     * När en cell i tabellen ändras, uppdateras den motsvarande spelaren i modellen.
     *
     * @param row Raden i tabellen som ändrades.
     * @param column Kolumnen i tabellen som ändrades.
     * @param newValue Det nya värdet som användaren angav.
     */
    void onCellChanged(int row, int column, const QString &newValue);

    /**
     * @brief Begär att en spelare tas bort från listan.
     *
     * När användaren begär att ta bort en spelare, tas spelaren bort från både modellen och
     * vyn, och ändringarna uppdateras i databasen.
     *
     * @param fideId Det unika FIDE-ID:t för spelaren som ska tas bort.
     */
    void onRemovePlayerRequested(const unsigned int &fideId);

private:
    PlayerListModel *playerListModel;    ///< Pekare till modellen som hanterar spelarlistan.
    PlayerListView *playerListView;      ///< Pekare till vyn som visar spelarlistan.
};


#endif // PLAYERLISTCONTROLLER_H
