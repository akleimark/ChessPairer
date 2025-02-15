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
    Q_OBJECT
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

signals:
    /**
     * @brief Signal som skickas när en cell ändras.
     *
     * @param row Raden som ändrades.
     * @param column Kolumnen som ändrades.
     * @param newValue Det nya värdet i cellen.
     */
    void cellChanged(int row, int column, const QString &newValue);

private slots:
    /**
     * @brief Slot som hanterar celländringar i tabellen.
     *
     * @param row Raden som ändrades.
     * @param column Kolumnen som ändrades.
     */
    void onCellChanged(int row, int column);
};

#endif // PLAYERLISTVIEW_H
