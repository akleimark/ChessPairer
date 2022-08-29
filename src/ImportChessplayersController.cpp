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
#include <wx/msgdlg.h>



ImportChessplayersController::ImportChessplayersController(Model *_model, View *_view):
    Controller(_model, _view)
{
     ImportChessplayersModel *iModel = (ImportChessplayersModel*) model;
     strategy = new ReadXMLFile(iModel);
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
    iModel->setFile(event.GetString().ToStdString());
}

void ImportChessplayersController::startImport(wxCommandEvent &event)
{
    ImportChessplayersModel *iModel = (ImportChessplayersModel*) model;
    std::cout << iModel->getFile() << std::endl;

    try
    {
        strategy->execute();
    }
    catch(Exception &exception)
    {
        wxMessageBox(exception.what(),
                 "Error", wxOK | wxICON_INFORMATION);
    }

}

void ReadFileStrategy::abortProcess()
{
    delete model;
    model = nullptr;
    throw IOErrorException("The file is corrupt. We abort the import process.");
}


void ReadXMLFile::execute()
{
    ImportChessplayersModel *iModel = (ImportChessplayersModel*) model;
    if(!misc::fileExists(iModel->getFile().c_str()))
    {
        throw IOErrorException("The selected file does not exist.");
    }

    ChessplayerModel *chessplayerModel = nullptr;
    std::set<ChessplayerModel> chessplayerList;
    unsigned int lineNumber = 0;
    boost::filesystem::ifstream fileHandler(model->getFile());
    std::string line;
    while (getline(fileHandler, line))
    {
        ++lineNumber;

        if(lineNumber == 1 && line.substr(0, 5) != "<?xml")
        {
            throw IOErrorException("The selected file is not an xml-file.");
        }
        else if(lineNumber > 1 && line == "<chessplayer>")
        {
            if(chessplayerModel == nullptr)
            {
                chessplayerModel = new ChessplayerModel;
            }
            else
            {
                abortProcess();
            }
        }
        else if(lineNumber > 1 && line == "</chessplayer>")
        {
            chessplayerModel->print();
            if(chessplayerModel->validate() == false)
            {
                abortProcess();
            }
            else
            {
                chessplayerList.insert(*chessplayerModel);
            }
        }
        else if(lineNumber > 1 && line.find("<id>") != std::string::npos && line.find("</id>") != std::string::npos)
        {
            int forwardIndex = strlen("<id>") + line.find("<id>");
            int endIndex = line.find("</id>");
            unsigned int id = std::stoi(line.substr(forwardIndex, endIndex - forwardIndex));
            chessplayerModel->setID(id);
        }
        else if(lineNumber > 1 && line.find("<firstname>") != std::string::npos && line.find("</firstname>") != std::string::npos)
        {
            int forwardIndex = strlen("<firstname>") + line.find("<firstname>");
            int endIndex = line.find("</firstname>");
            chessplayerModel->setFirstname(line.substr(forwardIndex, endIndex - forwardIndex));
        }

        else if(lineNumber > 1 && line.find("<lastname>") != std::string::npos && line.find("</lastname>") != std::string::npos)
        {
            int forwardIndex = strlen("<lastname>") + line.find("<lastname>");
            int endIndex = line.find("</lastname>");
            chessplayerModel->setLastname(line.substr(forwardIndex, endIndex - forwardIndex));
        }
        else if(lineNumber > 1 && line.find("<biological_sex>") != std::string::npos && line.find("</biological_sex>") != std::string::npos)
        {
            int forwardIndex = strlen("<biological_sex>") + line.find("<biological_sex>");
            int endIndex = line.find("</biological_sex>");
            chessplayerModel->setBiologicalSex(line.substr(forwardIndex, endIndex - forwardIndex));
        }
        else if(lineNumber > 1 && line.find("<birthdate>") != std::string::npos && line.find("</birthdate>") != std::string::npos)
        {
            int forwardIndex = strlen("<birthdate>") + line.find("<birthdate>");
            int endIndex = line.find("</birthdate>");
            chessplayerModel->setBirthDate(line.substr(forwardIndex, endIndex - forwardIndex));
        }
        else if(lineNumber > 1 && line.find("<federation>") != std::string::npos && line.find("</federation>") != std::string::npos)
        {
            int forwardIndex = strlen("<federation>") + line.find("<federation>");
            int endIndex = line.find("</federation>");
            chessplayerModel->setFederation(line.substr(forwardIndex, endIndex - forwardIndex));
        }
        else if(lineNumber > 1 && line.find("<chessclub>") != std::string::npos && line.find("</chessclub>") != std::string::npos)
        {
            int forwardIndex = strlen("<chessclub>") + line.find("<chessclub>");
            int endIndex = line.find("</chessclub>");
            chessplayerModel->setChessclub(line.substr(forwardIndex, endIndex - forwardIndex));
        }
    }

    for(ChessplayerModel aModel : chessplayerList)
    {
        aModel.print();
    }

}

