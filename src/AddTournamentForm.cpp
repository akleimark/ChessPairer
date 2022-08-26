#include "AddTournamentForm.h"
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>

AddTournamentForm::AddTournamentForm(wxWindow *parent)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxButton(parent, -1, "A Really Really Big Button"), 1, 0, 0);
    sizer->Add(new wxButton(parent, -1, "Tiny Button"), 3, 0, 0);
    sizer->SetSizeHints(parent);
    parent->SetSizer(sizer);

}

AddTournamentForm::~AddTournamentForm()
{

}
