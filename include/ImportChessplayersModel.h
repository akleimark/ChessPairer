#ifndef IMPORTCHESSPLAYERSMODEL_H
#define IMPORTCHESSPLAYERSMODEL_H

#include "ModelViewController.h"
#include "Interfaces.h"

class ImportChessplayersModel : public Model
{
    public:
        ImportChessplayersModel(): file("") {}
        virtual ~ImportChessplayersModel() {}
        void setFile(const std::string &newFile);
        std::string getFile() const {return file; }

    protected:
        std::string file;

    private:

};




#endif // IMPORTCHESSPLAYERSMODEL_H
