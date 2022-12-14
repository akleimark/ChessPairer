#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <vector>
#include "ModelViewController.h"
#include "Database.h"
#include "Exception.h"
#include "ChessplayerModel.h"
#include "TournamentModel.h"
#include <iostream>

/**
    Den h?r klassen anv?nds f?r att kunna anv?nda listor av klasser.
*/

template <class T>
class ListModel : public Model
{
    public:
        /**
            I konstruktorn s?tts storleken och vektorn till noll element.
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
            Den h?r funktionen h?mtar alla modeller som finns i databasen av en viss typ. Om
            en instans av klassen har skapats med T = ChessplayerModel h?mtas exempelvis alla schackspelare ur databasen.
        */
        void getAll();
        /**
            Den h?r funktionen h?mtar objektet p? plats index i vektorn (typen T).
            Om T = ChessplayerModel och det finns 10 schackspelare i databasen, h?mtas schackspelare 3, om man
            k?r kodsnutten ListModel<ChessplayerModel> model; model.getAll(); model.get(2);.
        */
        T get(const unsigned int &index) const { return data[index]; }

        /**
            Den h?r funktionen returnerar storleken p? vektorn 'data', d?r alla objekt ?r lagrade.
        */
        unsigned int getSize() const { return data.size(); }
        /// Den h?r operator?verlagringen returnerar en referens till objekt 'index' i containern 'data'.
        const T& operator[](const unsigned int &index) const { return data[index]; }
        /// Den h?r funktionen returnerar objekt T i containern 'data'.
        T atIndex(const unsigned int &index) {return data[index]; }

    protected:
        /**
            I den h?r vektorn l?ggs alla data som h?mtas fr?n databasen in.
        */
        std::vector<T> data;
        /**
            Meningen med den h?r funktionen ?r att den data som h?mtats ur databasen l?ggs in i vektorn 'data'.
        */
        void addToContainer();

    private:
};

#endif // LISTMODEL_H
