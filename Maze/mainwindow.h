#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gviewzoom.h"
#include <QtWidgets>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setBar(double value);
    void showBar(bool val);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QPixmap map;

public slots:
    void solve();
};

#endif // MAINWINDOW_H
