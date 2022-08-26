#include "ImportChessplayersModel.h"
#include "Misc.h"
#include "Exception.h"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include <iostream>
#include "ChessplayerModel.h"
#include <set>


void ImportChessplayersModel::setFile(const std::string &newFile)
{
    if(misc::fileExists(newFile) == false)
    {
        throw IOErrorException("The file does not exist.");
    }

    file = newFile;
}

void ImportChessplayersXML::doStrategy()
{
    std::set<ChessplayerModel> chessplayerList;
    unsigned int lineNumber = 0;
    boost::filesystem::ifstream fileHandler(file);
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
