#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QMouseEvent>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <qpalette.h>
#include <QAbstractButton>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>


#include "shape.h"
#include "ellipse.h"
#include "line.h"
#include "rectangle.h"

enum state {drawing, editing};

class DrawingAreaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingAreaWidget(QWidget *parent = nullptr);
    ~DrawingAreaWidget();

private:
    QList<Shape *> shapes;                      // a list of all painted shapes (exculding the selected one : currentShape)
    state currentState = drawing;               // the current activity of the user
    bool isDrawing = false;                     // is true when a shaped is being painted
    bool isMoving = false;                      // is true when a shaped is being moved
    bool isEditing = false;                     // is true when a shaped is being edited
    QPointF lastClicked;                        // store the coordinations of the last click
    Shape * currentShape = nullptr;             // if a shape is being painted or is selected, this attribute points to that shape
    int currentThickness = 1;                   // the shapes' thickness currently selected by the user
    QColor currentColor = Qt::black;            // the shapes' color currently selected by the user
    Qt::PenStyle currentStyle = Qt::SolidLine;  // the shapes' line style currently selected by the user
    shape_type currentShapeType = line;

    void proceedOpen();


protected:
    // Mouse event handlers : according the currentState, a proper handling is executed
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    // paintEvent
    void paintEvent(QPaintEvent *e) override;  // paints currentShape if currentShape is not null and paints all previous painted shapes

public slots:
    void changeState(QAbstractButton * modeButton);  // select draw mode or editing(moving, changing) mode
    void chooseStyle(QAbstractButton * styleButton);
    void chooseShape(QAbstractButton * shapeButton);
    void changeColor(QColor color);
    void changeThickness(int);

    void openFile();
    void saveFile();

signals:
    void paramChanged(QColor const &color, int const thickness, Qt::PenStyle style, shape_type const type);
};

#endif // DRAWINGAREA_H

/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/
