#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(){type = ellipse;};
    Ellipse(float x1, float y1, float x2, float y2):Shape(x1, y1, x2, y2){type = ellipse;};
    Ellipse(QTextStream  &inStream):Shape(inStream){};

    QPainterPath * preparePath() override;
};

#endif // ELLIPSE_H

/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/
