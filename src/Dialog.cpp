#include "Dialog.h"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <iostream>
#include "ChessplayerModel.h"
#include <wx/msgdlg.h>
#include "Exception.h"

const unsigned int Dialog::LEFT_MARGIN = 5;
const unsigned int AddChessplayerDialog::SPACE = 10;
const unsigned int Dialog::DEFAULT_WIDTH = 700;
const unsigned int Dialog::DEFAULT_HEIGHT = 700;
const wxFont Dialog::LABEL_FONT = wxFont(11, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

/**
    I den här konstruktorn initieras klassens variabler. Superklassens konstruktor körs, samtidigt som
    'verticalBox' sätts till 'nullptr'.
*/
Dialog::Dialog(const wxString &title):
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)), verticalBox(nullptr)
{

}

void Dialog::preCreate()
{
    verticalBox = new wxBoxSizer(wxVERTICAL);
}

void Dialog::postCreate()
{
    SetSizer(verticalBox);
    Centre();

}

/**
    I den här konstruktorn körs de tre funktionerna 'preCreate', 'create' och 'postCreate'.
*/
AddChessplayerDialog::AddChessplayerDialog(const wxString &title):
    Dialog(title)
{
    preCreate();
    create();
    postCreate();
    addBinds();
}

AddChessplayerDialog::~AddChessplayerDialog()
{

}

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
    firstnameLabel = new wxStaticText(this, -1, "Firstname: ");
    firstnameField = new wxTextCtrl(this, -1);
    firstnameLabel->SetFont(LABEL_FONT);
    firstnameBox->Add(firstnameLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    firstnameBox->Add(firstnameField, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(firstnameBox, Dialog::LEFT_MARGIN, wxALL, 0);

    lastnameBox = new wxBoxSizer(wxHORIZONTAL);
    lastnameLabel = new wxStaticText(this, -1, "Lastname: ");
    lastnameField = new wxTextCtrl(this, -1);
    lastnameLabel->SetFont(LABEL_FONT);
    lastnameBox->Add(lastnameLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    lastnameBox->Add(lastnameField, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(lastnameBox, Dialog::LEFT_MARGIN, wxALL, 0);

    biologicalSexBox = new wxBoxSizer(wxHORIZONTAL);
    biologicalSexLabel = new wxStaticText(this, -1, "Biological sex: ");
    maleButton = new wxRadioButton(this, -1, "Male");
    femaleButton = new wxRadioButton(this, -1, "Female");
    biologicalSexLabel->SetFont(LABEL_FONT);
    biologicalSexBox->Add(biologicalSexLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    biologicalSexBox->Add(maleButton, 0, wxALL, AddChessplayerDialog::SPACE);
    biologicalSexBox->Add(femaleButton, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(biologicalSexBox, Dialog::LEFT_MARGIN, wxALL, 0);

    birthdateBox = new wxBoxSizer(wxHORIZONTAL);
    birthdateLabel = new wxStaticText(this, -1, "Birthdate: ");
    birthdateField = new wxTextCtrl(this, -1);
    birthdateLabel->SetFont(LABEL_FONT);
    birthdateBox->Add(birthdateLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    birthdateBox->Add(birthdateField, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(birthdateBox, Dialog::LEFT_MARGIN, wxALL, 0);

    federationBox = new wxBoxSizer(wxHORIZONTAL);
    federationLabel = new wxStaticText(this, -1, "Federation: ");
    federationField = new wxTextCtrl(this, -1);
    federationLabel->SetFont(LABEL_FONT);
    federationBox->Add(federationLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    federationBox->Add(federationField, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(federationBox, Dialog::LEFT_MARGIN, wxALL, 0);

    clubBox = new wxBoxSizer(wxHORIZONTAL);
    clubLabel = new wxStaticText(this, -1, "Club: ");
    clubField = new wxTextCtrl(this, -1);
    clubLabel->SetFont(LABEL_FONT);
    clubBox->Add(clubLabel, 0, wxALL, AddChessplayerDialog::SPACE);
    clubBox->Add(clubField, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(clubBox, Dialog::LEFT_MARGIN, wxALL, 0);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(this, -1, "Add");
    resetButton = new wxButton(this, -1, "Reset");
    closeButton = new wxButton(this, -1, "Close");
    buttonBox->Add(addButton, 0, wxALL, AddChessplayerDialog::SPACE);
    buttonBox->Add(resetButton, 0, wxALL, AddChessplayerDialog::SPACE);
    buttonBox->Add(closeButton, 0, wxALL, AddChessplayerDialog::SPACE);
    verticalBox->Add(buttonBox, Dialog::LEFT_MARGIN, wxALL, 0);

}

void AddChessplayerDialog::addBinds()
{
    addButton->Bind(wxEVT_BUTTON, &AddChessplayerDialog::addChessplayer, this);
    resetButton->Bind(wxEVT_BUTTON, &AddChessplayerDialog::resetForm, this);
    closeButton->Bind(wxEVT_BUTTON, &AddChessplayerDialog::closeDialog, this);
}

void AddChessplayerDialog::addChessplayer(wxCommandEvent &event)
{

    chessplayer.setID(wxAtoi(idField->GetValue()));
    chessplayer.setFirstname(firstnameField->GetValue());
    chessplayer.setLastname(lastnameField->GetValue());
    if(maleButton->GetValue() == true)
    {
        chessplayer.setBiologicalSex("male");
    }
    else
    {
        chessplayer.setBiologicalSex("female");
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
                 "Error", wxOK | wxICON_INFORMATION);
        }
    }
    else
    {
        wxMessageBox("There are errors in the form. Check your values.",
                 "Error", wxOK | wxICON_INFORMATION);
    }
}

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

void AddChessplayerDialog::closeDialog(wxCommandEvent &event)
{
    this->EndModal(true);
}

