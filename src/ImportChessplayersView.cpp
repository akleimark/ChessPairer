#include "ImportChessplayersView.h"
#include "Defs.h"

ImportChessplayersView::ImportChessplayersView(wxWindow *parent):
    View(parent, "Import chessplayers")
{
    fileTypeBox = new wxBoxSizer(wxHORIZONTAL);
    fileTypeLabel = new wxStaticText(parent, -1, "File type: ");
    xmlButton = new wxRadioButton(parent, -1, "XML");
    textFileButton = new wxRadioButton(parent, -1, "Textfile");

    fileTypeBox->Add(fileTypeLabel, 0, wxALL, 10);
    fileTypeBox->Add(xmlButton, 0, wxALL, 10);
    fileTypeBox->Add(textFileButton, 0, wxALL, 10);
    this->Add(fileTypeBox, View::MARGIN, wxALL, 0);

    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    importButton = new wxButton(parent, -1, "Import");
    buttonBox->Add(importButton, 0, wxALL, 10);
    this->Add(buttonBox, View::MARGIN, wxALL, 0);

}

ImportChessplayersView::~ImportChessplayersView()
{

}

void ImportChessplayersView::update(Model *model)
{

}

void ImportChessplayersView::setController(Controller *_controller)
{

}


