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
#include "ManageTiebreaksController.h"
#include "ManageTiebreaksView.h"
#include "TiebreakModel.h"

class ChessPairerFrame;

/**
    Den h?r klassen utg?r sj?lva hj?rtat i applikationen. Klassen ?rver wxApp.
*/
class ChessPairerApp : public wxApp
{
    public:
        virtual bool OnInit();

    private:
        /// Den h?r pekarvariabeln h?ller en instans till klassen 'ChessPairerFrame', som utg?r huvudf?nstret.
        ChessPairerFrame *frame;
};

/**
    Den h?r klassen visar ett f?nster och fungerar som huvudf?nster f?r applikationen. N?r det
    h?r f?nstret st?ngs, avslutas applikationen.
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
        void OnManageTournamentTiebreaks(wxCommandEvent &event);
        void createMenuSystem();
        void addEvents();
        void destroy();
        void showView(const wxString &name);
        void hideAllViews();

        // Views
        /// Den h?r pekarvariabeln h?ller en instans till klassen 'ListChesplayers', som anv?nds f?r att visa en vy med alla tillagda schackspelare.
        std::map<wxString, View*> views;

        // Models
        /// Den h?r pekarvariabeln h?ller en instans av 'ChessplayerList', som ?r en modell, som hanterar data om schackspelarna.
        ListModel<ChessplayerModel*> *chessplayerListModel;
        ImportChessplayersModel *importChessplayersModel;
        ListModel<TournamentModel*> *tournamentListModel;
        TournamentModel *tournamentModel;
        TournamentPlayerModel *tournamentPlayerModel;
        ManageTournamentPlayersViewModel *manageTournamentPlayersViewModel;
        ListModel<TiebreakModel*> *tiebreaksListModel;
        TiebreakModel *tiebreakModels[2];
        ManageTiebreaksViewModel *manageTiebreaksViewModel;

        // Controllers
        ListChessplayersController *listChessplayersController;
        ImportChessplayersController *importChessplayersController;
        ListTournamentsController *listTournamentsController;
        ManageTournamentPlayersController *manageTournamentPlayersController;
        ManageTiebreaksController *manageTiebreaksController;

        // MVC
        void createModels();
        void createViews();
        void createControllers();
        void initMVC();
};

wxIMPLEMENT_APP(ChessPairerApp);

#endif // CHESSPAIRERAPP_H
