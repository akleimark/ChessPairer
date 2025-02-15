#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "MVC.h"
#include "SettingsModel.h"
#include <QFontComboBox>

class SettingsView : public View
{
public:
    SettingsView(SettingsModel *model);
    virtual void updateView() const override;
    virtual void addListeners() override;

private:
    QVBoxLayout *layout;
    QFontComboBox *fontComboBox;
    void createUI();
    SettingsModel *model;
};

#endif // SETTINGSVIEW_H
