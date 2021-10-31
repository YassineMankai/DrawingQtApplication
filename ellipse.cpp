#include "ellipse.h"


QPainterPath *Ellipse::preparePath()
{
    path->clear();
    qreal x = startingPoint->x();
    qreal y = startingPoint->y();
    qreal width = endingPoint->x() - startingPoint->x();
    qreal height = endingPoint->y() - startingPoint->y();
    path->addEllipse(x,y,width,height);

    return path;
}
