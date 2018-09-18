#ifndef MAZE_H
#define MAZE_H
#include "mazenode.h"
#include <QtWidgets>
#include "mainwindow.h"
class maze
{
public:
    maze(MainWindow *parent, QPixmap* pix);
    QImage solve();
    QImage map(mazenode* start, mazenode* finish);
    mazenode* above(int, int);
    void dijkstra(mazenode* start, mazenode* finish, long unsigned int nodes);
    mazenode* follow(mazenode*, int);

private:
    mazenode* root;
    mazenode* end;
    QImage img;
    QColor black;
    QColor white;
    mazenode*** tree;
    MainWindow* container;
};

#endif // MAZE_H
