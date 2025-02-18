#ifndef TOURNAMENTLISTCONTROLLER_H
#define TOURNAMENTLISTCONTROLLER_H

#include "MVC.h"
#include "TournamentListModel.h"
#include "TournamentListView.h"

/**
 * @class TournamentListController
 * @brief Hanterar interaktionen mellan modellen och vyn för turneringslistan.
 *
 * Denna klass är en kontroller som ansvarar för att hantera användarens interaktioner
 * med turneringslistan. Den reagerar på användarens input, uppdaterar modellen och
 * uppdaterar vyn baserat på dessa förändringar.
 *
 * @see TournamentListModel
 * @see TournamentListView
 */
class TournamentListController : public Controller
{
public:

    /**
     * @brief Konstruktör för TournamentListController.
     *
     * Skapar en instans av TournamentListController med referenser till modellen och vyn.
     *
     * @param model Pekare till en instans av TournamentListModel som används för att hantera turneringsdata.
     * @param view Pekare till en instans av TournamentListView som används för att visa turneringslistan.
     */
    TournamentListController(TournamentListModel *model, TournamentListView *view);

public slots:

    /**
     * @brief Hanterar klick på "Lägg till turnering"-knappen.
     *
     * När användaren klickar på knappen för att lägga till en ny turnering, anropas denna metod.
     * Denna metod ska skapa en ny turnering och lägga till den i modellen.
     */
    void onAddTournamentClicked();

    /**
     * @brief Hanterar förändringar i en cell i turneringslistan.
     *
     * När användaren ändrar ett värde i en cell (t.ex. en turnerings namn), anropas denna metod.
     * Den uppdaterar motsvarande data i modellen.
     *
     * @param row Radnummer där ändringen skedde.
     * @param column Kolumnnummer där ändringen skedde.
     * @param newValue Det nya värdet som användaren har angett.
     */
    void onCellChanged(int row, int column, const QString &newValue);

    /**
     * @brief Hanterar begäran om att ta bort en turnering.
     *
     * När användaren begär att ta bort en turnering, anropas denna metod.
     * Den bekräftar borttagningen och om användaren bekräftar, tas turneringen bort från modellen och databasen.
     *
     * @param id ID för den turnering som ska tas bort.
     */
    void onRemoveTournamentRequested(const unsigned int &id);

private:
    TournamentListModel *tournamentListModel; /**< Pekare till modellen som hanterar turneringsdata. */
    TournamentListView *tournamentListView; /**< Pekare till vyn som visar turneringslistan. */
};

#endif // TOURNAMENTLISTCONTROLLER_H
