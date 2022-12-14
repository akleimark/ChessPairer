#include "Dialog.h"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <iostream>
#include "ChessplayerModel.h"
#include <wx/msgdlg.h>
#include "Exception.h"
#include "Defs.h"

const unsigned int Dialog::LEFT_MARGIN = 5;
const unsigned int Dialog::SPACE = 20;
const unsigned int Dialog::DEFAULT_WIDTH = 700;
const unsigned int Dialog::DEFAULT_HEIGHT = 700;
const wxFont Dialog::LABEL_FONT = wxFont(11, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
const wxSize Dialog::BIG_SIZE = wxSize(200, 20);

/**
    I den h?r konstruktorn initieras klassens variabler. Superklassens konstruktor k?rs, samtidigt som
    'verticalBox' s?tts till 'nullptr'.
*/
Dialog::Dialog(const wxString &title):
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)), verticalBox(nullptr)
{

}

/**
    Den h?r funktionen k?rs innan funktionen 'create', som implementeras av alla klasser som
    ?rver 'Dialog'.
*/
void Dialog::preCreate()
{
    verticalBox = new wxBoxSizer(wxVERTICAL);
}

/**
    Den h?r funktionen k?rs efter 'create'. Den st?ller in den 'sizer' som anv?nds och k?r 'Centre'.
*/
void Dialog::postCreate()
{
    //verticalBox->SetSizeHints(this);
    SetSizer(verticalBox);
    Centre();
}

/**
    I den h?r konstruktorn k?rs de fyra funktionerna 'preCreate', 'create', 'postCreate' och 'addBinds'.
*/
AddChessplayerDialog::AddChessplayerDialog(const wxString &title):
    Dialog(title)
{
    preCreate();
    create();
    postCreate();
    addBinds();
}

