#include "emoconfig.h"

#include <xml/xml.h>

EmoConfig::EmoConfig(QString localPath,QString remotePath)
{
    this->localPath = localPath;
    this->remotePath = remotePath;

    download();
    load();
}

bool EmoConfig::download()
{
    if(!remotePath.isEmpty())
    {
    }

    return true;
}

bool EmoConfig::load()
{
    Xml xml;
    if (!xml.open(localPath))
    {
        if(!save())
        {
            return false;
        }
        return true;
    }

    XmlNodePtr pRoot = xml.getRoot();
    XmlNodesPtr pInfoos = pRoot->getChild("infoos")->getChildren();
    for (int i = 0;i < pInfoos->count();i++)
    {
        this->infoos.info.append((*pInfoos)[i]->getString());
    }
    
    for (XmlNodePtr pCategory = pRoot->getChild("category");
         pCategory = pCategory->getNextSibling("category");
         pCategory->isNull())
    {
        Category category;
        category.name = pCategory->getAttribute("name");
        XmlNodesPtr pEntries = pCategory->getChildren();
        for (int i = 0;i < pEntries->count();i++)
        {
            Category::Entry entry;
            entry.string = (*pEntries)[i]->getChild("string")->getString();
            entry.note = (*pEntries)[i]->hasChild("note") ?
                        (*pEntries)[i]->getChild("note")->getString() : QString();

            category.entry.append(entry);
        }
        this->category.append(category);
    }
    return true;
}

bool EmoConfig::save()
{
    Xml xml;
    if (!xml.open(localPath))
    {
        if (xml.create(localPath,"emoji"))
        {
            return false;
        }
    }

    XmlNodePtr pRoot = xml.getRoot();
    pRoot->removeChildren();

    XmlNodePtr pInfoos = pRoot->appendChild("infoos");
    for (int i = 0;i < this->infoos.info.count();i++)
    {
        pInfoos->appendChild("info")->setString(this->infoos.info[i]);
    }
    for (int i = 0;i < this->category.count();i++)
    {
        XmlNodePtr pCategory = pRoot->appendChild("category");
        pCategory->setAttribute("name",this->category[i].name);
        for (int j = 0;j < this->category[i].entry.count();j++)
        {
            XmlNodePtr pEntry = pCategory->appendChild("entry");
            pEntry->appendChild("string")->setString(
                        this->category[i].entry[j].string);
            if (!this->category[i].entry[j].note.isEmpty())
            {
                pEntry->appendChild("note")->setString(
                            this->category[i].entry[j].note);
            }
        }
    }

    return xml.save();
}
