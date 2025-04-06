#ifndef TOURNAMENTLISTVIEW_H
#define TOURNAMENTLISTVIEW_H

#include "MVC.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "TournamentListModel.h"

class TournamentListController;

/**
 * @class TournamentListView
 * @brief Visar och hanterar användargränssnittet för turneringslistan.
 *
 * Denna klass är ansvarig för att visa turneringslistan och tillhandahålla interaktiva
 * element för användaren, som knappar och tabeller. Den är också ansvarig för att skicka
 * signaler till kontrolleraren när användaren interagerar med gränssnittet.
 *
 * @see TournamentListModel
 * @see TournamentListController
 */
class TournamentListView : public View
{
    Q_OBJECT
public:

    /**
     * @brief Konstruktor för TournamentListView.
     *
     * Skapar en instans av TournamentListView och kopplar den till en modell för turneringslistan.
     *
     * @param model Pekare till en instans av TournamentListModel som innehåller data om turneringar.
     */
    explicit TournamentListView(TournamentListModel &model);

    /**
     * @brief Uppdaterar vyn med aktuell data från modellen.
     *
     * Denna metod används för att uppdatera gränssnittet när datan i modellen har förändrats.
     *
     * @override
     */
    virtual void updateView() override;

    /**
     * @brief Lägger till lyssnare för användarinteraktioner.
     *
     * Denna metod lägger till alla lyssnare (listeners) som behövs för att hantera användarens input,
     * såsom knapplister och celländringar i tabellen.
     *
     * @override
     */
    virtual void addListeners() override;

private:

    /**
     * @brief Skapar användargränssnittet för turneringslistvyn.
     *
     * Denna metod skapar och arrangerar alla användargränssnittselement, såsom knappar och tabeller.
     */
    void createUI();

    QTableWidget *tableWidget; /**< Tabellwidget som visar listan av turneringar. */
    QWidget *buttonWidget; /**< Widget som håller knappar för att lägga till och ta bort turneringar. */
    QPushButton *addTournamentButton; /**< Knappar för att lägga till en turnering. */
    QPushButton *removeTournamentButton; /**< Knappar för att ta bort en turnering. */
    QPushButton *selectTournamentButton;
    TournamentListModel &tournamentListModel; /**< Pekare till modellen som håller turneringsdata. */
    TournamentListController *tournamentListController;

signals:
    /**
     * @brief Signal som skickas när en cell i tabellen ändras.
     *
     * När en cell ändras skickas denna signal till kontrolleraren för att hantera uppdateringen.
     *
     * @param row Radnummer för den cell som ändrades.
     * @param column Kolumnnummer för den cell som ändrades.
     * @param newValue Det nya värdet i cellen.
     */
    void cellChanged(int row, int column, const QString &newValue);

    /**
     * @brief Signal som skickas när en turnering ska tas bort.
     *
     * När användaren begär att ta bort en turnering skickas denna signal till kontrolleraren för att
     * begära borttagning av turneringen.
     *
     * @param tournamentId ID för den turnering som ska tas bort.
     */
    void removeTournamentRequested(const unsigned int &tournamentId);

    void selectTournamentRequested(const unsigned int &tournamentId);

private slots:

    /**
     * @brief Slot som hanterar förändringar i celler i tabellen.
     *
     * När användaren ändrar en cell i tabellen anropas denna metod för att skicka signalen
     * om ändring av cellen.
     *
     * @param row Radnummer för den cell som ändrades.
     * @param column Kolumnnummer för den cell som ändrades.
     */
    void onCellChanged(int row, int column);

    /**
     * @brief Slot som hanterar ändringar i tabellens val.
     *
     * När användaren ändrar sitt val av rad i tabellen anropas denna metod.
     */
    void onSelectionChanged();

    /**
     * @brief Slot som hanterar klick på knappen för att ta bort en turnering.
     *
     * När användaren klickar på knappen för att ta bort en turnering anropas denna metod för att
     * skicka signalen om att en turnering ska tas bort.
     */
    void onRemoveTournamentClicked();

    void onSelectTournamentClicked();
};


#endif // TOURNAMENTLISTVIEW_H
