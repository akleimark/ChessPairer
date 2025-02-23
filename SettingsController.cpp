#include "SettingsController.h"
#include <QDebug>
#include "SettingsModel.h"
#include "Logger.h"

SettingsController::SettingsController(SettingsModel *model, SettingsView *view)
    : Controller(model, view), settingsModel(model), settingsView(view)
{

}

void SettingsController::onFontChanged(const QFont &font)
{
    Logger::getInstance()->logInfo( "Typsnitt ändrat till:" + font.family());
    settingsModel->addSettingToContainer(Setting("font", font.family()));
    settingsModel->addSettingToDatabase(Setting("font", font.family()));
}
