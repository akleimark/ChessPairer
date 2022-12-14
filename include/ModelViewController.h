#ifndef MODELVIEWCONTROLLER_H
#define MODELVIEWCONTROLLER_H

#include <wx/sizer.h>
#include<set>
#include <wx/stattext.h>
#include <wx/font.h>

class Controller;
class View;

/**
    Den h?r klassen ?r en del av MVC-arkitekturen. Klassen ansvarar f?r att hantera
    data, som ofta har h?mtats fr?n databasen. Det ?r ocks? den h?r klassen som ansvarar f?r att
    uppdatera vyn.
*/
class Model
{
    public:
        Model() {}
        /// Klassen skapar inga objekt med hj?lp av 'new'. Det ?r d?rf?r som destruktorn ?r tom.
        virtual ~Model() {}
        void addView(View *view);
        void notifyView(View *view);
        void notifyAllViews();

    protected:
        /// I den h?r containern lagras alla de vyer, som modellen har ansvar f?r att uppdatera.
        std::set<View*> views;

    private:
};

/**
    Klassen View, som ?rver 'wxBoxSizer' ?r det som man ser. Den ?r ocks? en del av
    MVC-arkitekturen.
*/
class View : public wxBoxSizer
{
    public:
        View(wxWindow *p_parent, const wxString &labelString);
        /// Klassen skapar inga objekt med hj?lp av 'new'. Det ?r d?rf?r som destruktorn ?r tom.
        virtual ~View() {}
        /// Den h?r funktionen uppdaterar vyn. Den m?ste implementeras av de klasser som ?rver 'View'.
        virtual void update(Model *model) = 0;
        /// Den h?r funktionen st?ller in kontrollklassen och st?ller in vilken funktion som skall triggas
        /// f?r de objekt som ?r relevanta. Den h?r funktionen m?ste implementeras av alla klasser som ?rver 'View'.
        virtual void setController(Controller *_controller) = 0;

    protected:
        /// F?nstret som allt skall visas p?.
        wxWindow *parent;
        /// Den h?r variabeln anv?nds av klassen f?r att visa en rubrik.
        wxStaticText *label;
        const static unsigned int MARGIN;
        /// Det h?r ?r en klass-konstant f?r att s?tta ett typsnitt p? rubrikerna.
        const static wxFont LABEL_FONT;
        /// Det h?r ?r en klass-konstant f?r att s?tta ett typsnitt p? under-rubrikerna.
        const static wxFont H3_FONT;

    private:
};

/**
    Den h?r klassen ?r den som har yttersta ansvaret i MVC-arkitekturen.
*/

class Controller
{
    protected:
        Controller(Model *_model, View *_view);
        /// Klassen skapar inga objekt med hj?lp av 'new'. Det ?r d?rf?r som destruktorn ?r tom.
        virtual ~Controller() {}
        /// Det h?r ?r den modell, som exempelvis kan anv?ndas f?r att uppdatera vyn.
        Model *model;
        /// Det h?r ?r den vy som anv?nds.
        View *view;
};

#endif // MODELVIEWCONTROLLER_H
