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
 * PlayerListView hanterar visningen av spelarlistan och tillhörande interaktioner, inklusive att visa
 * spelare i en tabell och tillhandahålla knappar för att lägga till eller ta bort spelare.
 */
class PlayerListView : public View
{
    Q_OBJECT
public:
    /**
     * @brief Skapar en PlayerListView-instans.
     *
     * Skapar en instans av PlayerListView och kopplar den till en spelarmodell.
     * Denna konstruktor initierar alla UI-komponenter och sätter upp grundläggande funktionalitet.
     *
     * @param model Pekare till spelarmodellen som denna vy kommer att interagera med.
     */
    explicit PlayerListView(PlayerListModel *model);

    /**
     * @brief Uppdaterar vyn med data från modellen.
     *
     * Denna metod anropas när modellen notifierar att data har förändrats och uppdaterar
     * spelarlistan som visas i tabellen.
     */
    virtual void updateView() const override;

    /**
     * @brief Lägger till eventlyssnare för användarinteraktion.
     *
     * Denna metod ansluter nödvändiga slots till händelser som användarinteraktioner med vyn,
     * som att klicka på knappar eller ändra celler i tabellen.
     */
    virtual void addListeners() override;

protected:


private:
    /**
     * @brief Skapar och konfigurerar UI-komponenterna.
     *
     * Denna metod skapar alla nödvändiga UI-komponenter för vyn, inklusive tabellen och knapparna,
     * samt konfigurerar deras egenskaper och layout.
     */
    void createUI();

    QTableWidget *tableWidget; ///< Tabell som visar spelarna.
    QWidget *buttonWidget; ///< Widget som innehåller knappar för interaktion.
    QPushButton *addPlayerButton; ///< Knapp för att lägga till en spelare.
    QPushButton *removePlayerButton; ///< Knapp för att ta bort en spelare.
    const PlayerListModel *playerListModel; ///< Pekare till spelarmodellen.

signals:
    /**
     * @brief Signal som skickas när en cell ändras.
     *
     * Denna signal sänds när en cell i tabellen ändras av användaren.
     *
     * @param row Raden som ändrades.
     * @param column Kolumnen som ändrades.
     * @param newValue Det nya värdet i cellen.
     */
    void cellChanged(int row, int column, const QString &newValue);

    /**
     * @brief Signal som begär att en spelare tas bort.
     *
     * Denna signal skickas när användaren begär att en spelare ska tas bort från listan.
     *
     * @param fideId Spelarens FIDE-ID som ska tas bort.
     */
    void removePlayerRequested(const unsigned int &fideId);

private slots:
    /**
     * @brief Slot som hanterar celländringar i tabellen.
     *
     * Denna metod anropas när en cell ändras i tabellen av användaren.
     * Ändringarna skickas vidare till modellen via en signal.
     *
     * @param row Raden som ändrades.
     * @param column Kolumnen som ändrades.
     */
    void onCellChanged(int row, int column);

    /**
     * @brief Slot som hanterar val av spelare i tabellen.
     *
     * Denna metod anropas när användaren väljer eller avmarkerar en spelare i tabellen.
     */
    void onSelectionChanged();

    /**
     * @brief Slot som hanterar borttagning av en spelare från listan.
     *
     * Denna metod anropas när användaren klickar på knappen för att ta bort en spelare.
     * Den skickar en signal om att en spelare ska tas bort baserat på FIDE-ID.
     */
    void onRemovePlayerClicked();
};


#endif // PLAYERLISTVIEW_H
