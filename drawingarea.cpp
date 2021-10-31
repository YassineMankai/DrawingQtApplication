#include "drawingarea.h"


DrawingAreaWidget::DrawingAreaWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(700,300);
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

DrawingAreaWidget::~DrawingAreaWidget()
{
    delete currentShape;
    QList<Shape *>::iterator i;
    for (i=shapes.begin();i!=shapes.end();++i)
    {
        delete (*i);
    }
}

/*
############################################################
###########start mouseEvent handling  description###########
############################################################
    when drawing: left click and drag to make a shape;
    when editing: left click and drag to move a shape;
                  right click to select a shape and change graphical attributes parameters to edit the shape;
*/

void DrawingAreaWidget::mousePressEvent(QMouseEvent *e)
{
    if (currentShape != nullptr && isEditing)  // reverse a previous select event
    {
        shapes.append(currentShape);
        currentShape = nullptr;
        isEditing = false;
    }

    QPointF cursor = e->pos();
    lastClicked = cursor;  // usefull for move event

    if (currentState == drawing)
    {
        // handling edge cases
        if (e->button() != Qt::LeftButton) {return;}  // drawing is only possible with left clicks
        isDrawing = true;

        switch(currentShapeType) {
        case line:
            currentShape = new Line(cursor.x(), cursor.y(), cursor.x(), cursor.y());
            break;
        case rectangle:
            currentShape = new Rectangle(cursor.x(), cursor.y(), cursor.x(), cursor.y());
            break;
        case ellipse:
            currentShape = new Ellipse(cursor.x(), cursor.y(), cursor.x(), cursor.y());
            break;
        default:
            qDebug() << "error";
        }

        currentShape->setColor(currentColor);
        currentShape->setThickness(currentThickness);
        currentShape->setStyle(currentStyle);
    }
    else  // currentState==editing : search if a shape is selected remove it from shapes list and set currentShape to it
    {
        bool change = false;

        int index = -1;
        for (index=shapes.size()-1; index>=0; index--)
        {
            if (shapes[index]->contains(cursor)) {
                currentShape = shapes[index];
                change = true;    // a shape was selected
                emit paramChanged(currentShape->getColor(), currentShape->getThickness(), currentShape->getStyle(), currentShape->getType());
                break;
            }
        }

        if (change) // remove the shape from list (currentShape is pointing to it)
        {
            shapes.removeAt(index);
        }
        else // no shape was selected : handle the case of a selected unedited shape
        {
            if (currentShape != nullptr)  // reverse a previous select event
            {
                shapes.append(currentShape);
                currentShape = nullptr;
                change = false;
            }
        }

        if (change)
        {
            isMoving = (e->button() == Qt::LeftButton);
            isEditing = (e->button() == Qt::RightButton);
        }

    }

    update();
}


void DrawingAreaWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPointF cursor = e->pos();

    if (currentState == drawing)
    {
        if (!isDrawing) {return;}
        currentShape->setEndingPoint(cursor.x(), cursor.y());
        update();
    }
    else  // currentState == editing : moving the selected shape
    {
        if (!isMoving) {return;}
        QPointF delta = cursor - lastClicked;
        lastClicked = cursor;
        currentShape->addDelta(delta);
    }

    update();
}


void DrawingAreaWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (currentState == drawing)
    {
        if (!isDrawing) {return;}  // only certain release events are important
        if (e->button() != Qt::LeftButton){return;}
        isDrawing = false;
        shapes.append(currentShape);
        currentShape = nullptr;
    }
    else //editing
    {
        if (isMoving)
        {
            if (e->button() != Qt::LeftButton){return;}
            isMoving = false;
            shapes.append(currentShape);
            currentShape = nullptr;
        }
        else if (isEditing)
        {

        }
    }
    update();

}

/*
############################################################
############end mouseEvent handling  description############
############################################################
*/


void DrawingAreaWidget::paintEvent(QPaintEvent * e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    QPen pen;

    if (currentShape != nullptr)  // paints the currentShape if not null
    {
        QPainterPath * path = currentShape->preparePath();

        pen.setColor(currentShape->getColor());
        pen.setWidth(currentShape->getThickness());
        pen.setStyle(currentShape->getStyle());

        painter.setPen(pen);

        painter.drawPath(*path);
    }


    // paint all previous shapes
    QList<Shape *>::iterator i;
    for (i=shapes.begin();i!=shapes.end();++i)
    {
        Shape * previousShape = *i;
        QPainterPath * path = previousShape->preparePath();


        pen.setColor(previousShape->getColor());
        pen.setWidth(previousShape->getThickness());
        pen.setStyle(previousShape->getStyle());

        painter.setPen(pen);

        painter.drawPath(*path);
    }
}



