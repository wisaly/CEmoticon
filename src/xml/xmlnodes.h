#ifndef XMLNODES_H
#define XMLNODES_H

#include ".\XmlNode.h"

/*!
	@brief 节点列表类

	注意操作时使用QXmlNodesPtr来操作
*/
class XmlNodes
{
    friend class Xml;
    friend class XmlNode;

public: 
    ~XmlNodes(void);
    XmlNodes(void);
    XmlNodes( XmlNodes & refNodes );

    XmlNodesPtr operator = (XmlNodesPtr pNodes);
    XmlNodes & operator = (XmlNodes & refNodes);
    //! @see item()
    XmlNodePtr operator[] ( int index );
    //! @see item()
    XmlNodePtr operator[] ( QString name );

	//! 获取数量
    int count(void);

	// 按索引获节点项
    XmlNodePtr item( int index );
	// 按名字获取节点项
    XmlNodePtr item( QString name );

protected: 
    XmlNodes(QDomNodeList nodeList);
	QDomNodeList m_nodeList; 
};
#endif
