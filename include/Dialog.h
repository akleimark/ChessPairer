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
    Det här är en abstrakt basklass, som ärver wxDialog. Med hjälp av den här
    klassen blir det enkelt att skapa underklasser för att skapa enhetliga dialogrutor.
*/
class Dialog : public wxDialog
{
    public:
        Dialog(const wxString &title);

    protected:
        /// Den här klasskonstanten anger hur många pixlar det är mellan objekten i dialogrutan.
        const static unsigned int SPACE;
        /// Den här klassvariabeln lagrar den förvalda bredden på dialogrutan.
        const static unsigned int DEFAULT_WIDTH;
        /// Den här klassvariabeln lagrar den förvalda höjden på dialogrutan.
        const static unsigned int DEFAULT_HEIGHT;
        void preCreate();
        virtual void postCreate();
        virtual void create() {}
        virtual void addBinds() = 0;
        /// Den här klasskonstanten används på alla objekt av typen 'label'.
        const static wxFont LABEL_FONT;
        /// Alla instanser av klassen använder en 'wxBoxSizer' för att lägga ut objekten i layouten.
        wxBoxSizer *verticalBox;
        /// Den här klasskonstanten anger hur stor marginalen från vänsterkanten är.
        const static unsigned int LEFT_MARGIN;

    private:

};

class AddChessplayerDialog : public Dialog
{
    public:
        AddChessplayerDialog(const wxString &title);
        virtual ~AddChessplayerDialog();

    protected:
        virtual void create();
        virtual void addBinds();
    private:

        /// Den här instansen av 'wxBoxSizer' används för att visa knapparna med texten 'Add', 'Reset' och 'Close'.
        wxBoxSizer *buttonBox;
        /// Den här knappen ger användaren möjlighet att lägga till en schackspelare till databasen.
        wxButton *addButton;
        /// Den här knappen ger användaren möjlighet att återställa formuläret.
        wxButton *resetButton;
        /// Den här knappen ger användaren möjlighet att stänga dialogrutan.
        wxButton *closeButton;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens id.
        wxBoxSizer *idBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Id: '.
        wxStaticText *idLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens id.
        wxTextCtrl *idField;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens förnamn.
        wxBoxSizer *firstnameBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Firstname: '.
        wxStaticText *firstnameLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens förnamn.
        wxTextCtrl *firstnameField;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens förnamn.
        wxBoxSizer *lastnameBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Lastname: '.
        wxStaticText *lastnameLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens efternamn.
        wxTextCtrl *lastnameField;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett radioknappar för att ändra den tänkta spelarens biologiska kön.
        wxBoxSizer *biologicalSexBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Biological sex: '
        wxStaticText *biologicalSexLabel;
        /// Det här är en radioknapp för att ändra spelarens biologiska kön till "man".
        wxRadioButton *maleButton;
        /// Det här är en radioknapp för att ändra spelarens biologiska kön till "kvinna".
        wxRadioButton *femaleButton;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens födelsedata.
        wxBoxSizer *birthdateBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Birthdate: '.
        wxStaticText *birthdateLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens födelsedata.
        wxTextCtrl *birthdateField;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens landstillhörighet.
        wxBoxSizer *federationBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Federation: '.
        wxStaticText *federationLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens landstillhörighet.
        wxTextCtrl *federationField;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens klubbtillhörighet.
        wxBoxSizer *clubBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Club: '.
        wxStaticText *clubLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens klubbtillhörighet.
        wxTextCtrl *clubField;
        /// Den här händelsestyrda funktionen körs, när användaren har fyllt i alla data om schackspelaren och har klickat på 'Add'.
        void addChessplayer(wxCommandEvent &event);
        /// Den här händelsestyrda funktionen körs, när användaren har klickat på 'Reset'.
        void resetForm(wxCommandEvent &event);
        /// Den här händelsestyrda funktionen körs, när användaren har klickat på 'Close'.
        void closeDialog(wxCommandEvent &event);
        /// Den här instansen av klassen 'Chessplayer' används för att spara data och lägga till schackspelaren till databasen.
        ChessplayerModel chessplayer;
};


class AddTournamentDialog : public Dialog
{
    public:
        AddTournamentDialog(const wxString &title);
        virtual ~AddTournamentDialog();

    protected:
        virtual void create();
        virtual void addBinds();
    private:

        /// Den här instansen av 'wxBoxSizer' används för att visa knapparna med texten 'Add', 'Reset' och 'Close'.
        wxBoxSizer *buttonBox;
        /// Den här knappen ger användaren möjlighet att lägga till en turnering till databasen.
        wxButton *addButton;
        /// Den här knappen ger användaren möjlighet att återställa formuläret.
        wxButton *resetButton;
        /// Den här knappen ger användaren möjlighet att stänga dialogrutan.
        wxButton *closeButton;
        /// Den här instansen av 'wxBoxSizer' används för att visa en etikett och ett textfält för att ändra den tänkta spelarens id.
        wxBoxSizer *idBox;
        /// Den här instansen av 'wxStaticText' visar en etikett med texten 'Id: '.
        wxStaticText *idLabel;
        /// Den här instansen av 'wxTextCtrl' ger användaren möjlighet att skriva in den tänkta spelarens id.
        wxTextCtrl *idField;

        wxBoxSizer *startDateBox;
        wxStaticText *startDateLabel;
        wxTextCtrl *startDateField;

        wxBoxSizer *endDateBox;
        wxStaticText *endDateLabel;
        wxTextCtrl *endDateField;

        wxBoxSizer *numberOfRoundsBox;
        wxStaticText *numberOfRoundsLabel;
        wxTextCtrl *numberOfRoundsField;
        wxBoxSizer *pairingSystemBox;
        wxStaticText *pairingSystemLabel;
        wxComboBox *pairingSystemComboBox;

        /// Den här händelsestyrda funktionen körs, när användaren har fyllt i alla data om turneringen och har klickat på 'Add'.
        void addTournament(wxCommandEvent &event);
        /// Den här händelsestyrda funktionen körs, när användaren har klickat på 'Reset'.
        void resetForm(wxCommandEvent &event);
        /// Den här händelsestyrda funktionen körs, när användaren har klickat på 'Close'.
        void closeDialog(wxCommandEvent &event);
        /// Den här instansen av klassen 'TournamentModel' används för att spara data och lägga till schackspelaren till databasen.
        TournamentModel tournamentModel;
};


#endif // DIALOG_H
