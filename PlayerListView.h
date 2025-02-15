#ifndef PLAYERLISTVIEW_H
#define PLAYERLISTVIEW_H

#include "MVC.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "PlayerListModel.h"

/**
 * @class PlayerListView
 * @brief Representerar GUI-komponenten som visar listan av spelare.
 *
 * PlayerListView hanterar visningen av spelarlistan och tillhörande interaktioner.
 */
class PlayerListView : public View
{
public:
    /**
     * @brief Skapar en PlayerListView-instans.
     *
     * @param model Pekare till spelarmodellen.
     */
    PlayerListView(PlayerListModel *model);

    /**
     * @brief Uppdaterar vyn med data från modellen.
     *
     * Anropas när modellen notifierar att data har förändrats.
     */
    virtual void updateView() const override;

    /**
     * @brief Lägger till eventlyssnare för användarinteraktion.
     */
    virtual void addListeners() override;

protected:
    /**
     * @brief Hanterar fönsterstorleksändringar.
     *
     * Justerar tabellens kolumnbredder dynamiskt.
     * @param event Fönsterstorlekshändelsen.
     */
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief Skapar och konfigurerar UI-komponenterna.
     */
    void createUI();

    QTableWidget *tableWidget; ///< Tabell som visar spelarna.
    QWidget *buttonWidget; ///< Widget som innehåller knappar.
    QPushButton *addPlayerButton; ///< Knapp för att lägga till en spelare.
};

#endif // PLAYERLISTVIEW_H
