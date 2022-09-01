#ifndef CHESSPAIRERAPP_H
#define CHESSPAIRERAPP_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "ChessplayerModel.h"
#include "ListChessplayersView.h"
#include "Database.h"
#include "ListChessplayersController.h"
#include "ImportChessplayersView.h"
#include "ImportChessplayersController.h"
#include "ImportChessplayersModel.h"
#include "TournamentModel.h"
#include "ListTournamentsController.h"
#include "ListModel.h"
#include "ViewModel.h"
#include "ManageTournamentPlayersController.h"

class ChessPairerFrame;

/**
    Den här klassen utgör själva hjärtat i applikationen. Klassen ärver wxApp.
*/
class ChessPairerApp : public wxApp
{
    public:
        virtual bool OnInit();

    private:
        /// Den här pekarvariabeln håller en instans till klassen 'ChessPairerFrame', som utgör huvudfönstret.
        ChessPairerFrame *frame;
};

/**
    Den här klassen visar ett fönster och fungerar som huvudfönster för applikationen. När det
    här fönstret stängs, avslutas applikationen.
*/
class ChessPairerFrame : public wxFrame
{
    public:
        ChessPairerFrame(const unsigned int &width = 500, const unsigned int &height = 500);

    private:

        void OnListTournaments(wxCommandEvent& event);
        void OnListChessplayers(wxCommandEvent& event);
        void OnResetDatabase(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnImportChessplayers(wxCommandEvent &event);
        void OnManageTournamentPlayers(wxCommandEvent &event);
        void createMenuSystem();
        void addEvents();
        void destroy();
        void showView(const wxString &name);
        void hideAllViews();

        // Views
        /// Den här pekarvariabeln håller en instans till klassen 'ListChesplayers', som används för att visa en vy med alla tillagda schackspelare.
        std::map<wxString, View*> views;

        // Models
        /// Den här pekarvariabeln håller en instans av 'ChessplayerList', som är en modell, som hanterar data om schackspelarna.
        ListModel<ChessplayerModel> *chessplayerListModel;
        ImportChessplayersModel *importChessplayersModel;
        ListModel<TournamentModel> *tournamentListModel;
        ManageTournamentPlayersViewModel *manageTournamentPlayersViewModel;

        // Controllers
        ListChessplayersController *listChessplayersController;
        ImportChessplayersController *importChessplayersController;
        ListTournamentsController *listTournamentsController;
        ManageTournamentPlayersController *manageTournamentPlayersController;

        // MVC

        void createModels();
        void createViews();
        void createControllers();
        void initMVC();

};


wxIMPLEMENT_APP(ChessPairerApp);

#endif // CHESSPAIRERAPP_H
