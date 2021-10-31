#include "rectangle.h"

QPainterPath *Rectangle::preparePath()
{
    path->clear();
    qreal x = startingPoint->x();
    qreal y = startingPoint->y();
    qreal width = endingPoint->x() - startingPoint->x();
    qreal height = endingPoint->y() - startingPoint->y();
    path->addRect(x,y,width,height);

    return path;
}
