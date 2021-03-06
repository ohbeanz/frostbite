#ifndef HIGHLIGHTSETTINGS_H
#define HIGHLIGHTSETTINGS_H

#include <QSettings>
#include <QApplication>
#include <QDebug>

#include <text/highlight/highlightsettingsentry.h>
#include <clientsettings.h>

class HighlightSettings {

public:
    HighlightSettings();
    ~HighlightSettings();

    void setSingleParameter(QString name, QVariant value);
    QVariant getSingleParameter(QString name, QVariant defaultValue);

    QList<HighlightSettingsEntry>* settingsList;

    void init();
    void setParameter(QString, HighlightSettingsEntry entry);
    void addParameter(QString, HighlightSettingsEntry entry);
    QList<HighlightSettingsEntry>* getSettings(QString);
    void setSettings(QString, QList<HighlightSettingsEntry>*);
    void loadSettings(QString);

private:
    QSettings* settings;

};

#endif // HIGHLIGHTSETTINGS_H
