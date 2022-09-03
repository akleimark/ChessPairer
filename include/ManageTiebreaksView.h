#ifndef MANAGETIEBREAKSVIEW_H
#define MANAGETIEBREAKSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>
#include "Table.h"
#include "TiebreakModel.h"
#include "ListModel.h"
#include <wx/listbox.h>
#include <wx/button.h>

class ManageTiebreaksView : public View
{
    public:
        ManageTiebreaksView(wxWindow *p_parent);
        virtual ~ManageTiebreaksView();
        virtual void update(Model *model);
        virtual void setController(Controller *_controller);

    protected:

    private:
        wxBoxSizer *tournamentBox;
        wxComboBox *tournamentComboBox;
        wxBoxSizer *bottomSizer;
        wxBoxSizer *leftSizer;
        wxBoxSizer *rightSizer;
        Table *tiebreaksTable;
        wxListBox *selectedTiebreaksList;
        wxStaticText *tiebreaksTableHeader;
        wxStaticText *selectedTiebreaksHeader;
        wxButton *addButton;
        void updateTiebreaks(ListModel<TiebreakModel*> *model);



};

#endif // MANAGETIEBREAKSVIEW_H
