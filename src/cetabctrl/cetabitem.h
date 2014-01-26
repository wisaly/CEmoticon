#ifndef CETABITEM_H
#define CETABITEM_H
#include "cepaintunit.h"

class CETabItem : public CEPaintUnit
{
public:
    CETabItem(CEPaintUnit *parent = 0,QRect rect = QRect());
    virtual ~CETabItem();

public:
    int		index;
    QString	content;
    QString note;
    int		*itemPadding;
    // Methods:
public:
    void draw(QPainter *painter);
    void moveRect(QRect rect);
    // hit test
    CEPaintUnit *hitTest(QPoint point,MouseEvent event = NOTHING);

    QRect itemRect();
};

#endif // CETABITEM_H
