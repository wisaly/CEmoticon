#include "cetabpage.h"

CETabPage::CETabPage(CEPaintUnit *parent, QRect rect)
    :CEPaintUnit(parent,rect),
      isActive(false),
      headerHeight(0),
      pageCount(0),
      headerHorzMargin(0),
      headerTopMargin(0),
      headerActiveHorzMargin(0),
      headerActiveTopMargin(0),
      pagePadding(0),
      columnCount(0),
      rowCount(0),
      m_itemCount(0)
{
}
CETabPage::~CETabPage()
{

}

void CETabPage::draw(QPainter *painter)
{
    // draw header
    QRect header = headerRect();

    painter->fillRect(header,backgroundColor);

    // draw header text
    painter->setPen(foregroundColor);
    painter->drawText(
                header,
                Qt::AlignCenter|Qt::AlignHCenter,
                caption);

    // draw page
    if (isActive)
    {
        QRect pageRect = bodyRect();

        painter->fillRect(pageRect,backgroundColor);

        // draw children
        CEPaintUnit::draw(painter);
    }
}

CEPaintUnit *CETabPage::hitTest(QPoint point, MouseEvent event)
{
    // test hit header
    QRect header = headerRect();
    if (header.contains(point))
    {
        return this;
    }
    else
    {
        if (isActive)
        {
            // test hit body
            QRect pageRect = bodyRect();
            if (pageRect.contains(point))
            {
                return CEPaintUnit::hitTest(point,event);
            }
        }

        return 0;
    }
}

void CETabPage::moveRect(QRect newRect)
{
    m_unitRect = newRect;

    CEPaintUnit *child = m_firstChild;
    while(child != 0)
    {
        CETabItem *item = dynamic_cast<CETabItem*>(child);
        Q_ASSERT(item != 0);
        item->moveRect(itemRect(item->index));

        child = child->nextSibling();
    }
}

CETabItem *CETabPage::appendItem(QString content, QString note)
{
    QRect rect = itemRect(m_itemCount);

    CETabItem *item = new CETabItem(this,rect);

    item->index = m_itemCount++;
    item->itemPadding = this->itemPadding;

    item->content = content;
    item->note = note;

    return item;
}

QRect CETabPage::itemRect(int index)
{
    QRect rect= bodyRect();
    rect.adjust(*pagePadding,*pagePadding,*pagePadding,*pagePadding);
    rect.setRect(
        rect.left() + index % *columnCount * rect.width() / * columnCount,
        rect.top() + index / *columnCount * rect.height() / * rowCount,
        rect.left() + (index % *columnCount + 1) * rect.width() / * columnCount,
        rect.top() + (index / *columnCount + 1) * rect.height() / * rowCount
        );
    return rect;
}

QRect CETabPage::bodyRect()
{
    QRect pageRect(
        0,
        *headerHeight,
        m_unitRect.width(),
        m_unitRect.height());

    calcPosition(pageRect);
    return pageRect;
}

QRect CETabPage::headerRect()
{
    QRect rect(
        index * m_unitRect.width() / *pageCount + (isActive ? *headerActiveHorzMargin : *headerHorzMargin),
        isActive ? *headerActiveTopMargin : *headerTopMargin,
        (index + 1) * m_unitRect.width() / *pageCount - (isActive ? *headerActiveHorzMargin : *headerHorzMargin),
        *headerHeight - (isActive ? 0 : *headerTopMargin));

    calcPosition(rect);
    return rect;
}
