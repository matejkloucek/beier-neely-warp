#ifndef ARROW_H
#define ARROW_H
#include <QGraphicsLineItem>


class Arrow
{
private:
    QGraphicsLineItem * line;
    QGraphicsPolygonItem * arrowHead;
    QColor color;
public:
    Arrow(QGraphicsLineItem * line, QGraphicsPolygonItem * arrowHead, QColor color);
    QGraphicsLineItem * getLine();
    QGraphicsPolygonItem * getArrowHead();
    QColor getColor();
};

#endif // ARROW_H
