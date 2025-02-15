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
    QString value = "";
    for(const Setting &aSetting: settingsContainer)
    {
        if(aSetting.getType() == type)
        {
            return aSetting.getValue();
        }
    }

    return value;
}
