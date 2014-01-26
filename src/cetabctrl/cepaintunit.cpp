#include "cepaintunit.h"

// Constructor
CEPaintUnit::CEPaintUnit(CEPaintUnit *parent, QRect rect)
    :visible(true),m_unitRect(rect),
      m_parent(parent),m_firstChild(0),m_nextSibling(0)
{
    // keep tree struct
    if (m_parent != 0)
    {
        if (m_parent->m_firstChild == 0)
        {
            // if parent has no child, be the first
            m_parent->m_firstChild = this;
        }
        else
        {
            // if parent have children, be the last
            CEPaintUnit *thisPrevious = m_parent->m_firstChild;
            while(thisPrevious->m_nextSibling != 0)
            {
                thisPrevious = thisPrevious->m_nextSibling;
            }
            thisPrevious->m_nextSibling = this;
        }
    }

    //
    backgroundColor = QColor(255,255,255);
    foregroundColor = QColor(0,0,0);
    hightlightColor = QColor(255,255,255);
    checkedColor = QColor(255,255,255);
    disabledColor = QColor(128,128,128);
}

// Destructor, free memory
CEPaintUnit::~CEPaintUnit()
{
    CEPaintUnit *child = m_firstChild;
    while(child != 0)
    {
        CEPaintUnit *needDelete = child;
        child = child->m_nextSibling;

        delete needDelete;
    }
}
void CEPaintUnit::draw(QPainter *painter)
{
    // Draw child
    if (this->visible)
    {
        CEPaintUnit *child = m_firstChild;
        while (child != 0)
        {
            child->draw(painter);

            child = child->m_nextSibling;
        }
    }
}

CEPaintUnit *CEPaintUnit::hitTest(QPoint point, CEPaintUnit::MouseEvent event)
{
    if (m_unitRect.contains(point) && this->visible)
    {
        CEPaintUnit *child = m_firstChild;
        while (child != 0)
        {
            CEPaintUnit *childHit = child->hitTest(point,event);
            if (childHit != 0)
            {
                return childHit;
            }
            child = child->m_nextSibling;
        }

        return this;
    }
    return 0;
}

void CEPaintUnit::moveRect(QRect newRect)
{
    CEPaintUnit *child = m_firstChild;
    while(child != 0)
    {
        child->moveRect(newRect);
        child = child->m_nextSibling;
    }
}

void CEPaintUnit::remove()
{
    if (m_parent != 0)
    {
        if (this == m_parent->firstChild())
        {
            // replace first child
            m_parent->m_firstChild = this->nextSibling();
        }
        else
        {
            // re-connect sibling link
            CEPaintUnit *prevSibling = m_parent->firstChild();
            while(prevSibling->nextSibling() != this)
            {
                Q_ASSERT(prevSibling != 0);
                prevSibling = prevSibling->nextSibling();
            }
            prevSibling->m_nextSibling = this->nextSibling();
        }
    }

    delete this;
}

void CEPaintUnit::removeChildren()
{
    for(CEPaintUnit *child = this->firstChild();child != 0;)
    {
        CEPaintUnit *needRemove = child;
        child = child->nextSibling();
        needRemove->remove();
    }
}

void CEPaintUnit::offset(int x, int y)
{
    m_unitRect.translate(x,y);
}

void CEPaintUnit::unitRect(QRect &rect)
{
    rect.setRect(0,0,m_unitRect.width(),m_unitRect.height());
}

QPoint &CEPaintUnit::calcPosition(QPoint &point)
{
    point += m_unitRect.topLeft();
    return point;
}

QRect &CEPaintUnit::calcPosition(QRect &rect)
{
    rect.translate(rect.topLeft());
    return rect;
}
