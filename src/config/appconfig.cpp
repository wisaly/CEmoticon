#include <QApplication>
#include "appconfig.h"
#include "xml/xml.h"
#include "common/common.h"

AppConfig::AppConfig()
{
    configFilePath = QApplication::applicationDirPath() + "/"
            + APP_CONFIG_FILE;
}

AppConfig *AppConfig::inst()
{
    static AppConfig inst;
    return &inst;
}

bool AppConfig::load()
{
    Xml xml;
    if (!xml.open(configFilePath))
    {
        if(!save())
        {
            return false;
        }
        return true;
    }

    XmlNodePtr pRoot = xml.getRoot();

    //QString s = pRoot->GetName();
    // ConfigWindow
    XmlNodePtr pConfigWindow = pRoot->getChild("ConfigWindow");
    this->configWindow.popAtStart = pConfigWindow->getAttribute("PopAtStart",false);

    // AccerateKey
    XmlNodePtr pAccerateKey = pRoot->getChild("AccerateKey");
    this->accerateKey.popSelect = pAccerateKey->getAttribute("PopSelect");

    // PopWindow
    XmlNodePtr pPopWindow = pRoot->getChild("PopWindow");
    this->popWindow.ctrlPadding = pPopWindow->getAttribute("CtrlPadding",int(0));
    this->popWindow.fontSize = pPopWindow->getAttribute("FontSize",int(0));
    this->popWindow.fontName = pPopWindow->getAttribute("FontName");
    this->popWindow.width = pPopWindow->getAttribute("Width",int(100));
    this->popWindow.height = pPopWindow->getAttribute("Height",int(50));

    // PopWindow.PageHeader
    XmlNodePtr pPageHeader = pPopWindow->getChild("PageHeader");
    this->popWindow.pageHeader.headerHeight = pPageHeader->getAttribute("HeaderHeight",int(0));
    this->popWindow.pageHeader.headerHorzMargin = pPageHeader->getAttribute("HeaderHorzMargin",int(0));
    this->popWindow.pageHeader.headerTopMargin = pPageHeader->getAttribute("HeaderTopMargin",int(0));
    this->popWindow.pageHeader.headerActiveHorzMargin = pPageHeader->getAttribute("HeaderActiveHorzMargin",int(0));
    this->popWindow.pageHeader.headerActiveTopMargin = pPageHeader->getAttribute("HeaderActiveTopMargin",int(0));
    this->popWindow.pageHeader.pagePadding = pPageHeader->getAttribute("PagePadding",int(0));
    // PopWindow.Pages
    XmlNodePtr pPages = pPopWindow->getChild("Pages");
    this->popWindow.pages.colors.clear();
    XmlNodesPtr pColors = pPages->getChild("Colors")->getChildren();
    for (int i = 0;i < pColors->count();i ++)
    {
        this->popWindow.pages.colors.append((*pColors)[i]->getAttribute("rgb",QColor()));
    }
    // PopWindow.PageItem
    XmlNodePtr pPageItem = pPopWindow->getChild("PageItem");
    this->popWindow.pageItem.itemPadding = pPageItem->getAttribute("ItemPadding",int(0));
    this->popWindow.pageItem.columnCount = pPageItem->getAttribute("ColumnCount",int(1));  // use default to avoid deviding by 0
    this->popWindow.pageItem.rowCount = pPageItem->getAttribute("RowCount",int(1));        //
    this->popWindow.pageItem.colors.background = pPageItem->getChild("Colors")->getAttribute("Background",QColor());
    this->popWindow.pageItem.colors.foreground = pPageItem->getChild("Colors")->getAttribute("Foreground",QColor());
    this->popWindow.pageItem.colors.hightlight = pPageItem->getChild("Colors")->getAttribute("Hightlight",QColor());
    this->popWindow.pageItem.colors.checked = pPageItem->getChild("Colors")->getAttribute("Checked",QColor());
    this->popWindow.pageItem.colors.disabled = pPageItem->getChild("Colors")->getAttribute("Disabled",QColor());

    // Sources
    XmlNodesPtr pSources = pRoot->getChild("Sources")->getChildren();
    this->sources.active = 0;
    this->sources.files.clear();
    for (int i = 0;i < pSources->count();i ++)
    {
        XmlNodePtr pFile = (*pSources)[i];
        this->sources.files.append(
                    EmoConfig(pFile->getAttribute("LocalPath"),
                              pFile->getAttribute("RemotePath")));
        if (this->sources.active == 0 && pFile->getAttribute("Active",false))
        {
            this->sources.active = &this->sources.files.last();
        }
    }

    return true;
}

