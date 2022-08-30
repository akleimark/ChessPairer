#include "ChessPairerApp.h"
#include "Defs.h"
#include "AddTournamentForm.h"
#include <iostream>
#include "ChessplayerModel.h"
#include "ListChessplayersView.h"
#include "Misc.h"
#include "Exception.h"
#include "ListTournamentsView.h"

/**
    Den här funktionen motsvarar funktionen 'main' i konsolapplikationer.
*/
bool ChessPairerApp::OnInit()
{
    frame = new ChessPairerFrame();
    frame->Show(true);

    Database *database = Database::getInstance();
    try
    {
        database->open();
    }
    catch(DatabaseErrorException &exception)
    {
        std::cerr << exception.what() << std::endl;
        exit(-1);
    }

    return true;
}

ChessPairerFrame::ChessPairerFrame(const unsigned int &width, const unsigned int &height)
    : wxFrame(NULL, wxID_ANY, APPLICATION_NAME)
{
    createMenuSystem();
    CreateStatusBar();
    SetStatusText("Welcome to " + APPLICATION_NAME + " .");

    addEvents();
    createModels();
    createViews();
    initMVC();
}
/**
    Den här funktionen skapar menysystemet.
*/
void ChessPairerFrame::createMenuSystem()
{
    wxMenu *menuFile = new wxMenu;

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuDatabase = new wxMenu;
    menuDatabase->Append(ID_LIST_TOURNAMENTS, "&List all tournaments...");
    menuDatabase->Append(ID_LIST_CHESSPLAYERS, "&List all chessplayers...");
    menuDatabase->Append(ID_RESET_DATABASE, "&Reset database...");
    menuDatabase->Append(ID_IMPORT_CHESSPLAYERS, "&Import chessplayers...");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuDatabase, "&Database");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
}

/**
    Den här funktionen körs, när programmet avslutas.
*/
void ChessPairerFrame::destroy()
{
    if(chessplayerListModel != nullptr)
    {
        delete chessplayerListModel;
        chessplayerListModel = nullptr;
    }
}


/**
    Den här funktionen lägger till alla 'events'.
*/
void ChessPairerFrame::addEvents()
{
    Bind(wxEVT_MENU, &ChessPairerFrame::OnListTournaments, this, ID_LIST_TOURNAMENTS);
    Bind(wxEVT_MENU, &ChessPairerFrame::OnListChessplayers, this, ID_LIST_CHESSPLAYERS);
    Bind(wxEVT_MENU, &ChessPairerFrame::OnResetDatabase, this, ID_RESET_DATABASE);
    Bind(wxEVT_MENU, &ChessPairerFrame::OnImportChessplayers, this, ID_IMPORT_CHESSPLAYERS);
    Bind(wxEVT_MENU, &ChessPairerFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &ChessPairerFrame::OnExit, this, wxID_EXIT);
}

/**
    Den här funktionen gömmer alla vyer. Detta görs, när alla vyerna har skapats.
*/
void ChessPairerFrame::hideAllViews()
{
    for (auto iter = views.begin(); iter != views.end(); ++iter)
    {
        iter->second->Show(false);
    }
}

/**
    Den här funktionen körs, när en viss vy skall visas.
*/
void ChessPairerFrame::showView(const wxString &name)
{
    for (auto iter = views.begin(); iter != views.end(); ++iter)
    {
        if(iter->first == name)
        {
            iter->second->Show(true);
            iter->second->SetSizeHints(this);
            this->SetSizerAndFit(iter->second, false);
        }
        else
        {
            iter->second->Show(false);
        }
    }

    this->SetMinClientSize(wxSize(DEFAULT_FRAME_WIDTH, DEFAULT_FRAME_HEIGHT));
}


/**
    I den här funktionen skapas alla de modeller som behövs för att applikationen skall fungera.
*/
void ChessPairerFrame::createModels()
{
    chessplayerListModel = new ListModel<ChessplayerModel>;
    importChessplayersModel = new ImportChessplayersModel;
    tournamentListModel = new ListModel<TournamentModel>;
}

