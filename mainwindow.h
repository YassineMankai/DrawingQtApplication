#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QToolBar>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>


#include "colorindicator.h"
#include "drawingarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    DrawingAreaWidget * drawingArea;
    ColorIndicator * colorIndicator;
    QSpinBox *thicknessIndicator;
    QRadioButton * solidL;
    QRadioButton * dashL;
    QRadioButton * dotL;
    QRadioButton * dashDotL;
    QRadioButton * lineS;
    QRadioButton * rectangeS;
    QRadioButton * ellipseS;

public slots:
    void quitApp();
    void changeParam(QColor const &color, int const _thickness, Qt::PenStyle _style, shape_type const _type);
};

#endif // MAINWINDOW_H

/*
 * made by : yassine mankai
 * yassine.mankai@telecom-paris.fr
 * thank you for using this app
*/
