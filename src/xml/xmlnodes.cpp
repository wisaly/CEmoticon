#include "XmlNodes.h"

XmlNodes::XmlNodes( QDomNodeList nodeList )
{
	m_nodeList = nodeList; 

}

XmlNodes::XmlNodes( XmlNodes & refNodes )
{
	m_nodeList = refNodes.m_nodeList; 

}

XmlNodes::XmlNodes(void)
{
}

XmlNodes::~XmlNodes(void)
{
}

XmlNodesPtr XmlNodes::operator=( XmlNodesPtr pNodes )
{
	m_nodeList = pNodes->m_nodeList; 
	return pNodes; 
}

XmlNodes & XmlNodes::operator=( XmlNodes & refNodes )
{
	m_nodeList = refNodes.m_nodeList; 
	return (*this); 
}

int XmlNodes::count( void )
{
	int nCount = 0; 
	QDomNode node; 

    for( int i = 0; i < m_nodeList.length(); i++)
	{ 
		node = m_nodeList.item(i);

		if (node.nodeType() == QDomNode::ElementNode)
		{
			nCount ++;
		}
	} 

	return nCount;
}

XmlNodePtr XmlNodes::item(int index )
{
    Q_ASSERT( index >= 0 && index < count() );

	int nCount = 0;

	QDomNode node;

    XmlNodePtr pNode ( new XmlNode() );

    for( int i = 0; i < m_nodeList.length(); i++)
	{ 
		node = m_nodeList.item(i);

		if (node.nodeType() == QDomNode::ElementNode)
		{
            if( nCount == index )
			{ 
				pNode->m_node = node; 

				break;
			} 
			nCount ++;
		}
	} 

	return pNode; 
}

XmlNodePtr XmlNodes::item(QString name )
{
    Q_ASSERT( name != "" );

	QDomNode node;
    XmlNodePtr pNode ( new XmlNode() );

    for( int i = 0; i < m_nodeList.length(); i++)
	{ 
		node = m_nodeList.item(i);

		QString strFindName = node.nodeName();

        if (name == strFindName)
		{
			pNode->m_node = node; 
			break;
		}
	}

	return pNode; 
}
XmlNodePtr XmlNodes::operator[]( int index )
{
    return item(index);
}

XmlNodePtr XmlNodes::operator[]( QString name )
{
    return item(name);
}
