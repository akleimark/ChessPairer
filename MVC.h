#ifndef MVC_H
#define MVC_H

#include <QObject>
#include <QWidget>
#include <vector>

// Forward-deklarationer
class View;
class Model;

class Controller : public QObject
{
    Q_OBJECT
    public:
        Controller(Model *model, View *view);

    protected:
        Model *model;
        View *view;
};

class Model
{
    public:
        Model() {}
        ~Model() {}
        void addView(View* view) { views.push_back(view); }
        void notifyView(View *view);
        void notifyAllViews();

    protected:
        std::vector<View*> views;
};

class View : public QWidget
{
    protected:
        Controller *controller;
        Model *model;

    public:
        View() : controller(nullptr) {}
        View(Model *model): controller(nullptr), model(model) {}
        virtual void updateView() const = 0;
        virtual void addListeners() = 0;
        void setController(Controller *controller) {this->controller = controller; }

};

#endif // MVC_H
