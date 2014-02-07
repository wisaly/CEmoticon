#include "cetabctrl.h"
#include "config/appconfig.h"
#include <QResizeEvent>

CETabCtrl::CETabCtrl(QWidget *parent) :
    QWidget(parent)
{
    m_ctrlPadding = AppConfig::inst()->popWindow.ctrlPadding;
    m_headerHeight = AppConfig::inst()->popWindow.pageHeader.headerHeight;
    m_headerHorzMargin = AppConfig::inst()->popWindow.pageHeader.headerHorzMargin;
    m_headerTopMargin = AppConfig::inst()->popWindow.pageHeader.headerTopMargin;
    m_headerActiveHorzMargin = AppConfig::inst()->popWindow.pageHeader.headerActiveHorzMargin;
    m_headerActiveTopMargin = AppConfig::inst()->popWindow.pageHeader.headerActiveTopMargin;
    m_pagePadding = AppConfig::inst()->popWindow.pageHeader.pagePadding;
    m_itemPadding = AppConfig::inst()->popWindow.pageItem.itemPadding;
    m_fontSize = AppConfig::inst()->popWindow.fontSize;
    m_fontName = AppConfig::inst()->popWindow.fontName;

    m_font = QFont(m_fontName,m_fontSize);

    reloadSetting();


    m_pageCount = 0;
    m_isCaptured = false;
    m_activePage = 0;
}

CETabCtrl::~CETabCtrl()
{
}

CETabPage *CETabCtrl::appendPage(QString caption)
{
    QRect pageRect = this->pageRect();

    CETabPage *page = new CETabPage(this,pageRect);
    page->index = m_pageCount++;

    page->pageCount = &m_pageCount;
    page->headerHeight = &m_headerHeight;
    page->headerHorzMargin = &m_headerHorzMargin;
    page->headerTopMargin = &m_headerTopMargin;
    page->headerActiveHorzMargin = &m_headerActiveHorzMargin;
    page->headerActiveTopMargin = &m_headerActiveTopMargin;
    page->pagePadding = &m_pagePadding;
    page->columnCount = &m_columnCount;
    page->rowCount = &m_rowCount;
    page->itemPadding = &m_itemPadding;
    page->caption = caption;

    page->backgroundColor = m_pageBackgroundColors.takeFirst();
    m_pageBackgroundColors.append(page->backgroundColor);

    if (m_activePage == 0)
    {
        m_activePage = page;
        page->isActive = true;
    }

    repaint();

    return page;
}

void CETabCtrl::removeAllPages()
{
    this->removeChildren();
    reloadSetting();
    m_pageCount = 0;
    m_activePage = 0;
}

void CETabCtrl::activePage(CETabPage *page)
{
    if (!page->isActive)
    {
        m_activePage->isActive = false;
        m_activePage = page;
        m_activePage->isActive = true;
        repaint();
    }
}

void CETabCtrl::reloadSetting()
{
    m_columnCount = AppConfig::inst()->popWindow.pageItem.columnCount;
    m_rowCount = AppConfig::inst()->popWindow.pageItem.rowCount;

    m_pageBackgroundColors.clear();

    for (int i = 0;i < AppConfig::inst()->popWindow.pages.colors.count();i++)
    {
        m_pageBackgroundColors.append(AppConfig::inst()->popWindow.pages.colors[i]);
    }
}

QRect CETabCtrl::pageRect()
{
    return m_unitRect.adjusted(m_ctrlPadding,m_ctrlPadding,m_ctrlPadding,m_ctrlPadding);
}

void CETabCtrl::resizeEvent(QResizeEvent *event)
{
    m_unitRect.setRect(0,0,event->size().width(),event->size().height());

    // update children rect
    moveRect(pageRect());
}

void CETabCtrl::paintEvent(QPaintEvent *event)
{
    // double cache
    QPixmap cache(event->rect().size());
    QPainter painter(&cache);
    painter.translate(-event->rect().x(),-event->rect().y());

    painter.fillRect(m_unitRect,backgroundColor);

    painter.setFont(m_font);
    painter.setBackgroundMode(Qt::TransparentMode);

    // draw content
    draw(&painter);

    painter.end();

    // draw to screen
    QPainter realPainter(this);
    realPainter.drawPixmap(0,0,cache);
}

void CETabCtrl::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void CETabCtrl::mouseReleaseEvent(QMouseEvent *event)
{
    CEPaintUnit *hit = hitTest(event->pos(),LBTNUP);
    if (hit != 0)
    {
        CETabPage *page = dynamic_cast<CETabPage*>(hit);
        if (page != 0)
        {
            activePage(page);
        }
        CETabItem *item = dynamic_cast<CETabItem*>(hit);
        if (item != 0)
        {
            if (CEPaintUnit::parent() != 0)
            {
                //GetParent()->SendMessage(MSG_HITITEM,(WPARAM)(LPCTSTR)pItem->strContent,0);
                emit hitItem(item->content,item->note);
            }
        }
    }
}
