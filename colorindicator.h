#ifndef COLORINDICATOR_H
#define COLORINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QColorDialog>


class ColorIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit ColorIndicator(QWidget *parent = nullptr);
    void setBackground(QColor const &color);

protected:
    void mousePressEvent(QMouseEvent *e) override;

signals:
    void colorChanged(QColor color);
};

#endif // COLORINDICATOR_H



/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/
