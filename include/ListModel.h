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
            I konstruktorn s�tts storleken � vektorn till noll element.
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
            data.clear();
            data.resize(0);
        }
        /**
            Den h�r funktionen h�mtar alla modeller som finns i databasen av en viss typ. Om
            en instans av klassen har skapats med T = ChessplayerModel h�mtas exempelvis alla schackspelare ur databasen.
        */
        void getAll();
        /**
            Den h�r funktionen h�mtar objektet p� plats index i vektorn (typen T).
            Om T = ChessplayerModel och det finns 10 schackspelare i databasen, h�mtas schackspelare 3, om man
            k�r kodsnutten ListModel<ChessplayerModel> model; model.getAll(); model.get(2);.
        */
        T get(const unsigned int &index) const { return data[index]; }
        /**
            Den h�r funktionen returnerar storleken p� vektorn 'data', d�r alla objekt �r lagrade.
        */
        unsigned int getSize() const { return data.size(); }

    protected:
        /**
            I den h�r vektorn l�ggs alla data som h�mtas fr�n databasen in.
        */
        std::vector<T> data;
        /**
            Meningen med den h�r funktionen �r att den data som h�mtats ur databasen l�ggs in i vektorn 'data'.
        */
        void addToContainer();

    private:
};

template <class T>
void ListModel<T>::getAll()
{
    wxString tableName = "";
    wxString className = typeid(T).name();

    if(className.find("ChessplayerModel") != std::string::npos)
    {
        tableName = "chessplayers";
    }
    else if(className.find("TournamentModel") != std::string::npos)
    {
        tableName = "tournaments";
    }

    Database *database = Database::getInstance();
    wxString sql = "select * from ";
    sql << tableName <<  " order by id";

    try
    {
        database->executeSql(sql);
    }
    catch(DatabaseErrorException &)
    {
        throw;
    }

     addToContainer();
}



#endif // LISTMODEL_H