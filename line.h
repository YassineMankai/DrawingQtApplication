#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line(){type = line;};
    Line(float x1, float y1, float x2, float y2):Shape(x1, y1, x2, y2){type = line;};
    Line(QTextStream  &inStream):Shape(inStream){};

    QPainterPath * preparePath() override;

};

#endif // LINE_H

/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/