bool AppConfig::save()
{
    Xml xml;
    if (!xml.open(configFilePath))
    {
        if (xml.create(configFilePath,"CEConfig"))
        {
            return false;
        }
    }

    XmlNodePtr pRoot = xml.getRoot();
    pRoot->removeChildren();

    // ConfigWindow
    XmlNodePtr pConfigWindow = pRoot->appendChild("ConfigWindow");
    pConfigWindow->setAttribute("PopAtStart",this->configWindow.popAtStart);

    // AccerateKey
    XmlNodePtr pAccerateKey = pRoot->appendChild("AccerateKey");
    pAccerateKey->setAttribute("PopSelect",this->accerateKey.popSelect);

    // PopWindow
    XmlNodePtr pPopWindow = pRoot->appendChild("PopWindow");
    pPopWindow->setAttribute("CtrlPadding",this->popWindow.ctrlPadding);
    pPopWindow->setAttribute("FontSize",this->popWindow.fontSize);
    pPopWindow->setAttribute("FontName",this->popWindow.fontName);
    pPopWindow->setAttribute("Width",this->popWindow.width);
    pPopWindow->setAttribute("Height",this->popWindow.height);


    // PopWindow.PageHeader
    XmlNodePtr pPageHeader = pPopWindow->appendChild("PageHeader");
    pPageHeader->setAttribute("HeaderHeight",this->popWindow.pageHeader.headerHeight);
    pPageHeader->setAttribute("HeaderHorzMargin",this->popWindow.pageHeader.headerHorzMargin);
    pPageHeader->setAttribute("HeaderTopMargin",this->popWindow.pageHeader.headerTopMargin);
    pPageHeader->setAttribute("HeaderActiveHorzMargin",this->popWindow.pageHeader.headerActiveHorzMargin);
    pPageHeader->setAttribute("HeaderActiveTopMargin",this->popWindow.pageHeader.headerActiveTopMargin);
    pPageHeader->setAttribute("PagePadding",this->popWindow.pageHeader.pagePadding);
    // PopWindow.Pages
    XmlNodePtr pPages = pPopWindow->appendChild("Pages");
    XmlNodePtr pColors = pPages->appendChild("Colors");

    for (int i = 0;i < this->popWindow.pages.colors.count();i++)
    {
        pColors->appendChild("Color")->setAttribute("rgb",this->popWindow.pages.colors[i]);
    }
    // PopWindow.PageItem
    XmlNodePtr pPageItem = pPopWindow->appendChild("PageItem");
    pPageItem->setAttribute("ItemPadding",this->popWindow.pageItem.itemPadding);
    pPageItem->setAttribute("ColumnCount",this->popWindow.pageItem.columnCount);
    pPageItem->setAttribute("RowCount",this->popWindow.pageItem.rowCount);
    pPageItem->appendChild("Colors")->setAttribute("Background",this->popWindow.pageItem.colors.background);
    pPageItem->appendChild("Colors")->setAttribute("Foreground",this->popWindow.pageItem.colors.foreground);
    pPageItem->appendChild("Colors")->setAttribute("Hightlight",this->popWindow.pageItem.colors.hightlight);
    pPageItem->appendChild("Colors")->setAttribute("Checked",this->popWindow.pageItem.colors.checked);
    pPageItem->appendChild("Colors")->setAttribute("Disabled",this->popWindow.pageItem.colors.disabled);

    return xml.save();
}
