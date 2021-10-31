#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainterPath>
#include <QWidget>
#include <QColor>
#include <QPointF>
#include <QDebug>

enum shape_type { line, rectangle, ellipse};

class Shape
{
protected:
    QPointF *startingPoint = nullptr;
    QPointF *endingPoint = nullptr;
    QPainterPath *path = nullptr; // path to be added to the painter

    QColor color = Qt::black;
    int thickness = 1;
    Qt::PenStyle style = Qt::SolidLine;
    shape_type type = line;

public:
    Shape();
    Shape(float x1, float y1, float x2, float y2);
    Shape(QTextStream  &inStream);

    virtual ~Shape();

    void setColor(const QColor &value);
    void setThickness(int value);
    void setStyle(const Qt::PenStyle &value);

    void setStartingPoint(float x, float y);
    void setEndingPoint(float x, float y);
    void addDelta(const QPointF &delta);

    virtual bool contains(const QPointF &point) const;

    virtual QPainterPath * preparePath()=0;  // according to the shape type, set path to the proper value and return the path pointer

    QColor getColor() const {return color;};
    int getThickness() const {return thickness;};
    Qt::PenStyle getStyle() const {return style;};
    float getX_start() const {return startingPoint->x();};
    float getY_start() const {return startingPoint->y();};
    float getX_end()   const {return endingPoint->x();};
    float getY_end()   const {return endingPoint->y();};

    virtual QString toText() const;

    shape_type getType() const;
};

#endif // SHAPE_H

/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/

