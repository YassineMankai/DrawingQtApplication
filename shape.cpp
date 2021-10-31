#include "shape.h"

shape_type Shape::getType() const
{
    return type;
}

Shape::Shape()
{

}


Shape::Shape(float x1, float y1, float x2, float y2)
{
    startingPoint = new QPointF(x1,y1);
    endingPoint = new QPointF(x2,y2);
    path = new QPainterPath();

}

Shape::Shape(QTextStream  &inStream)
{
    path = new QPainterPath();

    int type_int;

    inStream >> type_int;
    type = shape_type(type_int);

    float xStart,yStart,xEnd,yEnd;
    inStream >> xStart >> yStart;
    inStream >> xEnd >> yEnd;
    startingPoint = new QPointF(xStart, yStart);
    endingPoint = new QPointF(xEnd, yEnd);

    QString colorString;
    inStream >> colorString;
    color = QColor(colorString);

    inStream >> thickness;

    int style_int;
    inStream >> style_int;
    style =  Qt::PenStyle(style_int);
}

Shape::~Shape()
{
    delete path;
    delete startingPoint;
    delete endingPoint;
}


void Shape::setStartingPoint(float x, float y)
{
    startingPoint->setX(x);
    startingPoint->setY(y);
}

void Shape::setEndingPoint(float x, float y)
{
    endingPoint->setX(x);
    endingPoint->setY(y);
}

void Shape::addDelta(const QPointF &delta)
{
    *startingPoint += delta;
    *endingPoint += delta;
}

bool Shape::contains(const QPointF &point) const
{
    if (!path) {qDebug() << "error"; return false;}
    else {
        QPointF topLeft = point - QPointF(15,15);
        QPointF bottomRight = point + QPointF(15,15);
        QRectF cursorRect(topLeft, bottomRight);
        return path->intersects(cursorRect);
    };
}

QString Shape::toText() const
{
    QString res("");

    QTextStream  outStream(&res);

    outStream << type << Qt::endl;
    outStream << type << Qt::endl;
    outStream << getX_start() << ' ' << getY_start() << Qt::endl;
    outStream << getX_end() << ' ' << getY_end() << Qt::endl;
    outStream << getColor().name() << Qt::endl;
    outStream << thickness << Qt::endl;
    outStream << getStyle() << Qt::endl;

    return res;
}

void Shape::setStyle(const Qt::PenStyle &value)
{
    style = value;
}


void Shape::setColor(const QColor &value)
{
    color = value;
}

void Shape::setThickness(int value)
{
    thickness = value;
}

