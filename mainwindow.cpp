#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // ##################################################
    // ###### handle widgets and internal layouts  ######
    // ##################################################

    //ui->setupUi(this);

    // add a menubar, a toolbar, a central widget and a drawing area in central widget
    this->setMinimumSize(1000,600);
    QMenuBar *menubar = this->menuBar( );
    QToolBar *toolbar = this->addToolBar(tr("&toolbar"));
    QWidget *cenWidget = new QWidget(this);
    setCentralWidget(cenWidget);

    drawingArea = new DrawingAreaWidget(cenWidget);

    // add a menu in menubar adn actions in menu
    QMenu * menu = menubar->addMenu( tr("&File") );

    QAction * open = menu->addAction(QIcon(":/icons/file.png"),tr("&Open"));
    QAction * save = menu->addAction(QIcon(":/icons/save.jpeg"),tr("&Save"));
    QAction * quit = menu->addAction(QIcon(":/icons/quit.jpeg"),tr("&Quit"));

    toolbar->addAction(open);
    toolbar->addAction(save);
    toolbar->addAction(quit);

    // add a color indicator/selector and a thickness indicator/selector
    colorIndicator = new ColorIndicator(cenWidget);

    thicknessIndicator = new QSpinBox(cenWidget);
    thicknessIndicator->setMinimum(1);
    thicknessIndicator->setMaximum(50);

    QVBoxLayout *indicatorLayout = new QVBoxLayout;
    indicatorLayout->addWidget(colorIndicator);
    indicatorLayout->addWidget(thicknessIndicator);
    indicatorLayout->setAlignment(Qt::Alignment(Qt::AlignHCenter));

    QGroupBox *indicatorGroupWidget = new QGroupBox(tr("Select thickness/color :"));
    indicatorGroupWidget->setLayout(indicatorLayout);

    // add mode selector
    QRadioButton * drawingMode = new QRadioButton(tr("&drawing"), cenWidget);
    drawingMode->setChecked(true);
    QRadioButton * editingMode = new QRadioButton(tr("&editing"), cenWidget);

    QButtonGroup *modeGroupButton = new QButtonGroup(this);
    modeGroupButton->addButton(drawingMode);
    modeGroupButton->addButton(editingMode);

    QVBoxLayout *modeLayout = new QVBoxLayout;
    modeLayout->addWidget(drawingMode);
    modeLayout->addWidget(editingMode);

    QGroupBox *modeGroupWidget = new QGroupBox(tr("Select the mode :"));
    modeGroupWidget->setLayout(modeLayout);

    // add a select line type widget
    solidL = new QRadioButton(tr("&solid"), cenWidget);
    solidL->setChecked(true);
    dashL = new QRadioButton(tr("&dash"), cenWidget);
    dotL = new QRadioButton(tr("&dot"), cenWidget);
    dashDotL = new QRadioButton(tr("&dash dot"), cenWidget);

    QButtonGroup * styleGroupButton = new QButtonGroup(this);
    styleGroupButton->addButton(solidL);
    styleGroupButton->addButton(dashL);
    styleGroupButton->addButton(dotL);
    styleGroupButton->addButton(dashDotL);

    QVBoxLayout *lineStyleSetterLayout = new QVBoxLayout;
    lineStyleSetterLayout->addWidget(solidL);
    lineStyleSetterLayout->addWidget(dashL);
    lineStyleSetterLayout->addWidget(dotL);
    lineStyleSetterLayout->addWidget(dashDotL);

    QGroupBox *styleGroupWidget = new QGroupBox(tr("Select the line type :"));
    styleGroupWidget->setLayout(lineStyleSetterLayout);

    // add a select shape type widget
    lineS = new QRadioButton("&line", cenWidget);
    lineS->setChecked(true);
    rectangeS = new QRadioButton(tr("&rectangle"), cenWidget);
    ellipseS = new QRadioButton(tr("&ellipse"), cenWidget);

    QButtonGroup * shapeGroupButton = new QButtonGroup(this);
    QGroupBox *shapeGroupWidget = new QGroupBox(tr("Select the shape type :"));

    shapeGroupButton->addButton(lineS);
    shapeGroupButton->addButton(rectangeS);
    shapeGroupButton->addButton(ellipseS);

    QVBoxLayout *shapeTypeSetterLayout = new QVBoxLayout;
    shapeTypeSetterLayout->addWidget(lineS);
    shapeTypeSetterLayout->addWidget(rectangeS);
    shapeTypeSetterLayout->addWidget(ellipseS);

    shapeGroupWidget->setLayout(shapeTypeSetterLayout);

    // #############################
    // ###### end of widget handling
    // #############################


    // ######################################
    // ###### handle external layouts  ######
    // ######################################

    QHBoxLayout *mainLayout = new QHBoxLayout; // for drawing area
    QVBoxLayout *rightLayout = new QVBoxLayout; // for attribute setters

    // group shape selector, style selector, color indicator and thickness indicator in a group box
    QGroupBox *graphicalAttributesSetters = new QGroupBox(tr("Parameters"));
    rightLayout->addWidget(modeGroupWidget);
    rightLayout->addWidget(indicatorGroupWidget);
    rightLayout->addWidget(styleGroupWidget);
    rightLayout->addWidget(shapeGroupWidget);
    graphicalAttributesSetters->setLayout(rightLayout);
    graphicalAttributesSetters->setMaximumWidth(200);


    mainLayout->addWidget(drawingArea);
    mainLayout->addWidget(graphicalAttributesSetters);
    cenWidget->setLayout(mainLayout);

    // #############################################
    // ###### end of external layout handling ######
    // #############################################

    // ##################################################
    // ###### handle slots and signals connections ######
    // ##################################################
    connect(drawingArea, SIGNAL(paramChanged(QColor const &, int const, Qt::PenStyle, shape_type const)),
            this, SLOT(changeParam(QColor const &, int const, Qt::PenStyle, shape_type const)));

    connect(modeGroupButton, SIGNAL(buttonClicked(QAbstractButton*)),drawingArea, SLOT(changeState(QAbstractButton*)));
    connect(styleGroupButton, SIGNAL(buttonClicked(QAbstractButton*)),drawingArea, SLOT(chooseStyle(QAbstractButton*)));
    connect(shapeGroupButton, SIGNAL(buttonClicked(QAbstractButton*)),drawingArea, SLOT(chooseShape(QAbstractButton*)));


    connect(colorIndicator, SIGNAL(colorChanged(QColor)),drawingArea, SLOT(changeColor(QColor)));
    connect(thicknessIndicator, SIGNAL(valueChanged(int)),drawingArea, SLOT(changeThickness(int)));

    connect(open, SIGNAL(triggered()), drawingArea, SLOT(openFile()));
    connect(save, SIGNAL(triggered()), drawingArea, SLOT(saveFile()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApp()));

    // ###############################################
    // ###### end of slots and signals handling ######
    // ###############################################
}



