#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QString>
#include <QList>
#include "MVC.h"

class Setting
{
public:
    Setting(const QString &type, const QString &value):
        type(type), value(value) {}
    QString getType() const {return type; }
    QString getValue() const {return value; }

private:
    QString type;
    QString value;

};


class SettingsModel : public Model
{
public:
    SettingsModel() {}
    virtual ~SettingsModel() {}
    void addSettingToContainer(const Setting &setting);
    void addSettingToDatabase(const Setting &setting);
    QString getSettingByType(const QString &type) const;
    virtual void reset() override { settingsContainer.clear(); }

private:
    QVector<Setting> settingsContainer;

};

#endif // SETTINGSMODEL_H
