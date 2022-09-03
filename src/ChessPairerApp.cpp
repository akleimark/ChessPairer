#include "ChessPairerApp.h"
#include "Defs.h"
#include <iostream>
#include "ChessplayerModel.h"
#include "ListChessplayersView.h"
#include "Misc.h"
#include "Exception.h"
#include "ListTournamentsView.h"
#include "ManageTournamentPlayersView.h"

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
    SetStatusText(L"V\u00E4lkommen till " + APPLICATION_NAME + " .");

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
    menuFile->Append(wxID_EXIT, QUIT_MESSAGE);

    wxMenu *menuDatabase = new wxMenu;
    menuDatabase->Append(ID_LIST_TOURNAMENTS, "&Visa alla turneringar...");
    menuDatabase->Append(ID_LIST_CHESSPLAYERS, "&Visa alla schackspelare...");
    menuDatabase->Append(ID_IMPORT_CHESSPLAYERS, "&Importera schackspelare...");
    menuDatabase->Append(ID_RESET_DATABASE, L"\u00C5terst\u00E4ll databasen...");

    wxMenu *menuTournaments = new wxMenu;
    menuTournaments->Append(ID_LIST_TOURNAMENT_PLAYERS, "&Hantera spelare...");
    menuTournaments->Append(ID_LIST_TOURNAMENT_TIEBREAKS, L"&St\u00E4ll in särskiljning...");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, ABOUT_MESSAGE);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&Arkiv");
    menuBar->Append(menuDatabase, "&Databas");
    menuBar->Append(menuTournaments, "&Turneringar");
    menuBar->Append(menuHelp, L"Hj\u00E4lp");

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
    Bind(wxEVT_MENU, &ChessPairerFrame::OnManageTournamentPlayers, this, ID_LIST_TOURNAMENT_PLAYERS);
    Bind(wxEVT_MENU, &ChessPairerFrame::OnManageTournamentTiebreaks, this, ID_LIST_TOURNAMENT_TIEBREAKS);
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
    chessplayerListModel = new ListModel<ChessplayerModel*>;
    importChessplayersModel = new ImportChessplayersModel;
    tournamentListModel = new ListModel<TournamentModel*>;
    tournamentModel = nullptr;
    tournamentPlayerModel = nullptr;
    tiebreaksListModel = new ListModel<TiebreakModel*>;
    manageTournamentPlayersViewModel = new ManageTournamentPlayersViewModel(tournamentListModel, chessplayerListModel, tournamentModel, tournamentPlayerModel);
    manageTiebreaksViewModel = new ManageTiebreaksViewModel(tournamentListModel, tiebreaksListModel, tournamentModel);
}

/**
    Den här funktionen har ansvar för att skapa alla de vyer som applikationen använder sig av.
*/
void ChessPairerFrame::createViews()
{
    views["LIST_TOURNAMENTS"] = new ListTournamentsView(this);
    views["LIST_CHESSPLAYERS"] = new ListChessplayersView(this);
    views["IMPORT_CHESSPLAYERS"] = new ImportChessplayersView(this);
    views["MANAGE_TOURNAMENT_PLAYERS"] = new ManageTournamentPlayersView(this);
    views["MANAGE_TOURNAMENT_TIEBREAKS"] = new ManageTiebreaksView(this);
}

void ChessPairerFrame::createControllers()
{
    listTournamentsController = new ListTournamentsController(tournamentListModel, views["LIST_TOURNAMENTS"]);
    listChessplayersController = new ListChessplayersController(chessplayerListModel, views["LIST_CHESSPLAYERS"]);
    importChessplayersController = new ImportChessplayersController(importChessplayersModel, views["IMPORT_CHESSPLAYERS"]);
    manageTournamentPlayersController = new ManageTournamentPlayersController(manageTournamentPlayersViewModel, views["MANAGE_TOURNAMENT_PLAYERS"]);
    manageTiebreaksController = new ManageTiebreaksController(manageTiebreaksViewModel, views["MANAGE_TOURNAMENT_TIEBREAKS"]);
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
    manageTournamentPlayersViewModel->addView(views["MANAGE_TOURNAMENT_PLAYERS"]);
    views["MANAGE_TOURNAMENT_PLAYERS"]->setController(manageTournamentPlayersController);
    manageTiebreaksViewModel->addView(views["MANAGE_TOURNAMENT_TIEBREAKS"]);
    views["MANAGE_TOURNAMENT_TIEBREAKS"]->setController(manageTiebreaksController);

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
    message << APPLICATION_NAME <<L" \u00E4r ett program f\u00F6r att lotta schackturneringar." << "\n\n" << L"Utvecklare: "
    << DEVELOPER_NAME << "\n" << "E-post: " << DEVELOPER_EMAIL << "\n";

    wxMessageBox(message, ABOUT_MESSAGE, wxOK | wxICON_INFORMATION);
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
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
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
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        exit(-1);
    }

    showView("LIST_CHESSPLAYERS");
}

void ChessPairerFrame::OnResetDatabase(wxCommandEvent& event)
{
    wxString message;
    message << CONFIRM_MESSAGE << L"\u00E5terst\u00E4lla databasen?";
    int result = wxMessageBox(message, CONFIRM_LABEL, wxOK | wxCANCEL);
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
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
            return;
        }

        wxMessageBox(SUCCESS_MESSAGE, SUCCESS_MESSAGE, wxOK | wxICON_INFORMATION);
    }
}

void ChessPairerFrame::OnImportChessplayers(wxCommandEvent &event)
{
    showView("IMPORT_CHESSPLAYERS");
}

void ChessPairerFrame::OnManageTournamentPlayers(wxCommandEvent &event)
{
    tournamentListModel->getAll();
    chessplayerListModel->getAll();
    manageTournamentPlayersViewModel->notifyAllViews();

    showView("MANAGE_TOURNAMENT_PLAYERS");
}

void ChessPairerFrame::OnManageTournamentTiebreaks(wxCommandEvent &event)
{
    showView("MANAGE_TOURNAMENT_TIEBREAKS");
}
