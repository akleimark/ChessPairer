#include "ImportChessplayersView.h"
#include "Defs.h"
#include "ImportChessplayersController.h"

/**
    I den här konstruktorn läggs alla objekt in, för att visa vyn på ett korrekt vis.
*/
ImportChessplayersView::ImportChessplayersView(wxWindow *parent):
    View(parent, "Importera schackspelare")
{
    fileTypeBox = new wxBoxSizer(wxHORIZONTAL);
    fileTypeLabel = new wxStaticText(parent, -1, "Typ av fil: ");
    fileTypeLabel->SetFont(LABEL_FONT);
    xmlButton = new wxRadioButton(parent, -1, "XML");
    xmlButton->SetId(XML_BUTTON_ID);
    textFileButton = new wxRadioButton(parent, -1, "Textfil");
    textFileButton->SetId(TEXTFILE_BUTTON_ID);

    fileTypeBox->Add(fileTypeLabel, 0, wxALL, 10);
    fileTypeBox->Add(xmlButton, 0, wxALL, 10);
    fileTypeBox->Add(textFileButton, 0, wxALL, 10);
    this->Add(fileTypeBox, View::MARGIN, wxALL, 0);

    selectFileBox = new wxBoxSizer(wxHORIZONTAL);
    selectFileLabel = new wxStaticText(parent, -1, L"V\u00E4lj fil: ");
    selectFileLabel->SetFont(View::LABEL_FONT);
    selectFileField = new wxTextCtrl(parent, -1);
    selectFileBox->Add(selectFileLabel, 0, wxALL, 10);
    selectFileBox->Add(selectFileField, 0, wxALL, 10);
    this->Add(selectFileBox, View::MARGIN, wxALL, 0);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    importButton = new wxButton(parent, -1, "Importera");
    buttonBox->Add(importButton, 0, wxALL, 10);
    this->Add(buttonBox, View::MARGIN, wxALL, 0);
}


void ImportChessplayersView::setController(Controller *_controller)
{
    ImportChessplayersController *controller = (ImportChessplayersController*) _controller;

    xmlButton->Bind(wxEVT_RADIOBUTTON, &ImportChessplayersController::setFileType, controller);
    textFileButton->Bind(wxEVT_RADIOBUTTON, &ImportChessplayersController::setFileType, controller);
    selectFileField->Bind(wxEVT_TEXT, &ImportChessplayersController::setFile, controller);
    importButton->Bind(wxEVT_BUTTON, &ImportChessplayersController::startImport, controller);
}
