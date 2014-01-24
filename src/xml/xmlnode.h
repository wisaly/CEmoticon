#ifndef XMLNODE_H
#define XMLNODE_H

#include <QDomNode>
#include <QColor>
#include <QFont>
#include <QSharedPointer>

class Xml;

class XmlNode;
//! 使用智能指针存储对象
typedef QSharedPointer<XmlNode>  XmlNodePtr;

class XmlNodes;
//! 使用智能指针存储对象
typedef QSharedPointer<XmlNodes>  XmlNodesPtr;

/*!
	@brief XML节点类

	注意操作时使用QXmlNodePtr来操作
*/
class XmlNode
{
    friend class Xml;
    friend class XmlNodes;
public:
    ~XmlNode(void);

protected:
    XmlNode(QDomNode node);
	QDomNode m_node;
    bool _getValue(QString &value);
    bool _setValue(QString value);
    bool _stringToBool(QString value,bool defaultValue);
    QString _boolToString(bool value);
public: 

	//! 构造函数
    XmlNode(void);
    XmlNode( XmlNode & refNode );

	//! 重载 = 号
    XmlNodePtr operator = ( XmlNodePtr pNode);
    XmlNode & operator = ( XmlNode & refNode);

	//! 获取结点名称
	QString getName(void); 

	//! 获取属性
    QString getAttribute( QString name, QString defaultValue = "");
	//! 设置属性
    bool setAttribute(QString name, QString value);
	//! 设置属性
    bool setAttribute(QString name, char *value)
    { return setAttribute(name,QString(value)); }

	//! 获取属性
    bool getAttribute(QString name,bool defaultValue);
	//! 设置属性
    bool setAttribute(QString name,bool value);

	//! 获取属性
    int getAttribute(QString name,int defaultValue);
	//! 设置属性
    bool setAttribute(QString name,int value);

	//! 获取属性
    QColor getAttribute(QString name,QColor defaultValue);
	//! 设置属性
    bool setAttribute(QString name,QColor value);

	//! 获取属性
    QFont getAttribute(QString name,QFont defaultValue);
	//! 设置属性
    bool setAttribute(QString name,QFont value);

	//! 删除属性
    bool delAttribute( QString name );

	//! 获取所有属性名列表
    void getAttributes(QStringList &names);
	
	//! 获取子节点
    XmlNodePtr getChild(QString name);
    //!
    XmlNodePtr getNextSibling(QString name);
    //!
    bool hasChild(QString name);
	//! 增加子节点
    XmlNodePtr appendChild(QString name);
	//! 获取所有子节点
    XmlNodesPtr getChildren();
	//! 是否有子节点
	bool hasChildren(void); 
	//! 删除所有子节点
	bool removeChildren(void); 



	//! 删除当前结点
	bool remove(void); 



	//! 取文本值
    QString getString( QString defaultValue = "");
	//! 取布尔值
    bool getBool( bool defaultValue = false );
	//! 取整数值
    int getInt( int defaultValue = 0 );
	//! 取浮点数值
    double getFloat( double defaultValue = 0.0f );



	//! 设置文本值
    bool setString( QString value );
	//! 设置布尔值
    bool setBool( bool value );
	//! 设置整数值
    bool setInt( int value );
	//! 设置浮点数值
    bool setFloat( double value );

	//! 节点是否为空
	bool isNull(void); 
};

#endif
