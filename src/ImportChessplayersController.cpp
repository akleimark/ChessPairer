#include "ImportChessplayersController.h"
#include <iostream>
#include "ImportChessplayersModel.h"
#include "ChessplayerModel.h"
#include "Misc.h"
#include "Exception.h"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include <iostream>
#include <set>


ImportChessplayersController::ImportChessplayersController(Model *_model, View *_view):
    Controller(_model, _view), strategy(nullptr)
{

}

ImportChessplayersController::~ImportChessplayersController()
{

}


void ImportChessplayersController::setFileType(wxCommandEvent &event)
{
    ImportChessplayersModel *iModel = (ImportChessplayersModel*) model;

    if(strategy != nullptr)
    {
        delete strategy;
        strategy = nullptr;
    }

    // XML
    if(event.GetId() == 0)
    {
        strategy = new ReadXMLFile(iModel);
    }
    // Textfil
    else if(event.GetId() == 1)
    {

    }
}

void ImportChessplayersController::setFile(wxCommandEvent &event)
{
    ImportChessplayersModel *iModel = (ImportChessplayersModel*) model;
    try
    {
        iModel->setFile(event.GetString().ToStdString());
    }
    catch(IOErrorException &exception)
    {
        //std::cout << exception.what() << std::endl;
    }
}

void ImportChessplayersController::startImport(wxCommandEvent &event)
{
    ImportChessplayersModel *iModel = (ImportChessplayersModel*) model;
    std::cout << iModel->getFile() << std::endl;

    //strategy->execute();
}



void ReadXMLFile::execute()
{
    std::set<ChessplayerModel> chessplayerList;
    unsigned int lineNumber = 0;
    boost::filesystem::ifstream fileHandler(model->getFile());
    std::string line;
    while (getline(fileHandler, line))
    {
        ++lineNumber;

        if(lineNumber == 1)
        {
            if(line.substr(0, 5) != "<?xml")
            {
                throw IOErrorException("The selected file is not an xml-file.");
            }
        }

        wxString wxLine = line;
    }
}

