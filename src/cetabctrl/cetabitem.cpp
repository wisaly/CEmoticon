#include "cetabitem.h"

CETabItem::CETabItem(CEPaintUnit *parent, QRect rect)
    :CEPaintUnit(parent,rect)
{

}

CETabItem::~CETabItem()
{

}

void CETabItem::draw(QPainter *painter)
{
    QRect rectItem = itemRect();
    // item rect
    painter->fillRect(rectItem,backgroundColor);

    // draw text
    painter->setPen(foregroundColor);
    painter->drawText(rectItem,
                      Qt::AlignCenter|Qt::AlignHCenter,
                      note.isEmpty() ? content : note);


}

void CETabItem::moveRect(QRect rect)
{
    m_unitRect = rect;
}

CEPaintUnit *CETabItem::hitTest(QPoint point, CEPaintUnit::MouseEvent event)
{
    Q_UNUSED(event);

    QRect rect = itemRect();

    if(!rect.contains(point))
    {
        return 0;
    }

    // in item
    return this;
}

QRect CETabItem::itemRect()
{
    return m_unitRect.adjusted(*itemPadding,*itemPadding,*itemPadding,*itemPadding);
}