/*
###########################################################
############ start slot and signal declaration ############
###########################################################
*/
void DrawingAreaWidget::changeState(QAbstractButton *modeButton)
{
    QString styleName = modeButton->text();
    if(styleName == "&drawing") {
        currentState = drawing;
    }
    else if(styleName == "&editing") {
        currentState = editing;
    }
}

void DrawingAreaWidget::changeColor(QColor color)
{
    currentColor = color;
    if ( (currentState == editing) && (isEditing) && (currentShape) )
    {
        currentShape->setColor(currentColor);
        update();
    }
}

void DrawingAreaWidget::changeThickness(int value)
{
    currentThickness = value;
    if ( (currentState == editing) && (isEditing) && (currentShape) )
    {
        currentShape->setThickness(currentThickness);
        update();
    }
}

void DrawingAreaWidget::chooseStyle(QAbstractButton * styleButton)
{
    QString styleName = styleButton->text();
    if(styleName == "&solid") {
        currentStyle = Qt::SolidLine;
    }
    else if(styleName == "&dash") {
        currentStyle = Qt::DashLine;
    }
    else if(styleName == "&dot") {
        currentStyle = Qt::DotLine;
    }
    else if(styleName == "&dash dot") {
        currentStyle = Qt::DashDotDotLine;
    }
    if ( (currentState == editing) && (isEditing) && (currentShape) )
    {
        currentShape->setStyle(currentStyle);
        update();

    }
}

void DrawingAreaWidget::chooseShape(QAbstractButton *shapeButton)
{
    QString styleName = shapeButton->text();
    if(styleName == "&line") {
        currentShapeType = line;
    }
    else if(styleName == "&rectangle") {
        currentShapeType = rectangle;
    }
    else if(styleName == "&ellipse") {
        currentShapeType = ellipse;
    }
    if ( (currentState == editing) && (isEditing) && (currentShape) )
    {
        Shape *newShape = nullptr;
        if(styleName == "&line") {
            newShape = new Line(currentShape->getX_start(), currentShape->getY_start(), currentShape->getX_end(), currentShape->getY_end());
        }
        else if(styleName == "&rectangle") {
            newShape = new Rectangle(currentShape->getX_start(), currentShape->getY_start(), currentShape->getX_end(), currentShape->getY_end());
        }
        else if(styleName == "&ellipse") {
            newShape = new Ellipse(currentShape->getX_start(), currentShape->getY_start(), currentShape->getX_end(), currentShape->getY_end());
        }
        newShape->setColor(currentShape->getColor());
        newShape->setThickness(currentShape->getThickness());
        newShape->setStyle(currentShape->getStyle());

        delete currentShape;
        currentShape = newShape;
        update();
    }
}

void DrawingAreaWidget::openFile(){
    QMessageBox msgBox;
    msgBox.setText("You will loose the current session if not saved.\n Click no and select save menu item if you want to save your session. \nDo you still want to proceed the open operation!!!");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        proceedOpen();
        break;
    case QMessageBox::No:
        // Don't Save was clicked
        break;
    default:
        // should never be reached
        break;
    }
}

void DrawingAreaWidget::proceedOpen(){
    QString path = QDir::current().path();
    path += "/files";
    QString fileName=QFileDialog::getOpenFileName(this,tr("open text file"),path,tr("Text Files(*.txt)"));
    if (fileName.isEmpty()){return;}
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {

        delete currentShape;
        currentShape = nullptr;

        QList<Shape *>::iterator i;
        for (i=shapes.begin();i!=shapes.end();++i)
        {
            delete (*i);
        }
        shapes.clear();

        QTextStream in(&file);

        int nbShpes;
        in >> nbShpes;
        for (int shapeIndex=0; shapeIndex<nbShpes; shapeIndex++)
        {
            int typeInt;
            in >> typeInt;
            switch(shape_type(typeInt))
            {
            case line:
                shapes.append(new Line(in));
                break;
            case rectangle:
                shapes.append(new Rectangle(in));
                break;
            case ellipse:
                shapes.append(new Ellipse(in));
                break;
            default:
                qDebug() << "error";
            }
        }
    }
    update();
}

void DrawingAreaWidget::saveFile(){
    QString path = QDir::current().path();
    path += "/files";
    QString fileName=QFileDialog::getSaveFileName(this,tr("save text file"),path,tr("Text Files(*.txt)"));

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);

        out << shapes.size() << Qt::endl;

        QList<Shape *>::iterator i;

        for (i=shapes.begin();i!=shapes.end();++i)
        {
            out << (*i)->toText();
        }

    }

}
/*
###########################################################
############# end slot and signal declaration #############
###########################################################
*/
