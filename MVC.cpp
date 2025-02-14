#include "MVC.h"

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
        }
    }
}
void Model::notifyAllViews()
{
    for(View *cView : views)
    {
        cView->updateView();

    }
}
