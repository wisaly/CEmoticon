#ifndef CETABPAGE_H
#define CETABPAGE_H
#include "cetabitem.h"

class CETabPage : public CEPaintUnit
{
public:
    CETabPage(CEPaintUnit *parent = 0,QRect rect = QRect());
    virtual ~CETabPage();

    // Attributes:
public:
    int		index;						// index of tab
    QString	caption;					// caption text
    bool	isActive;					// is this page actived
    int		*headerHeight;              // tab header height
    int		*pageCount;                 // tab pages count
    int		*headerHorzMargin;          // page header margin on horizontal
    int		*headerTopMargin;			// page header margin on top
    int		*headerActiveHorzMargin;	// active page header margin on horizontal
    int		*headerActiveTopMargin;     // active page header margin on top
    int		*pagePadding;				// padding of page
    int		*columnCount;				// count of column
    int		*rowCount;                  // count of row
    int		*itemPadding;				// padding of items
private:
    int		m_itemCount;				// item count

    // Methods:
public:
    // draw page
    void draw(QPainter *painter);
    // hit test
    CEPaintUnit *hitTest(QPoint point,MouseEvent event = NOTHING);
    // move to new rect
    void moveRect(QRect newRect);
    // apend item
    CETabItem *appendItem(QString content,QString note);

    QRect itemRect(int index);

private:
    // get rect of page header
    QRect bodyRect();
    // get rect of page body
    QRect headerRect();
};

#endif // CETABPAGE_H
