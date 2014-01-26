#include "cetabctrl.h"

#include <config/appconfig.h>

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
//    m_columnCount = AppConfig::inst()->PopWindow.PageItem.ColumnCount;
//    m_rowCount = AppConfig::inst()->PopWindow.PageItem.RowCount;

//    m_lstPageBackgrounds.RemoveAll();

//    for (POSITION pos = CConfigManager::Inst()->PopWindow.Pages.Colors.GetHeadPosition();
//        pos != NULL;)
//    {
//        m_lstPageBackgrounds.AddTail(CConfigManager::Inst()->PopWindow.Pages.Colors.GetNext(pos));
//    }
}

QRect CETabCtrl::pageRect()
{

}

void CETabCtrl::resizeEvent(QResizeEvent *event)
{

}

void CETabCtrl::paintEvent(QPaintEvent *event)
{
    /*// double cache
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
    realPainter.drawPixmap(0,0,cache);*/
}

void CETabCtrl::mousePressEvent(QMouseEvent *event)
{

}

void CETabCtrl::mouseMoveEvent(QMouseEvent *event)
{

}

void CETabCtrl::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void CETabCtrl::mouseReleaseEvent(QMouseEvent *event)
{

}
