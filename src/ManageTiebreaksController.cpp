#include "ManageTiebreaksController.h"
#include "ViewModel.h"

ManageTiebreaksController::~ManageTiebreaksController()
{

}

void ManageTiebreaksController::changeTournament(wxCommandEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    unsigned int index = event.GetSelection();

    TournamentModel *tournament = viewModel->getTournaments()->get(index);
    viewModel->tournament(tournament);

    try
    {
        tournament->print();
         viewModel->getTiebreaks()->getAll();
    }
    catch(DatabaseErrorException &error)
    {
        std::cout << error.what() << std::endl;
    }

    viewModel->notifyView(view);

}

void ManageTiebreaksController::selectTiebreakSystem(wxGridEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    TournamentModel *tournament = viewModel->getTournament();

    if(tournament == nullptr)
    {
        return;
    }
    unsigned int index = event.GetRow();

    TiebreakModel *tiebreakModel = viewModel->getTiebreaks()->atIndex(index);
    viewModel->setTiebreakModel(tiebreakModel);
}

void ManageTiebreaksController::addTiebreakSystem(wxCommandEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    TournamentModel *tournament = viewModel->getTournament();

    if(tournament == nullptr)
    {
        return;
    }

    tournament->addTiebreakSystem(viewModel->getTiebreakModel());
    viewModel->notifyAllViews();
}