/**
    I den h?r funktionen skapas alla objekt som ?r specifika f?r klassen 'AddChessplayerDialog'.
*/
void AddChessplayerDialog::create()
{
    idBox = new wxBoxSizer(wxHORIZONTAL);
    idLabel = new wxStaticText(this, -1, "Id: ");
    idField = new wxTextCtrl(this, -1);
    idLabel->SetFont(LABEL_FONT);
    idBox->Add(idLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    idBox->Add(idField, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(idBox, Dialog::LEFT_MARGIN, wxALL, 0);

    firstnameBox = new wxBoxSizer(wxHORIZONTAL);
    firstnameLabel = new wxStaticText(this, -1, L"F\u00F6rnamn: ");
    firstnameField = new wxTextCtrl(this, -1);
    firstnameLabel->SetFont(LABEL_FONT);
    firstnameBox->Add(firstnameLabel, 1, wxALL, AddChessplayerDialog::SPACE);
    firstnameBox->Add(firstnameField, 2, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(firstnameBox, Dialog::LEFT_MARGIN, wxALL, 0);

    lastnameBox = new wxBoxSizer(wxHORIZONTAL);
    lastnameLabel = new wxStaticText(this, -1, "Efternamn: ");
    lastnameField = new wxTextCtrl(this, -1);
    lastnameLabel->SetFont(LABEL_FONT);
    lastnameBox->Add(lastnameLabel, 1, wxALL, AddChessplayerDialog::SPACE);
    lastnameBox->Add(lastnameField, 2, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(lastnameBox, Dialog::LEFT_MARGIN, wxALL, 0);

    biologicalSexBox = new wxBoxSizer(wxHORIZONTAL);
    biologicalSexLabel = new wxStaticText(this, -1, L"Biologiskt k\u00F6n: ");
    maleButton = new wxRadioButton(this, -1, "Man");
    femaleButton = new wxRadioButton(this, -1, "Kvinna");
    biologicalSexLabel->SetFont(LABEL_FONT);
    biologicalSexBox->Add(biologicalSexLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    biologicalSexBox->Add(maleButton, 0, wxALL, AddChessplayerDialog::SPACE);
    biologicalSexBox->Add(femaleButton, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(biologicalSexBox, Dialog::LEFT_MARGIN, wxALL, 0);

    birthdateBox = new wxBoxSizer(wxHORIZONTAL);
    birthdateLabel = new wxStaticText(this, -1, L"F\u00F6delsedatum: ");
    birthdateField = new wxTextCtrl(this, -1);
    birthdateLabel->SetFont(LABEL_FONT);
    birthdateBox->Add(birthdateLabel, 9, wxALL, AddChessplayerDialog::SPACE);
    birthdateBox->Add(birthdateField, 8, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(birthdateBox, Dialog::LEFT_MARGIN, wxALL, 0);

    federationBox = new wxBoxSizer(wxHORIZONTAL);
    federationLabel = new wxStaticText(this, -1, "Nation: ");
    federationField = new wxTextCtrl(this, -1);
    federationLabel->SetFont(LABEL_FONT);
    federationBox->Add(federationLabel, 2, wxALL, AddChessplayerDialog::SPACE);
    federationBox->Add(federationField, 4, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(federationBox, Dialog::LEFT_MARGIN, wxALL, 0);

    clubBox = new wxBoxSizer(wxHORIZONTAL);
    clubLabel = new wxStaticText(this, -1, "Klubb: ");
    clubField = new wxTextCtrl(this, -1);
    clubLabel->SetFont(LABEL_FONT);
    clubBox->Add(clubLabel, 2, wxALL, AddChessplayerDialog::SPACE);
    clubBox->Add(clubField, 4, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(clubBox, Dialog::LEFT_MARGIN, wxALL, 0);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(this, -1, ADD_STRING);
    resetButton = new wxButton(this, -1, RESET_STRING);
    closeButton = new wxButton(this, -1, CLOSE_STRING);
    buttonBox->Add(addButton, 0, wxALL, Dialog::SPACE);
    buttonBox->Add(resetButton, 0, wxALL, Dialog::SPACE);
    buttonBox->Add(closeButton, 0, wxALL, Dialog::SPACE);
    verticalBox->Add(buttonBox, Dialog::LEFT_MARGIN, wxALL, 0);
}

void AddChessplayerDialog::addBinds()
{
    addButton->Bind(wxEVT_BUTTON, &AddChessplayerDialog::addChessplayer, this);
    resetButton->Bind(wxEVT_BUTTON, &AddChessplayerDialog::resetForm, this);
    closeButton->Bind(wxEVT_BUTTON, &AddChessplayerDialog::closeDialog, this);
}

/**
    Den h?r h?ndelsestyrda funktionen k?rs n?r anv?ndaren har tryckt p? "L?gg till", f?r att skapa den schackspelare,
    som han har lagt in data om. Funktionen kontrollerar, huruvida alla data ?r korrekt. Schackspelaren kommer
    endast att l?ggas in i databasen, om schackspelarens data ?r korrekt.
*/
void AddChessplayerDialog::addChessplayer(wxCommandEvent &event)
{
    chessplayer.setID(wxAtoi(idField->GetValue()));
    chessplayer.setFirstname(firstnameField->GetValue());
    chessplayer.setLastname(lastnameField->GetValue());
    if(maleButton->GetValue() == true)
    {
        chessplayer.setBiologicalSex("man");
    }
    else
    {
        chessplayer.setBiologicalSex("kvinna");
    }

    chessplayer.setBirthDate(birthdateField->GetValue());
    chessplayer.setFederation(federationField->GetValue());
    chessplayer.setChessclub(clubField->GetValue());
    if(chessplayer.validate())
    {
        try
        {
            chessplayer.addToDatabase();
            this->EndModal(true);
        }
        catch(DatabaseErrorException &exception)
        {
            wxMessageBox(exception.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        }
    }
    else
    {
        wxMessageBox(FORM_ERROR, GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
    }
}
/**
    Den h?r h?ndelsestyrda funktionen k?rs endast om anv?ndaren har valt att trycka p? knappen "?terst?ll".
    Alla data som anv?ndaren har fyllt i kommer att tas bort och de ursprungliga v?rdena kommer att visas.
*/
void AddChessplayerDialog::resetForm(wxCommandEvent &event)
{
    idField->SetValue("");
    firstnameField->SetValue("");
    lastnameField->SetValue("");
    maleButton->SetValue(true);
    birthdateField->SetValue("");
    federationField->SetValue("");
    clubField->SetValue("");
}

/**
    Den h?r h?ndelsestyrda funktionen k?rs om anv?ndaren har klickat p? "St?ng".
*/
void AddChessplayerDialog::closeDialog(wxCommandEvent &event)
{
    this->EndModal(true);
}

/**
     I den h?r konstruktorn k?rs de fyra funktionerna 'preCreate', 'create', 'postCreate' och 'addBinds'.
*/
AddTournamentDialog::AddTournamentDialog(const wxString &title):
    Dialog(title)
{
    preCreate();
    create();
    postCreate();
    addBinds();
}
/**
    I den h?r funktionen, skapas alla objekt som ?r specifika f?r klassen
    'AddTournamentDialog'.
*/
void AddTournamentDialog::create()
{
    idBox = new wxBoxSizer(wxHORIZONTAL);
    idLabel = new wxStaticText(this, -1, "Id: ");
    idField = new wxTextCtrl(this, -1);
    idLabel->SetFont(LABEL_FONT);
    idBox->Add(idLabel, 1, wxALL, Dialog::SPACE);
    idBox->Add(idField, 3, wxALL, Dialog::SPACE);
    verticalBox->Add(idBox, Dialog::LEFT_MARGIN, wxALL, 0);

    startDateBox = new wxBoxSizer(wxHORIZONTAL);
    startDateLabel = new wxStaticText(this, -1, "Startdatum: ");
    startDateField = new wxTextCtrl(this, -1);
    startDateLabel->SetFont(LABEL_FONT);
    startDateBox->Add(startDateLabel, 9, wxALL, Dialog::SPACE);
    startDateBox->Add(startDateField, 9, wxALL, Dialog::SPACE);
    verticalBox->Add(startDateBox, Dialog::LEFT_MARGIN, wxALL, 0);

    endDateBox = new wxBoxSizer(wxHORIZONTAL);
    endDateLabel = new wxStaticText(this, -1, "Slutdatum: ");
    endDateField = new wxTextCtrl(this, -1);
    endDateLabel->SetFont(LABEL_FONT);
    endDateBox->Add(endDateLabel, 9, wxALL, Dialog::SPACE);
    endDateBox->Add(endDateField, 9, wxALL, Dialog::SPACE);
    verticalBox->Add(endDateBox, Dialog::LEFT_MARGIN, wxALL, 0);

    numberOfRoundsBox = new wxBoxSizer(wxHORIZONTAL);
    numberOfRoundsLabel = new wxStaticText(this, -1, "Antal ronder: ");
    numberOfRoundsField = new wxTextCtrl(this, -1);
    numberOfRoundsLabel->SetFont(LABEL_FONT);
    numberOfRoundsBox->Add(numberOfRoundsLabel, 1, wxALL, Dialog::SPACE);
    numberOfRoundsBox->Add(numberOfRoundsField, 1, wxALL, Dialog::SPACE);
    verticalBox->Add(numberOfRoundsBox, Dialog::LEFT_MARGIN, wxALL, 0);

    pairingSystemBox = new wxBoxSizer(wxHORIZONTAL);
    pairingSystemLabel = new wxStaticText(this, -1, "Lottningssystem: ");
    pairingSystemComboBox = new wxComboBox(this, -1);
    pairingSystemComboBox->Append("Monrad");
    pairingSystemComboBox->Append("Berger");

    pairingSystemLabel->SetFont(LABEL_FONT);
    pairingSystemBox->Add(pairingSystemLabel, 0, wxALL, Dialog::SPACE);
    pairingSystemBox->Add(pairingSystemComboBox, 0, wxALL, Dialog::SPACE);
    verticalBox->Add(pairingSystemBox, Dialog::LEFT_MARGIN, wxALL, 0);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(this, -1, ADD_STRING);
    resetButton = new wxButton(this, -1, RESET_STRING);
    closeButton = new wxButton(this, -1, CLOSE_STRING);
    buttonBox->Add(addButton, 0, wxALL, AddTournamentDialog::SPACE);
    buttonBox->Add(resetButton, 0, wxALL, AddTournamentDialog::SPACE);
    buttonBox->Add(closeButton, 0, wxALL, AddTournamentDialog::SPACE);
    verticalBox->Add(buttonBox, Dialog::LEFT_MARGIN, wxALL, 0);
}

void AddTournamentDialog::addBinds()
{
    addButton->Bind(wxEVT_BUTTON, &AddTournamentDialog::addTournament, this);
    resetButton->Bind(wxEVT_BUTTON, &AddTournamentDialog::resetForm, this);
    closeButton->Bind(wxEVT_BUTTON, &AddTournamentDialog::closeDialog, this);
}

/**
    Den h?r h?ndelsestyrda funktionen k?rs n?r anv?ndaren har fyllt i alla turneringens data och klickat p?
    "L?gg till". Turneringen kommer endast att skapas, om alla data ?r korrekt.
*/
void AddTournamentDialog::addTournament(wxCommandEvent &event)
{
    tournamentModel.setID(idField->GetValue());
    tournamentModel.setStartDate(startDateField->GetValue());
    tournamentModel.setEndDate(endDateField->GetValue());
    tournamentModel.setNumberOfRounds(wxAtoi(numberOfRoundsField->GetValue()));
    tournamentModel.setPairingSystem(pairingSystemComboBox->GetValue());

    if(tournamentModel.validate())
    {
        try
        {
            tournamentModel.addToDatabase();
            this->EndModal(true);

        }
        catch(DatabaseErrorException &exception)
        {
            wxMessageBox(exception.what(),
                 GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
        }
    }
    else
    {
        wxMessageBox(FORM_ERROR, GENERAL_ERROR_MESSAGE, wxOK | wxICON_INFORMATION);
    }
}

/**
    Den h?r h?ndelsestyrda funktionen k?rs endast om anv?ndaren har valt att trycka p? knappen "?terst?ll".
    Alla data som anv?ndaren har fyllt i kommer att tas bort och de ursprungliga v?rdena kommer att visas.
*/
void AddTournamentDialog::resetForm(wxCommandEvent &event)
{
    idField->SetValue("");
    numberOfRoundsField->SetValue("");
    pairingSystemComboBox->SetValue("");
    startDateField->SetValue("");
    endDateField->SetValue("");
}
/**
    Den h?r h?ndelsestyrda funktionen k?rs om anv?ndaren har klickat p? "St?ng".
*/
void AddTournamentDialog::closeDialog(wxCommandEvent &event)
{
    this->EndModal(true);
}
