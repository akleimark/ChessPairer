#ifndef LISTMODEL_H
#define LISTMODEL_H

#include "Interfaces.h"
#include "MVC.h"
#include <vector>
#include "Logger.h"

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
    ListModel(SettingsModel *settingsModel) : settingsModel(settingsModel) {}

    virtual ~ListModel() override
    {
        for (T* item : container)
        {
            delete item;
        }
        container.clear();
    }

    virtual void addToContainer(T *data) { container.push_back(data); }

    virtual unsigned int addToDatabase(const T *data) = 0;

    virtual void updateDatabase(const T *data) = 0;

    T* at(const unsigned int &index) const;

    unsigned int size() const { return container.size(); }

    virtual void reset() override
    {
        for (T* item : container)
        {
            delete item;
        }
        container.clear();
    }

    SettingsModel* getSettingsModel() const { return settingsModel; }

    typename std::vector<T*>::const_iterator cbegin() const { return container.cbegin(); }

    typename std::vector<T*>::const_iterator cend() const { return container.cend(); }

    virtual void removeById(const unsigned int &index) = 0;

protected:
    SettingsModel *settingsModel;
    std::vector<T*> container;
};

template <typename T>
T* ListModel<T>::at(const unsigned int &index) const
{
    if(index >= container.size())
    {
        Logger::getInstance()->logError("Index out of bounds");
    }
    return container[index];
}

#endif // LISTMODEL_H
