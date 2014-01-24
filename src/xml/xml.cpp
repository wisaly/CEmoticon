#include "Xml.h"
#include <QFile>
#include <QTextStream>

Xml::Xml(void)
{
}

Xml::~Xml(void)
{
	//Close();
}

bool Xml::open(QString xmlFilePath )
{
    QFile file(xmlFilePath);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		return false;
	}

	if (!m_doc.setContent(&file,false))
	{
		return false;
	}

    m_filePath = xmlFilePath;

	return true;
}

bool Xml::create(QString xmlFilePath, QString rootName )
{
    if(QFile::exists(xmlFilePath))
	{
		return false;
	}
    QFile file(xmlFilePath);
	file.open(QFile::WriteOnly);
	file.close();

	m_doc.clear();
    m_filePath = xmlFilePath;

	QDomNode node = m_doc.createProcessingInstruction("xml","version=\"1.0\"");
	m_doc.appendChild(node);
    node = m_doc.createElement(rootName);
	m_doc.appendChild(node);

	return save();
}

XmlNodePtr Xml::getRoot( void )
{
	Q_ASSERT(!m_doc.isNull());

	QDomElement element = m_doc.documentElement();

	// 不存在 则 创建 
	if(element.isNull())
	{ 
		element = m_doc.createElement("xmlRoot");
		Q_ASSERT(!element.isNull()); 

		m_doc.appendChild(element); 
	} 

    XmlNodePtr pNode(new XmlNode(element));

	return pNode; 
}

bool Xml::save(QString filePath /*= ""*/ )
{
	Q_ASSERT(!m_doc.isNull());

    if( !filePath.isEmpty() )
	{
        m_filePath = filePath;
	}
	
    QFile f(m_filePath);
	if(!f.open(QFile::WriteOnly | QFile::Text))
		return false;

	QTextStream out(&f);

	out.setCodec("UTF-8"); //中文编码

	m_doc.save(out,4,QDomDocument::EncodingFromDocument);

	return true; 
}

//XmlNodePtr Xml::SelectSingleNode( QString strPath )
//{
//	Q_ASSERT(!m_doc.isNull());
//
//	QDomNode node = m_doc.namedItem(strPath);
//
//	XmlNodePtr pNode ( new XmlNode(node) );
//
//	return pNode; 
//}
//
//XmlNodesPtr Xml::SelectNodes( QString strPath )
//{
//	Q_ASSERT(!m_doc.isNull());
//
//	QDomNodeList nodeList = m_doc.elementsByTagName(strPath);
//
//	XmlNodesPtr pNodes ( new XmlNodes(nodeList) );
//
//	return pNodes; 
//}
