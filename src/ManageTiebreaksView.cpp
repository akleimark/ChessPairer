#include "ManageTiebreaksView.h"

ManageTiebreaksView::ManageTiebreaksView(wxWindow *p_parent):
    View(p_parent, L"Hantera s\u00E4rskiljning")
{
    tournamentBox = new wxBoxSizer(wxHORIZONTAL);
    tournamentComboBox = new wxComboBox(parent, -1);
    tournamentComboBox->SetMinSize(wxSize(200, 40));
    tournamentBox->Add(tournamentComboBox, 0, wxALL, 10);
    this->Add(tournamentBox, View::MARGIN, wxALL, 0);
}

ManageTiebreaksView::~ManageTiebreaksView()
{

}

void ManageTiebreaksView::update(Model *model)
{

}

void ManageTiebreaksView::setController(Controller *_controller)
{

}
