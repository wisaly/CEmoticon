#ifndef EMOCONFIG_H
#define EMOCONFIG_H
#include <QString>
#include <QStringList>
#include <QList>

class EmoConfig
{
    QString configFilePath;
    struct Infoos
    {
        QStringList info;
    }infoos;
    struct Category
    {
        QString name;
        struct Entry
        {
            QString string;
            QString note;
        };
        QList<Entry> entry;
    };
    QList<Category> category;

    bool isModifying;
public:
    EmoConfig(QString file);

    bool load();
    bool save();
};

#endif // EMOCONFIG_H
