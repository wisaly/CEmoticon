#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>
#include <QList>
#include <QColor>

class AppConfig
{
public:
    QString configFilePath;
    struct ConfigWindow
    {
        bool popAtStart;
    }configWindow;
    struct AccerateKey
    {
        QString popSelect;
    }accerateKey;
    struct PopWindow
    {
        int ctrlPadding;
        int fontSize;
        QString fontName;
        int width;
        int height;
        struct PageHeader
        {
            int headerHeight;
            int headerHorzMargin;
            int headerTopMargin;
            int headerActiveHorzMargin;
            int headerActiveTopMargin;
            int pagePadding;
        }pageHeader;
        struct Pages
        {
            QList<QColor> colors;
        }pages;
        struct PageItem
        {
            int itemPadding;
            int columnCount;
            int rowCount;
            struct Colors
            {
                QColor background;
                QColor foreground;
                QColor hightlight;
                QColor checked;
                QColor disabled;
            }colors;
        }pageItem;
    }popWindow;
    bool isModifying;
private:
    AppConfig();
public:
    static AppConfig *inst();

    bool load();
    bool save();
};

#endif // APPCONFIG_H
