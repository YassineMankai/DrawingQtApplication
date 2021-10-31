#include "colorindicator.h"

ColorIndicator::ColorIndicator(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(50,50);
    setMinimumSize(40,40);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}

void ColorIndicator::setBackground(const QColor &color)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setAutoFillBackground(true);
    setPalette(pal);
}

void ColorIndicator::mousePressEvent(QMouseEvent *)
{
    QColor newColor = QColorDialog::getColor(Qt::white);

    setBackground(newColor);


    emit colorChanged(newColor);
}
