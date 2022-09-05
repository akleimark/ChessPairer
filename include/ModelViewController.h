#ifndef MODELVIEWCONTROLLER_H
#define MODELVIEWCONTROLLER_H

#include <wx/sizer.h>
#include<set>
#include <wx/stattext.h>
#include <wx/font.h>

class Controller;
class View;

/**

*/
class Model
{
    public:
        Model() {}
        virtual ~Model() {}
        void addView(View *view);
        void notifyView(View *view);
        void notifyAllViews();

    protected:
        /// I den här containern lagras alla de vyer, som modellen har ansvar för att uppdatera.
        std::set<View*> views;

    private:
};

class View : public wxBoxSizer
{
    public:
        View(wxWindow *p_parent, const wxString &labelString);
        virtual ~View() {}
        virtual void update(Model *model) = 0;
        virtual void setController(Controller *_controller) = 0;

    protected:
        /// Fönstret som allt skall visas på.
        wxWindow *parent;
        /// Den här variabeln används av klassen för att visa en rubrik.
        wxStaticText *label;
        const static unsigned int MARGIN;
        const static wxFont LABEL_FONT;
        const static wxFont H3_FONT;

    private:
};

class Controller
{
    protected:

        Controller(Model *_model, View *_view);
        virtual ~Controller() {}
        Model *model;
        View *view;
};

#endif // MODELVIEWCONTROLLER_H
