#include "ModelViewController.h"

const unsigned int View::MARGIN = 20;
const wxFont View::LABEL_FONT = wxFont(11, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

View::View(wxWindow *p_parent, const wxString &labelString):
    wxBoxSizer(wxVERTICAL), parent(p_parent)
{
    label = new wxStaticText(parent, -1, labelString);
    this->Add(label, 0, wxALIGN_CENTER, 0);

    font = new wxFont;
    font->SetFaceName("Georgia");
    font->SetPointSize(16);
    label->SetFont(*font);
    this->Show(false);
}


void Model::addView(View *view)
{
    views.insert(view);
}

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




