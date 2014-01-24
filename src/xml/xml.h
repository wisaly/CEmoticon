#ifndef XML_H
#define XML_H
#include <QDomDocument>
#include "XmlNode.h"
#include "XmlNodes.h"

/*!
	@brief XML解析库
*/
class Xml
{
public:
    Xml(void);
    ~Xml(void);

protected:
	QDomDocument	m_doc;
    QString			m_filePath;

public: 
	//! 打开文件
    bool open(QString xmlFilePath);
	//! 创建文件
    bool create(QString xmlFilePath,QString strRootName = "xml");
	//! 保存文件
    bool save(QString filePath = "");
	//! 获取根节点
    XmlNodePtr getRoot(void);
};
#endif
