#ifndef IMPORTCHESSPLAYERSCONTROLLER_H
#define IMPORTCHESSPLAYERSCONTROLLER_H

#include "ModelViewController.h"
#include "Interfaces.h"
#include "ImportChessplayersModel.h"

class ReadFileStrategy;
class ImportChessplayersController : public Controller
{
    public:
        ImportChessplayersController(Model *_model, View *_view);
        virtual ~ImportChessplayersController();
        void setFileType(wxCommandEvent &event);
        void setFile(wxCommandEvent &event);
        void startImport(wxCommandEvent &event);

    protected:

    private:
        ReadFileStrategy *strategy;
};

class ReadFileStrategy : public Strategy
{
    public:
        ReadFileStrategy(ImportChessplayersModel *_model):
            model(_model) {}
        virtual ~ReadFileStrategy() {}
        virtual void execute() = 0;

    protected:
        ImportChessplayersModel *model;

};

class ReadXMLFile : public ReadFileStrategy
{
    public:
        ReadXMLFile(ImportChessplayersModel *_model):
                    ReadFileStrategy(_model) {}
        virtual ~ReadXMLFile() {}
        virtual void execute();
};


#endif // IMPORTCHESSPLAYERSCONTROLLER_H
