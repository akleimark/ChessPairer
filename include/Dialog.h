#ifndef DIALOG_H
#define DIALOG_H

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include "ChessplayerModel.h"
#include "TournamentModel.h"
#include "wx/combobox.h"

/**
    Det h?r ?r en abstrakt basklass, som ?rver wxDialog. Med hj?lp av den h?r
    klassen blir det enkelt att skapa underklasser f?r att skapa enhetliga dialogrutor.
*/
class Dialog : public wxDialog
{
    public:
        Dialog(const wxString &title);
        virtual ~Dialog() {}

    protected:
        /// Den h?r klasskonstanten anger hur m?nga pixlar det ?r mellan objekten i dialogrutan.
        const static unsigned int SPACE;
        /// Den h?r klassvariabeln lagrar den f?rvalda bredden p? dialogrutan.
        const static unsigned int DEFAULT_WIDTH;
        /// Den h?r klassvariabeln lagrar den f?rvalda h?jden p? dialogrutan.
        const static unsigned int DEFAULT_HEIGHT;
        void preCreate();
        virtual void postCreate();
        /// Det ?r i den h?r funktionen som alla klass-specifika objekt l?ggs till.
        /// Den implementeras av alla klasser som ?rver 'Dialog'.
        virtual void create() {}
        /// I den h?r funktionen, som m?ste implementeras av alla klasser som ?rver 'Dialog', l?ggs alla
        /// h?ndelser till.
        virtual void addBinds() = 0;
        /// Den h?r klasskonstanten anv?nds p? alla objekt av typen 'label'.
        const static wxFont LABEL_FONT;
        /// Alla instanser av klassen anv?nder en 'wxBoxSizer' f?r att l?gga ut objekten i layouten.
        wxBoxSizer *verticalBox;
        /// Den h?r klasskonstanten anger hur stor marginalen fr?n v?nsterkanten ?r.
        const static unsigned int LEFT_MARGIN;
        const static wxSize BIG_SIZE;

    private:
};

/**
    Den h?r klassen ?rver klassen 'Dialog'. Tanken med klassen ?r att skapa en dialogruta,
    f?r att ge anv?ndaren m?jlighet att l?gga till en schackspelare till databasen.
*/
class AddChessplayerDialog : public Dialog
{
    public:
        AddChessplayerDialog(const wxString &title);
        virtual ~AddChessplayerDialog() {}

    protected:
        virtual void create();
        virtual void addBinds();
    private:

        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa knapparna med texten 'Add', 'Reset' och 'Close'.
        wxBoxSizer *buttonBox;
        /// Den h?r knappen ger anv?ndaren m?jlighet att l?gga till en schackspelare till databasen.
        wxButton *addButton;
        /// Den h?r knappen ger anv?ndaren m?jlighet att ?terst?lla formul?ret.
        wxButton *resetButton;
        /// Den h?r knappen ger anv?ndaren m?jlighet att st?nga dialogrutan.
        wxButton *closeButton;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens id.
        wxBoxSizer *idBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Id: '.
        wxStaticText *idLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens id.
        wxTextCtrl *idField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens f?rnamn.
        wxBoxSizer *firstnameBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Firstname: '.
        wxStaticText *firstnameLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens f?rnamn.
        wxTextCtrl *firstnameField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens f?rnamn.
        wxBoxSizer *lastnameBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Lastname: '.
        wxStaticText *lastnameLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens efternamn.
        wxTextCtrl *lastnameField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett radioknappar f?r att ?ndra den t?nkta spelarens biologiska k?n.
        wxBoxSizer *biologicalSexBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Biological sex: '
        wxStaticText *biologicalSexLabel;
        /// Det h?r ?r en radioknapp f?r att ?ndra spelarens biologiska k?n till "man".
        wxRadioButton *maleButton;
        /// Det h?r ?r en radioknapp f?r att ?ndra spelarens biologiska k?n till "kvinna".
        wxRadioButton *femaleButton;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens f?delsedata.
        wxBoxSizer *birthdateBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Birthdate: '.
        wxStaticText *birthdateLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens f?delsedata.
        wxTextCtrl *birthdateField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens landstillh?righet.
        wxBoxSizer *federationBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Federation: '.
        wxStaticText *federationLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens landstillh?righet.
        wxTextCtrl *federationField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens klubbtillh?righet.
        wxBoxSizer *clubBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Club: '.
        wxStaticText *clubLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens klubbtillh?righet.
        wxTextCtrl *clubField;
        /// Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren har fyllt i alla data om schackspelaren och har klickat p? 'Add'.
        void addChessplayer(wxCommandEvent &event);
        /// Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren har klickat p? 'Reset'.
        void resetForm(wxCommandEvent &event);
        /// Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren har klickat p? 'Close'.
        void closeDialog(wxCommandEvent &event);
        /// Den h?r instansen av klassen 'Chessplayer' anv?nds f?r att spara data och l?gga till schackspelaren till databasen.
        ChessplayerModel chessplayer;
};