/**
    Den här funktionen har ansvar för att skapa alla de vyer som applikationen använder sig av.
*/
void ChessPairerFrame::createViews()
{
    views["LIST_TOURNAMENTS"] = new ListTournamentsView(this);
    views["LIST_CHESSPLAYERS"] = new ListChessplayersView(this);
    views["IMPORT_CHESSPLAYERS"] = new ImportChessplayersView(this);

}

void ChessPairerFrame::createControllers()
{
    listTournamentsController = new ListTournamentsController(tournamentListModel, views["LIST_TOURNAMENTS"]);
    listChessplayersController = new ListChessplayersController(chessplayerListModel, views["LIST_CHESSPLAYERS"]);
    importChessplayersController = new ImportChessplayersController(importChessplayersModel, views["IMPORT_CHESSPLAYERS"]);
}


/**
    Den här funktionen initierar 'Model-View'Controller'.
*/
void ChessPairerFrame::initMVC()
{
    createControllers();
    tournamentListModel->addView(views["LIST_TOURNAMENTS"]);
    views["LIST_TOURNAMENTS"]->setController(listTournamentsController);
    chessplayerListModel->addView(views["LIST_CHESSPLAYERS"]);
    views["LIST_CHESSPLAYERS"]->setController(listChessplayersController);
    importChessplayersModel->addView(views["IMPORT_CHESSPLAYERS"]);
    views["IMPORT_CHESSPLAYERS"]->setController(importChessplayersController);
    hideAllViews();
}

/**
    Den här händelsestyrda funktionen köra när användaren har valt alternativet 'Quit'.
*/
void ChessPairerFrame::OnExit(wxCommandEvent& event)
{
    Close(true);

    try
    {
        Database::getInstance()->close();
    }
    catch(DatabaseErrorException &exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    destroy();
    this->Destroy();
}

/**
    Den här händelsestyrda funktionen köra när användaren har valt alternativet 'About'.
*/
void ChessPairerFrame::OnAbout(wxCommandEvent& event)
{
    wxString message;
    message << "ChessPairer is an application for pairing chess tournaments." << "\n\n" << "Author: Anders Kleimark\n"
        << "Contact: " << "akleimark@gmail.com\n";

    wxMessageBox(message, "About", wxOK | wxICON_INFORMATION);
}



void ChessPairerFrame::OnListTournaments(wxCommandEvent& event)
{
    try
    {
        tournamentListModel->getAll();
        tournamentListModel->notifyAllViews();
    }
    catch(Exception &exception)
    {
        wxMessageBox(exception.what(),
                 "Error", wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    showView("LIST_TOURNAMENTS");
}


/**
    Den här händelsestyrda funktionen köra när användaren har valt alternativet 'List all chessplayers'.
*/
void ChessPairerFrame::OnListChessplayers(wxCommandEvent& event)
{
    try
    {
        chessplayerListModel->getAll();
        chessplayerListModel->notifyAllViews();
    }
    catch(Exception &exception)
    {
        wxMessageBox(exception.what(),
                 "Error", wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    showView("LIST_CHESSPLAYERS");
}

void ChessPairerFrame::OnResetDatabase(wxCommandEvent& event)
{
    int result = wxMessageBox("Are you sure you want to reset the database?",
                 "Confirm", wxOK | wxCANCEL);
    if(result == wxOK)
    {
        Database *database = Database::getInstance();
        try
        {
            database->resetDatabase();
        }
        catch(DatabaseErrorException &exception)
        {
            wxMessageBox(exception.what(),
                 "Error", wxOK | wxICON_INFORMATION);
            return;
        }

        wxMessageBox("Success",
                 "Success", wxOK | wxICON_INFORMATION);
    }
}

void ChessPairerFrame::OnImportChessplayers(wxCommandEvent &event)
{
    showView("IMPORT_CHESSPLAYERS");
}
