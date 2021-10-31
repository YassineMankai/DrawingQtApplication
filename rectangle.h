#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(){type = rectangle;};
    Rectangle(float x1, float y1, float x2, float y2):Shape(x1, y1, x2, y2){type = rectangle;};
    Rectangle(QTextStream  &inStream):Shape(inStream){};


    QPainterPath * preparePath() override;
};

#endif // RECTANGLE_H

/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/

