#include "XmlNode.h"
#include "XmlNodes.h"

// 构造函数
XmlNode::XmlNode( QDomNode node )
{
	m_node = node;
}

XmlNode::XmlNode(void)
{
}

XmlNode::XmlNode( XmlNode & refNode )
{
	m_node = refNode.m_node; 
}

// 析构函数
XmlNode::~XmlNode(void)
{
}

XmlNodePtr XmlNode::operator=( XmlNodePtr pNode )
{
	m_node = pNode->m_node; 
	return pNode; 
}

XmlNode & XmlNode::operator=( XmlNode & refNode )
{
	m_node = refNode.m_node; 
	return (*this); 
}

bool XmlNode::isNull( void )
{
	return m_node.isNull(); 
}

XmlNodePtr XmlNode::getChild(QString name )
{
	Q_ASSERT(!m_node.isNull());

    QDomNode childNode = m_node.namedItem(name);
	
	if (childNode.isNull())
	{
        return appendChild(name);
	}

    XmlNodePtr pChild( new XmlNode(childNode) );

    return pChild;
}

XmlNodePtr XmlNode::getNextSibling(QString name)
{
    Q_ASSERT(!m_node.isNull());

    QDomNode sibling = m_node.nextSiblingElement(name);

    return XmlNodePtr(new XmlNode(sibling));
}

bool XmlNode::hasChild(QString name)
{
    Q_ASSERT(!m_node.isNull());

    return m_node.namedItem(name).isNull();
}

XmlNodePtr XmlNode::appendChild(QString name )
{
	Q_ASSERT(!m_node.isNull());

	QDomDocument doc = m_node.ownerDocument();
	Q_ASSERT(!doc.isNull());

    QDomNode childNode = doc.createElement(name);
	Q_ASSERT(!childNode.isNull());

	m_node.appendChild(childNode);

    XmlNodePtr pChild( new XmlNode(childNode) );

	return pChild; 
}

bool XmlNode::_getValue(QString &value )
{
	Q_ASSERT( !m_node.isNull() ); 

    value = QString();
	for (QDomNode child = m_node.firstChild();
		!child.isNull();
		child = child.nextSibling())
	{
		if (child.nodeType() == QDomNode::TextNode)
		{
            value = child.nodeValue().trimmed();
			return true;
		}
	}

	return false;
}

bool XmlNode::_setValue(QString value )
{
	Q_ASSERT( !m_node.isNull() ); 

	for (QDomNode child = m_node.firstChild();
		!child.isNull();
		child = child.nextSibling())
	{
		if (child.nodeType() == QDomNode::TextNode)
		{
            child.setNodeValue(value);
			return true;
		}
	}

	// create text node if not exist
	QDomDocument doc = m_node.ownerDocument();
	Q_ASSERT(!doc.isNull());

    QDomNode childNode = doc.createTextNode(value);
	Q_ASSERT(!childNode.isNull());

	m_node.insertBefore(childNode,QDomNode());

	return true;
}

QString XmlNode::getName( void )
{
	Q_ASSERT( !m_node.isNull() ); 

	QString strRet = m_node.nodeName();

	return strRet; 
}

void XmlNode::getAttributes(QStringList &names )
{
	Q_ASSERT( !m_node.isNull() ); 

	QDomNamedNodeMap nodemap = m_node.attributes();

    names.clear();
	for (int i = 0;i < nodemap.count();i ++)
	{
        names.append(nodemap.item(i).nodeName());
	}
}

QString XmlNode::getAttribute(QString name, QString defaultValue /*= ""*/ )
{
	Q_ASSERT( !m_node.isNull() ); 

	QDomNamedNodeMap nodemap = m_node.attributes();

    QDomNode node = nodemap.namedItem(name);


	QString strValue; 
	if( node.isNull() ) 
	{ 
        strValue = defaultValue;
        setAttribute( name, strValue);
	} 
	else 
	{ 
		strValue = node.nodeValue();
	} 

	return strValue; 
}

bool XmlNode::setAttribute(QString name, QString value )
{
	Q_ASSERT( !m_node.isNull() ); 

	QDomElement element = m_node.toElement();
    element.setAttribute(name,value);

	return true; 
}

bool XmlNode::getAttribute(QString name, bool defaultValue )
{
    QString strValue = getAttribute(name);

    return _stringToBool(strValue,defaultValue);
}

bool XmlNode::setAttribute(QString name, bool value )
{
    return setAttribute(name,_boolToString(value));
}

int XmlNode::getAttribute(QString name, int defaultValue )
{
    QString strValue = getAttribute(name);

	bool bOk;
	int nRet = strValue.toInt(&bOk);
	
    return bOk ? nRet : defaultValue;
}

