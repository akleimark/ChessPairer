#include "MVC.h"

const QFont View::DEFAULT_LABEL_FONT = QFont("Georgia", 14, 700);
const QFont View::DEFAULT_NORMAL_FONT = QFont("Georgia", 14, 400);
const QFont View::DEFAULT_HEADER_FONT = QFont("Georgia", 16, 700);

Controller::Controller(Model *model, View *view):
    model(model), view(view)
{
    model->addView(view);
    view->setController(this);
}

void Model::notifyView(View *view)
{
    for(View *cView : views)
    {
        if(cView == view)
        {
            view->updateView();
            return;
        }
    }
    throw std::runtime_error("Ingen vy kunde uppdateras.");
}
void Model::notifyAllViews()
{
    for(View *cView : views)
    {
        cView->updateView();
    }
}
