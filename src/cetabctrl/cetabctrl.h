#ifndef CETABCTRL_H
#define CETABCTRL_H

#include "cetabpage.h"

#include <QWidget>


class CETabCtrl : public QWidget,public CEPaintUnit
{
    Q_OBJECT

public:
    explicit CETabCtrl(QWidget *parent = 0);
    ~CETabCtrl();

private:
    // ctrl attributes
    int		m_ctrlPadding;				// padding of this ctrl
    // page attributes
    int		m_pageCount;				// pages count
    int		m_headerHeight;		    	// page header height
    int		m_headerHorzMargin;		    // page header margin on horizontal
    int		m_headerTopMargin;			// page header margin on top
    int		m_headerActiveHorzMargin;	// active page header margin on horizontal
    int		m_headerActiveTopMargin;	// active page header margin on top
    int		m_pagePadding;				// padding of page
    QString	m_fontName;			    	// font name
    int		m_fontSize;		    		// point size * 10
    QFont   m_font;                     // font object
    int		m_columnCount;				// count of column
    int		m_rowCount;		    		// count of row
    int		m_itemPadding;				// padding of items

    QList<QColor> m_pageBackgroundColors;	// background color queue

    CETabPage *m_activePage;			// page which is actived
    bool    m_isCaptured;				// is mouse captured


    //Methods:
public:
    CETabPage *appendPage(QString caption = QString());
    void removeAllPages();
    void activePage(CETabPage *page);
    void reloadSetting();
private:
    QRect pageRect();

public:
    void resizeEvent(QResizeEvent * event);
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // CETABCTRL_H
