#ifndef MODELVIEWCONTROLLER_H
#define MODELVIEWCONTROLLER_H

#include <wx/sizer.h>
#include<set>
#include <wx/stattext.h>
#include <wx/font.h>

class Controller;
class View;

/**
    Den här klassen är en del av MVC-arkitekturen. Klassen ansvarar för att hantera
    data, som ofta har hämtats från databasen. Det är också den här klassen som ansvarar för att
    uppdatera vyn.
*/
class Model
{
    public:
        Model() {}
        /// Klassen skapar inga objekt med hjälp av 'new'. Det är därför som destruktorn är tom.
        virtual ~Model() {}
        void addView(View *view);
        void notifyView(View *view);
        void notifyAllViews();

    protected:
        /// I den här containern lagras alla de vyer, som modellen har ansvar för att uppdatera.
        std::set<View*> views;

    private:
};

/**
    Klassen View, som ärver 'wxBoxSizer' är det som man ser. Den är också en del av
    MVC-arkitekturen.
*/
class View : public wxBoxSizer
{
    public:
        View(wxWindow *p_parent, const wxString &labelString);
        /// Klassen skapar inga objekt med hjälp av 'new'. Det är därför som destruktorn är tom.
        virtual ~View() {}
        /// Den här funktionen uppdaterar vyn. Den måste implementeras av de klasser som ärver 'View'.
        virtual void update(Model *model) = 0;
        /// Den här funktionen ställer in kontrollklassen och ställer in vilken funktion som skall triggas
        /// för de objekt som är relevanta. Den här funktionen måste implementeras av alla klasser som ärver 'View'.
        virtual void setController(Controller *_controller) = 0;

    protected:
        /// Fönstret som allt skall visas på.
        wxWindow *parent;
        /// Den här variabeln används av klassen för att visa en rubrik.
        wxStaticText *label;
        const static unsigned int MARGIN;
        /// Det här är en klass-konstant för att sätta ett typsnitt på rubrikerna.
        const static wxFont LABEL_FONT;
        /// Det här är en klass-konstant för att sätta ett typsnitt på under-rubrikerna.
        const static wxFont H3_FONT;

    private:
};

/**
    Den här klassen är den som har yttersta ansvaret i MVC-arkitekturen.
*/

class Controller
{
    protected:
        Controller(Model *_model, View *_view);
        /// Klassen skapar inga objekt med hjälp av 'new'. Det är därför som destruktorn är tom.
        virtual ~Controller() {}
        /// Det här är den modell, som exempelvis kan användas för att uppdatera vyn.
        Model *model;
        /// Det här är den vy som används.
        View *view;
};

#endif // MODELVIEWCONTROLLER_H
