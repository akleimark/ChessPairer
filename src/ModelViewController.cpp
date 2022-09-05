#include "ModelViewController.h"

const unsigned int View::MARGIN = 20;
const wxFont View::LABEL_FONT = wxFont(11, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
const wxFont View::H3_FONT = wxFont(9, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

View::View(wxWindow *p_parent, const wxString &labelString):
    wxBoxSizer(wxVERTICAL), parent(p_parent)
{
    label = new wxStaticText(parent, -1, labelString);
    this->Add(label, 0, wxALIGN_CENTER, 0);

    wxFont font(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    label->SetFont(font);
    this->Show(false);
}

/**
    Den här funktionen lägger till en vy till containern 'views'.
    @param view En pekare till den vy, som skall läggas till.
*/
void Model::addView(View *view)
{
    views.insert(view);
}

/**

*/
void Model::notifyView(View *view)
{
    for(View *cView : views)
    {
        if(view == cView)
        {
            view->update(this);
            break;
        }
    }
}

void Model::notifyAllViews()
{
    for(View *view : views)
    {
        view->update(this);
    }
}

Controller::Controller(Model *_model, View *_view):
    model(_model), view(_view)
{

}


