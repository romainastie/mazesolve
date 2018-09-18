#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
    ui->setupUi(this);
    ui->progressBar->hide();
    scene = new QGraphicsScene;
    map = QPixmap (QFileDialog::getOpenFileName(this,tr("Open Image"),"", tr("Image Files (*.png *.jpg *.bmp)")));

    if(map.isNull())
    {
        QMessageBox* box = new QMessageBox(QMessageBox::Critical,"Critical Error","Could not load image");
        box->show();
    }
    scene->addPixmap(map);
    Graphics_view_zoom* z = new Graphics_view_zoom(ui->graphicsView);
    z->set_modifiers(Qt::NoModifier);
    ui->graphicsView->setScene(scene);
    connect(ui->quitButton,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
    connect(ui->calcButton,SIGNAL(clicked(bool)),this,SLOT(solve()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::solve()
{
    ui->progressBar->show();
    ui->progressBar->setRange(0,0);
    ui->progressBar->setValue(0);
    maze m(this, &map);
    //QFuture<QImage> f1 = QtConcurrent::run(m, &maze::solve);
    //connect()
    map.convertFromImage(m.solve());
   scene->clear();
    scene->addPixmap(map);
    ui->progressBar->hide();
    //do stuff to the nodes here to solve the puzzle.
    return;
}

void MainWindow::setBar(double value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::showBar(bool val)
{
    if(val == true)
    {
        ui->progressBar->show();
    }
    else
    {
        ui->progressBar->hide();
    }
}
