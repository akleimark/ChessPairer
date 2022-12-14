#include "ModelViewController.h"

const unsigned int View::MARGIN = 20;
const wxFont View::LABEL_FONT = wxFont(11, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
const wxFont View::H3_FONT = wxFont(9, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

/**
    I den h?r konstruktorn l?ggs rubriken till vyn. Alla klasser som ?rver den h?r klassen
    kommer allts? att ha en rubrik, vars text skickas med via underklassernas konstruktorer.
*/
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
    Den h?r funktionen l?gger till en vy till containern 'views'.
    @param view En pekare till den vy, som skall l?ggas till.
*/
void Model::addView(View *view)
{
    views.insert(view);
}

/**
    Den h?r funktionen uppdaterar en specifik vy.
    @param view En pekare till den vy som skall uppdateras.
*/
void Model::notifyView(View *view)
{
    if(std::any_of(views.begin(), views.end(), [view](View *c){return c == view; }))
    {
        view->update(this);
    }

}

/**
    Den h?r funktionen uppdaterar alla vyer som finns i containern 'views'.
*/
void Model::notifyAllViews()
{
    for(View *view : views)
    {
        view->update(this);
    }
}

/**
    Den h?r konstruktorn s?tter bara v?rdet p? modellklassen och vyklassen via
    argumenten.
    @param _model En pekare till den 'Model', som klassen anv?nder
    @param _view En pekare till den 'View', som klassen anv?nder.
*/
Controller::Controller(Model *_model, View *_view):
    model(_model), view(_view)
{

}