/**
    Den h?r klassen ?rver klassen 'Dialog'. Tanken med klassen ?r att skapa en dialogruta,
    f?r att ge anv?ndaren m?jlighet att l?gga till en turnering till databasen.
*/

class AddTournamentDialog : public Dialog
{
    public:
        AddTournamentDialog(const wxString &title);
        virtual ~AddTournamentDialog() {}

    protected:
        virtual void create();
        virtual void addBinds();
    private:

        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa knapparna med texten 'L?gg till', '?terst?ll' och 'St?ng'.
        wxBoxSizer *buttonBox;
        /// Den h?r knappen ger anv?ndaren m?jlighet att l?gga till en turnering till databasen.
        wxButton *addButton;
        /// Den h?r knappen ger anv?ndaren m?jlighet att ?terst?lla formul?ret.
        wxButton *resetButton;
        /// Den h?r knappen ger anv?ndaren m?jlighet att st?nga dialogrutan.
        wxButton *closeButton;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra turneringens id.
        wxBoxSizer *idBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten 'Id: '.
        wxStaticText *idLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in den t?nkta spelarens id.
        wxTextCtrl *idField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra den t?nkta spelarens id.
        wxBoxSizer *startDateBox;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in turneringens id.
        wxStaticText *startDateLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in turneringens startdatum.
        wxTextCtrl *startDateField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra turneringens startdatum.
        wxBoxSizer *endDateBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten "Slutdatum:".
        wxStaticText *endDateLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in turneringens slutdatum.
        wxTextCtrl *endDateField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och ett textf?lt f?r att ?ndra antalet ronder i turneringen.
        wxBoxSizer *numberOfRoundsBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten "Antal ronder:".
        wxStaticText *numberOfRoundsLabel;
        /// Den h?r instansen av 'wxTextCtrl' ger anv?ndaren m?jlighet att skriva in antalet ronder, som skall g?lla i turneringen.
        wxTextCtrl *numberOfRoundsField;
        /// Den h?r instansen av 'wxBoxSizer' anv?nds f?r att visa en etikett och en 'wxComboBox' med lottningssystemen.
        wxBoxSizer *pairingSystemBox;
        /// Den h?r instansen av 'wxStaticText' visar en etikett med texten "Lottningssystem:".
        wxStaticText *pairingSystemLabel;
        /// Den h?r instansen av 'wxComboBox' visar en comboBox med m?jliga lottningssystem.
        wxComboBox *pairingSystemComboBox;
        /// Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren har fyllt i alla data om turneringen och har klickat p? 'Add'.
        void addTournament(wxCommandEvent &event);
        /// Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren har klickat p? 'Reset'.
        void resetForm(wxCommandEvent &event);
        /// Den h?r h?ndelsestyrda funktionen k?rs, n?r anv?ndaren har klickat p? 'Close'.
        void closeDialog(wxCommandEvent &event);
        /// Den h?r instansen av klassen 'TournamentModel' anv?nds f?r att spara data och l?gga till schackspelaren till databasen.
        TournamentModel tournamentModel;
};

#endif // DIALOG_H