void MainWindow::quitApp(){
    QMessageBox msgBox;
    msgBox.setText("You will loose the current session if not saved.\n Click no and select save menu item if you want to save your session. \nDo you still want to proceed the quit operation!!!");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        QApplication::quit();
        break;
    case QMessageBox::No:
        // Don't Save was clicked
        break;
    default:
        // should never be reached
        break;
    }
}

void MainWindow::changeParam(QColor const &color, int const _thickness, Qt::PenStyle _style, shape_type const _type)
{
    colorIndicator->setBackground(color);

    thicknessIndicator->setValue(_thickness);

    if(_style == Qt::SolidLine) {
        solidL->setChecked(true);
    }
    else if(_style == Qt::DashLine) {
        dashL->setChecked(true);
    }
    else if(_style == Qt::DotLine) {
        dotL->setChecked(true);
    }
    else if(_style == Qt::DashDotDotLine) {
        dashDotL->setChecked(true);
    }

    switch(_type) {
    case line:
        lineS->setChecked(true);
        break;
    case rectangle:
        rectangeS->setChecked(true);
        break;
    case ellipse:
        ellipseS->setChecked(true);
        break;
    default:
        qDebug() << "error";
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    MainWindow::quitApp();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete drawingArea;
    delete colorIndicator;
    delete thicknessIndicator;
    delete solidL;
    delete dashL;
    delete dotL;
    delete dashDotL;
    delete lineS;
    delete rectangeS;
    delete ellipseS;
}

