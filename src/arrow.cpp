#include "arrow.h"

Arrow::Arrow(QGraphicsLineItem * line, QGraphicsPolygonItem * arrowHead, QColor color)
{
    this->line = line;
    this->arrowHead = arrowHead;
    this->color = color;
}

QGraphicsLineItem *Arrow::getLine()
{
    return this->line;
}

QGraphicsPolygonItem *Arrow::getArrowHead()
{
    return this->arrowHead;
}

QColor Arrow::getColor()
{
    return this->color;
}
