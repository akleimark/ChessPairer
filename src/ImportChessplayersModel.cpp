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
    file = newFile;
}

