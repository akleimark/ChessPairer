#ifndef LISTMODEL_H
#define LISTMODEL_H

#include "Interfaces.h"
#include "MVC.h"

/**
 * @class ListModel
 * @brief En generisk modellklass för att hantera en lista av objekt.
 *
 * ListModel fungerar som en basmodell för hantering av en samling objekt av typen T.
 * Den innehåller grundläggande funktioner för att manipulera listan samt interagera
 * med en databas. Klasser som ärver ListModel måste implementera databasfunktionerna.
 *
 * @tparam T Datatypen för objekten som ska hanteras i listan.
 */
template <typename T>
class ListModel : public Model, public ResetInterface
{
public:
    /**
     * @brief Konstruktor för ListModel.
     *
     * Initierar modellen med en instans av SettingsModel.
     *
     * @param settingsModel Pekare till SettingsModel-instansen som hanterar användarinställningar.
     */
    ListModel(SettingsModel *settingsModel) : settingsModel(settingsModel) {}

    /**
     * @brief Virtuell destruktor för polymorfism.
     */
    virtual ~ListModel() override = default;

    /**
     * @brief Lägger till ett objekt i den interna behållaren.
     *
     * @param data Objektet som ska läggas till i listan.
     */
    virtual void addToContainer(const T &data) { container.push_back(data); }

    /**
     * @brief Lägger till ett objekt i databasen.
     *
     * Ren virtuell metod som måste implementeras i subklasser för att definiera
     * hur objekt ska lagras i databasen.
     *
     * @param data Objektet som ska läggas till i databasen.
     */
    virtual unsigned int addToDatabase(const T &data) = 0;

    /**
     * @brief Uppdaterar ett objekt i databasen.
     *
     * Ren virtuell metod som måste implementeras i subklasser för att definiera
     * hur objekt ska uppdateras i databasen.
     *
     * @param data Objektet som ska uppdateras.
     */
    virtual void updateDatabase(const T &data) = 0;

    /**
     * @brief Hämtar ett objekt vid ett givet index.
     *
     * Hämtar objektet vid det angivna indexet som en konstant referens.
     *
     * @param index Index för objektet som ska hämtas.
     * @return En konstant referens till objektet.
     * @throws std::runtime_error Om indexet är utanför giltigt intervall.
     */
    const T& at(const unsigned int &index) const;

    /**
     * @brief Hämtar ett objekt vid ett givet index.
     *
     * Hämtar objektet vid det angivna indexet som en referens.
     *
     * @param index Index för objektet som ska hämtas.
     * @return En referens till objektet.
     * @throws std::runtime_error Om indexet är utanför giltigt intervall.
     */
    T& at(const unsigned int &index);

    /**
     * @brief Hämtar antalet objekt i listan.
     *
     * @return Antalet objekt i listan.
     */
    unsigned int size() const { return container.size(); }

    /**
     * @brief Återställer modellen genom att rensa den interna behållaren.
     *
     * Rensar alla objekt från listan.
     */
    virtual void reset() override { container.clear(); }

    /**
     * @brief Hämtar instansen av SettingsModel.
     *
     * @return Pekare till SettingsModel-instansen.
     */
    SettingsModel* getSettingsModel() const { return settingsModel; }

    /**
     * @brief Hämtar en konstant iterator till början av listan.
     *
     * @return En konstant iterator som pekar på det första elementet.
     */
    typename std::vector<T>::const_iterator cbegin() const { return container.cbegin(); }

    /**
     * @brief Hämtar en konstant iterator till slutet av listan.
     *
     * @return En konstant iterator som pekar på slutet av listan.
     */
    typename std::vector<T>::const_iterator cend() const { return container.cend(); }

    /**
 * @brief Tar bort en turnering från modellen och databasen baserat på turnerings-ID.
 *
 * Denna metod är virtuell och måste implementeras i en konkret klass som hanterar
 * turneringsdata. Den ansvarar för att ta bort turneringen från både den interna
 * datamodellen (vektor) samt från databasen.
 *
 * @param index ID för den turnering som ska tas bort.
 *
 * @note Denna metod måste implementeras i en härledd klass som t.ex.
 * TournamentListModel, där den exekverar SQL-frågan för att ta bort turneringen från
 * databasen samt hanterar uppdatering av den interna vektorn.
 *
 * @see TournamentListModel::removeById
 */
    virtual void removeById(const unsigned int &index) = 0;

protected:
    SettingsModel *settingsModel; ///< Pekare till instansen av SettingsModel.
    std::vector<T> container; ///< Intern behållare för objekt.
};

template <typename T>
const T& ListModel<T>::at(const unsigned int &index) const
{
    if(index >= container.size())
    {
        throw std::runtime_error("Index out of bounds");
    }
    return container[index];
}

template <typename T>
T& ListModel<T>::at(const unsigned int &index)
{
    if(index >= container.size())
    {
        throw std::runtime_error("Index out of bounds");
    }

    return container[index];
}

#endif // LISTMODEL_H
