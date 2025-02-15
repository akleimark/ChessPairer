#ifndef PLAYERLISTCONTROLLER_H
#define PLAYERLISTCONTROLLER_H

#include "MVC.h"
#include "PlayerListModel.h"
#include "PlayerListView.h"

/**
 * @class PlayerListController
 * @brief Hanterar interaktionen mellan PlayerModel och PlayerListView.
 *
 * PlayerListController tar emot användaråtgärder från vyn och uppdaterar modellen vid behov.
 */
class PlayerListController : public Controller
{
public:
    /**
     * @brief Skapar en PlayerListController-instans.
     *
     * @param model Pekare till spelarmodellen.
     * @param view Pekare till spelarlistans vy.
     */
    PlayerListController(PlayerListModel *model, PlayerListView *view);

public slots:
    /**
     * @brief Slot som hanterar klick på "Lägg till spelare"-knappen.
     *
     * När knappen klickas öppnas en dialogruta där användaren kan ange en ny spelares information.
     */
    void onAddPlayerClicked();
    /**
     * @brief Hanterar ändringar i tabellen och uppdaterar modellen.
     *
     * @param row Raden som ändrades.
     * @param column Kolumnen som ändrades.
     * @param newValue Det nya värdet.
     */
    void onCellChanged(int row, int column, const QString &newValue);

private:
    PlayerListModel *playerListModel;    ///< Pekare till modellen som hanterar spelarlistan.
    PlayerListView *playerView;  ///< Pekare till vyn som visar spelarlistan.
};

#endif // PLAYERLISTCONTROLLER_H
