#ifndef IMPORTCHESSPLAYERSMODEL_H
#define IMPORTCHESSPLAYERSMODEL_H

#include "ModelViewController.h"
#include "Interfaces.h"

class ImportChessplayersModel : public Model, public Strategy
{
    public:
        ImportChessplayersModel(): file("") {}
        virtual ~ImportChessplayersModel() {}
        void setFile(const std::string &newFile);
        virtual void doStrategy() = 0;

    protected:
        std::string file;

    private:

};

class ImportChessplayersXML : public ImportChessplayersModel
{
    public:
        ImportChessplayersXML() {}
        virtual ~ImportChessplayersXML() {}
        virtual void doStrategy();

    protected:


    private:
};



#endif // IMPORTCHESSPLAYERSMODEL_H
