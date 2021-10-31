#include "line.h"

QPainterPath *Line::preparePath()
{
    path->clear();
    path->moveTo(*startingPoint);
    path->lineTo(*endingPoint);

    return path;
}
