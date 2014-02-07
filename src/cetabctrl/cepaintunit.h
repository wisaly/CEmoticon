#ifndef CEPAINTUNIT_H
#define CEPAINTUNIT_H

#include <QColor>
#include <QPainter>

class CEPaintUnit// : public QObject
{
public:
    explicit CEPaintUnit(CEPaintUnit *parent = 0,QRect rect = QRect());
    virtual ~CEPaintUnit();
    // Constant
    enum MouseEvent{NOTHING,LBTNDOWN,LBTNUP,LBTNMOVE,RBTNDOWN,RBTNUP,RBTNMOVE};

    // Attribute
public:
    bool			visible;	    	// is this unit visible
    QColor		    backgroundColor;	// background color
    QColor  		foregroundColor;	// foreground color
    QColor	    	hightlightColor;	// highlight color
    QColor		    checkedColor;		// checked color
    QColor	    	disabledColor;		// disabled color
protected:
    QRect			m_unitRect;		    // rect of this unit
    CEPaintUnit	    *m_parent;		    // parent unit
    CEPaintUnit	    *m_firstChild;	    // first child unit
    CEPaintUnit	    *m_nextSibling;     // next sibling unit

    // Methods:
public:
    // draw this unit
    virtual void draw(QPainter *painter);
    // hit test
    virtual CEPaintUnit *hitTest(QPoint point,MouseEvent event = NOTHING);
    // move unit to new rect
    virtual void moveRect(QRect newRect);
    // remove this unit
    void remove();
    // remove all children
    void removeChildren();
    // offset unit
    void offset(int x,int y);
    // get rect coordinate to unit
    void unitRect(QRect &rect);
    // get parent unit
    inline CEPaintUnit *parent(){ return m_parent; }
    // get first child unit
    inline CEPaintUnit *firstChild(){ return m_firstChild; }
    // get next sibling unit
    inline CEPaintUnit *nextSibling(){ return m_nextSibling; }

protected:
    // offset point to paint coordinate
    QPoint &calcPosition(QPoint &point);
    // offset rect to paint coordinate
    QRect &calcPosition(QRect &rect);
};

#endif // CEPAINTUNIT_H
