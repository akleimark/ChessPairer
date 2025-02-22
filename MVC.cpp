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
    // Använd std::any_of för att kontrollera om vyn finns i listan och uppdatera om så är fallet
    if (std::any_of(views.begin(), views.end(), [view](const View *cView) { return cView == view; }))
    {
        view->updateView();
        return;
    }

    // Om ingen matchande vy hittades, kasta ett undantag
    throw std::runtime_error("Ingen vy kunde uppdateras.");
}

void Model::notifyAllViews()
{
    for(View *cView : views)
    {
        cView->updateView();
    }
}
