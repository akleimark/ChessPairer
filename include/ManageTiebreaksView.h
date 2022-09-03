#ifndef MANAGETIEBREAKSVIEW_H
#define MANAGETIEBREAKSVIEW_H

#include "ModelViewController.h"
#include <wx/combobox.h>

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
};

#endif // MANAGETIEBREAKSVIEW_H
