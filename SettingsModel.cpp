#include "SettingsModel.h"
#include "Database.h"

void SettingsModel::addSettingToContainer(const Setting &setting)
{
    settingsContainer.push_back(setting);
}


void SettingsModel::addSettingToDatabase(const Setting &setting)
{
    Database* db = Database::getInstance();
    QSqlQuery query(db->getDatabase());  // Använd rätt databasinstans

    query.prepare("INSERT OR REPLACE INTO settings (type, value) VALUES (:type, :value)");
    query.bindValue(":type", setting.getType());
    query.bindValue(":value", setting.getValue());

    if (!query.exec())
    {
        qDebug() << "Fel vid inmatning i databasen:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Inställning sparad:" << setting.getType() << "=" << setting.getValue();
    }
}


QString SettingsModel::getSettingByType(const QString &type) const
{
    // Använd std::find_if för att hitta den första instansen av en inställning med rätt typ
    auto it = std::find_if(settingsContainer.begin(), settingsContainer.end(),
    [&type](const Setting &aSetting)
    {
       return aSetting.getType() == type;
    });

    // Returnera värdet om inställningen hittades, annars en tom QString
    return (it != settingsContainer.end()) ? it->getValue() : "";
}

