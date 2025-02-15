#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include "MVC.h"
#include "SettingsModel.h"
#include "SettingsView.h"

class SettingsController : public Controller
{
    Q_OBJECT
public:
    SettingsController(SettingsModel *model, SettingsView *view);

private:
    SettingsModel *settingsModel;
    SettingsView *settingsView;

public slots:
    void onFontChanged(const QFont &font);

};

#endif // SETTINGSCONTROLLER_H
