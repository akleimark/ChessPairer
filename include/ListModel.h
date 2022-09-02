#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <vector>
#include "ModelViewController.h"
#include "Database.h"
#include "Exception.h"
#include "ChessplayerModel.h"
#include "TournamentModel.h"
#include <iostream>

template <class T>
class ListModel : public Model
{
    public:
        /**
            I konstruktorn sätts storleken å vektorn till noll element.
        */
        ListModel<T>()
        {
            data.resize(0);
        }
        /**
            I destruktorn tas alla data bort och vektorn rensas.
        */
        virtual ~ListModel<T>()
        {
            for(T item : data)
            {
                if(item != nullptr)
                {
                    delete item;
                    item = nullptr;
                }

            }

            data.clear();
            data.resize(0);
        }
        /**
            Den här funktionen hämtar alla modeller som finns i databasen av en viss typ. Om
            en instans av klassen har skapats med T = ChessplayerModel hämtas exempelvis alla schackspelare ur databasen.
        */
        void getAll();
        /**
            Den här funktionen hämtar objektet på plats index i vektorn (typen T).
            Om T = ChessplayerModel och det finns 10 schackspelare i databasen, hämtas schackspelare 3, om man
            kör kodsnutten ListModel<ChessplayerModel> model; model.getAll(); model.get(2);.
        */
        T get(const unsigned int &index) const { return data[index]; }

        /**
            Den här funktionen returnerar storleken på vektorn 'data', där alla objekt är lagrade.
        */
        unsigned int getSize() const { return data.size(); }
        const T& operator[](const unsigned int &index) const { return data[index]; }
        T atIndex(const unsigned int &index) {return data[index]; }

    protected:
        /**
            I den här vektorn läggs alla data som hämtas från databasen in.
        */
        std::vector<T> data;
        /**
            Meningen med den här funktionen är att den data som hämtats ur databasen läggs in i vektorn 'data'.
        */
        void addToContainer();

    private:
};


#endif // LISTMODEL_H