bool XmlNode::setAttribute(QString name, int value )
{
	QString strValue; 

    strValue.sprintf("%d",value);

    return setAttribute(name,strValue);
}

 QColor XmlNode::getAttribute(QString name, QColor defaultValue )
 {
    int nVal = getAttribute(name,int(-1));
 
 	if (nVal == -1)
 	{
        return defaultValue;
 	}
 	
 	return QColor(nVal & 255, nVal >> 8 & 255, nVal >> 16 & 255);
 }
 bool XmlNode::setAttribute(QString name, QColor value )
 {
    int nVal = (((uint)value.blue()<< 16) | (ushort)(((ushort)value.green()<< 8) | value.red()));
 
    return setAttribute(name,nVal);
 }
 
 QFont XmlNode::getAttribute(QString name, QFont defaultValue )
 {
 	QFont fontRet;
    if(!fontRet.fromString(getAttribute(name)))
 	{
        return defaultValue;
 	}
 
 	return fontRet;
 }
 
 bool XmlNode::setAttribute(QString name, QFont value )
 {
    return setAttribute(name,value.toString());
 }

bool XmlNode::delAttribute(QString name )
{
	Q_ASSERT( !m_node.isNull() );

	QDomNamedNodeMap nodemap = m_node.attributes();

    nodemap.removeNamedItem(name);

	return true; 
}

bool XmlNode::hasChildren( void )
{
	Q_ASSERT( !m_node.isNull() );

    bool bHasChildren = false;

	QDomNode node;
	QDomNodeList nodelist = m_node.childNodes();

    for (int i = 0; i < nodelist.length(); i++)
	{
		node = nodelist.item(i);

		if(node.nodeType() == QDomNode::ElementNode)
		{
			bHasChildren = true;
			break;
		}
	}

	return bHasChildren; 
}

bool XmlNode::remove( void )
{
	Q_ASSERT( !m_node.isNull() );

	QDomNode node = m_node.parentNode();

	node.removeChild(m_node);

    return true;
}

bool XmlNode::removeChildren( void )
{
	Q_ASSERT( !m_node.isNull() );

	QDomNode node;
	QDomNodeList nodelist = m_node.childNodes();

	for (int i = nodelist.length() - 1; i >= 0; i--)
	{
		node = nodelist.item(i);

		if(node.nodeType() == QDomNode::ElementNode)
		{
			m_node.removeChild(node);
		}
	}

	return true;
}

XmlNodesPtr XmlNode::getChildren()
{
	Q_ASSERT( !m_node.isNull() );

	QDomNodeList nodelist = m_node.childNodes();

    XmlNodesPtr pNodes(new XmlNodes(nodelist));

	return pNodes; 
}

QString XmlNode::getString(QString defaultValue /*= ""*/ )
{
	QString strValue; 
	_getValue(strValue); 

	if( strValue.isEmpty() && 
        !defaultValue.isEmpty() )
	{ 
        strValue = defaultValue;
		_setValue(strValue); 
	} 

	return strValue; 
}

bool XmlNode::getBool(bool defaultValue /*= false */ )
{
	QString strValue; 
	_getValue(strValue); 

    return _stringToBool(strValue,defaultValue);
}

int XmlNode::getInt(int defaultValue /*= 0 */ )
{
	QString strValue; 
	_getValue(strValue); 

	if(strValue.isEmpty())
	{ 
        setInt(defaultValue);
	} 

	return strValue.toInt();
}

double XmlNode::getFloat(double defaultValue /*= 0.0f */ )
{
	QString strValue; 
	_getValue(strValue); 

	if(strValue.isEmpty()) 
	{ 
        setFloat(defaultValue);
	} 

	return strValue.toDouble();
}

bool XmlNode::setString(QString value )
{
    return _setValue(value);
}

bool XmlNode::setBool(bool value )
{ 
    return _setValue(_boolToString(value));
}

bool XmlNode::setInt(int value )
{
	QString strValue; 

    strValue.sprintf("%d",value);
	return _setValue(strValue); 
}

bool XmlNode::setFloat(double value )
{
	QString strValue; 

    strValue.sprintf("%f",value);
	return _setValue(strValue); 
}

bool XmlNode::_stringToBool(QString value, bool defaultValue )
{
    if((value.toLower() == "true") || (value == "1"))
	{ 
		return true; 
	} 
    else if((value.toLower() == "false") || (value == "0"))
	{ 
		return false; 
	} 
	else
	{
        return defaultValue;
	}
}

QString XmlNode::_boolToString(bool value )
{
    return value ? "true" : "false";
}
