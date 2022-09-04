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
    viewModel->setTournament(tournament);

    try
    {
        tournament->print();
         viewModel->getTiebreaks()->getAll();
         tournament->getAllTiebreaks();
    }
    catch(DatabaseErrorException &error)
    {
        std::cout << error.what() << std::endl;
    }

    viewModel->notifyView(view);

}

void ManageTiebreaksController::selectTiebreakToAdd(wxGridEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    TournamentModel *tournament = viewModel->getTournament();

    if(tournament == nullptr)
    {
        return;
    }
    unsigned int index = event.GetRow();

    TiebreakModel *tiebreakModel = viewModel->getTiebreaks()->atIndex(index);
    viewModel->setSecondTiebreakModel(nullptr);
    viewModel->setFirstTiebreakModel(tiebreakModel);
}

void ManageTiebreaksController::selectTiebreakToRemove(wxGridEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    TournamentModel *tournament = viewModel->getTournament();

    if(tournament == nullptr)
    {
        return;
    }
    unsigned int index = event.GetRow();

    TiebreakModel *tiebreakModel = tournament->getTiebreak(index);
    viewModel->setFirstTiebreakModel(nullptr);
    viewModel->setSecondTiebreakModel(tiebreakModel);
}


void ManageTiebreaksController::addTiebreakSystem(wxCommandEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    TournamentModel *tournament = viewModel->getTournament();

    if(tournament == nullptr || viewModel->getFirstTiebreakModel() == nullptr)
    {
        return;
    }
    try
    {
        tournament->addTiebreakSystem(viewModel->getFirstTiebreakModel());
        viewModel->setFirstTiebreakModel(nullptr);
        viewModel->setSecondTiebreakModel(nullptr);
        viewModel->notifyAllViews();
    }
    catch(Exception &error)
    {
        error.showDialog();
    }

}

void ManageTiebreaksController::removeTiebreakSystem(wxCommandEvent &event)
{
    ManageTiebreaksViewModel *viewModel = (ManageTiebreaksViewModel*) model;
    TournamentModel *tournament = viewModel->getTournament();

    if(tournament == nullptr || viewModel->getSecondTiebreakModel() == nullptr)
    {
        return;
    }

    TiebreakModel* tiebreak = viewModel->getSecondTiebreakModel();

    try
    {
        tournament->removeTiebreakSystem(tiebreak);
        viewModel->setFirstTiebreakModel(nullptr);
        viewModel->setSecondTiebreakModel(nullptr);
        viewModel->notifyAllViews();
    }
    catch(Exception &error)
    {
        error.showDialog();
    }
}


