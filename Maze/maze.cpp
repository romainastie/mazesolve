#include "maze.h"
#include <iostream>

maze::maze(MainWindow* parent, QPixmap* pix)
{
    container = parent;
    black = QColor(0,0,0);
    white = QColor(255,255,255);
    img = pix->toImage();
    // Create 2D array of pointers:
    tree = new mazenode** [img.height()];
    for (int i = 0; i < img.height(); ++i)
    {
        tree[i] = new mazenode* [img.width()];
    }

    // Null out the pointers contained in the array:
    for (int i = 0; i < img.height(); ++i)
    {
        for (int j = 0; j < img.width(); ++j)
        {
            tree[i][j] = nullptr;
        }
    }


    root=nullptr;
    end = nullptr;


}

 QImage maze::solve()
{
    QImage img2 = img.copy();
    QColor teal(51,255,153);
    QColor red(255,0,0);
    unsigned long int count = 0;

    mazenode* prev = nullptr;
    for(int i= 0; i<img.height(); i++)
    {
        for(int j= 0; j<img.width(); j++)
        {
            if (img.pixel(j,i) == white.rgb())
            {
                if(i==0) //if white and first row...
                {
                    tree[i][j]=new mazenode(i,j);
                    img2.setPixelColor(j,i,Qt::cyan);
                    root=tree[i][j];
                    count++;
                    break;
                }

                if(i==img.height()-1)
                {
                    tree[i][j]=new mazenode(i,j,nullptr,above(i,j));
                    img2.setPixelColor(j,i,Qt::cyan);
                    end = tree[i][j];
                    count++;
                    break;
                }

                //if not first row, then we have cases:

                //wall path path
                if (img.pixel(j-1,i) == black.rgb() && img.pixel(j+1,i) == white.rgb())
                {
                    prev = nullptr; //reset row
                    tree[i][j] = new mazenode(i,j,prev,above(i,j));
                    img2.setPixelColor(j,i,teal);
                    prev=tree[i][j];
                    count++;
                }

                //path path wall
                if (img.pixel(j+1,i) == black.rgb() && img.pixel(j-1,i) == white.rgb())
                {
                    tree[i][j] = new mazenode(i,j,prev,above(i,j));
                    img2.setPixelColor(j,i,teal);
                    prev = tree[i][j];
                    count++;
                }

                //wall path wall is a vertical corridor, with exceptions.
                if (img.pixel(j+1,i) == black.rgb() && img.pixel(j-1,i) == black.rgb())
                {
                    if (img.pixel(j,i-1) == black.rgb() || img.pixel(j,i+1) == black.rgb())
                    {
                        prev = nullptr;
                        tree[i][j] = new mazenode(i,j,prev,above(i,j));
                        img2.setPixelColor(j,i,red);
                        count++;
                    }
                }

                //path path path cases are left.
                if (img.pixel(j+1,i) == white.rgb() && img.pixel(j-1,i) == white.rgb())
                {
                    //check for intersection types:
                    /*
                     * T
                     * Inverted T
                     * 4-way
                     */
                    //white above, black below.
                    if(img.pixel(j,i-1)==white.rgb() && img.pixel(j,i+1) == black.rgb())
                    {
                        tree[i][j] = new mazenode(i,j,prev,above(i,j));
                        img2.setPixelColor(j,i,teal);
                        prev=tree[i][j];
                        count++;
                    }
                    //black above, white below.
                    if(img.pixel(j,i-1)==black.rgb() && img.pixel(j,i+1) == white.rgb())
                    {
                        tree[i][j] = new mazenode(i,j,prev);
                        img2.setPixelColor(j,i,teal);
                        prev = tree[i][j];
                        count++;
                    }
                    //white above and below.
                    if(img.pixel(j,i-1)==white.rgb() && img.pixel(j,i+1) == white.rgb())
                    {
                        tree[i][j] = new mazenode(i,j,prev,above(i,j));
                        img2.setPixelColor(j,i,teal);
                        prev=tree[i][j];
                        count++;
                    }
                }

            }
        }
        prev=nullptr;
    }

    if (root == nullptr)
    {
        QMessageBox::critical(nullptr,"Critical Error!","No start node was found.");
    }

    if (end == nullptr)
    {
        QMessageBox::critical(nullptr,"Critical Error!","No end node was found.");
    }

    //node treee is create. now implement Dijkstra's.
    //start at node root.
    std::cerr<<count<<std::endl;
    //return img2;
    dijkstra(root, end, count);
    return map(root, end);
}
mazenode* maze::above(int i, int j)
{
    //find node above the current node.
    if (img.pixel(j,i-1) == black.rgb() || i<0)
    {
        return nullptr;
    }
    if(img.pixel(j,i-1) == white.rgb() && tree[i-1][j] == nullptr)
    {
        return above(i-1,j);
    }
    return tree[i-1][j];
}

void maze::dijkstra(mazenode* start, mazenode* finish, unsigned long nodes)
{
    mazenode* current;
    std::vector<mazenode*> vec;
    std::vector<mazenode*> complete;
    vec.push_back(start);
    while(vec.size()>0)
    {
        current = vec[0];
        vec.erase(vec.begin());
        if(current==finish)
        {
            //we have a solution!
            finish->setVia(current->getNT());
            finish->setD(current->getNT()->getD()+1);
            return;
        }
        if (current->getD()==0 && current!=start)
        {
            //find shortest path to here.
            int minDist = -1;
            for(int h=0; h<4; h++)
            {
                if(current->consider(h) != nullptr) //avoid nulls
                {
                    if(current->consider(h)->getD() != 0 || current->consider(h) == start) //avoid unvisited
                    {
                        if(minDist==-1)
                        {
                            minDist = current->consider(h)->getD();
                        }
                        if (current->consider(h)->getD()<minDist)
                        {
                            minDist = current->consider(h)->getD();
                        }
                    }
                }
            }
            int index = 0; // we have a mindist. Find node which corresponds.
            for(; index<4; index++)
            {
                if(current->consider(index) != nullptr)
                {
                    if (current->consider(index)->getD() == minDist)
                    {
                        break;
                    }
                }
            }
            current->setD(minDist+1);
            current->setVia(current->consider(index));
        }
        else
        {
            for(int j=0; j<4; j++)
            {
                if(current->consider(j) != nullptr) // if that neighbor is valid...
                    //(below) if neighbor is explored, and provides shorter path...
                    if(current->consider(j)->getD() < current->getD()-1 && current->consider(j)->getD() != 0)
                    {
                        current->setD(current->consider(j)->getD()+ 1);
                        current->setVia(current->consider(j));
                    }
            }

        }
        for(int i=0; i<4; i++)
        {
            if(current->consider(i) != nullptr && !current->consider(i)->complete() && std::find(vec.begin(),vec.end(),current->consider(i)) == vec.end())
            {
                vec.push_back(current->consider(i));
            }//look at current node.
            //use node->consider(i) to get neighbors in order, add to vector.
        }
        complete.push_back(current);
    }
    delete current;
    complete.clear();
    vec.clear();
}

QImage maze::map(mazenode* start, mazenode* finish)
{
    QColor blue(50,50,240);
    QColor red(240,50,50);
    QImage img3 = img.copy();
    mazenode* current = finish;
    for(; current!= start;)
    {
        img3.setPixelColor(current->getX(),current->getY(),blue);
        //moving left!
        if(current->via() == current->getNL())
        {
            int offset = 0;
            while(tree[current->getY()][current->getX()-offset] != current->via())
            {
                img3.setPixelColor(current->getX()-offset,current->getY(),blue);
                offset++;
            }

        }
        //moving right!

        if(current->via() == current->getNR())
        {
            int offset = 0;
            while(tree[current->getY()][current->getX()+offset] != current->via())
            {
                img3.setPixelColor(current->getX()+offset,current->getY(),blue);
                offset++;
            }

        }

        //moving up!
        if(current->via() == current->getNT())
        {
            int offset = 0;
            while(tree[current->getY()-offset][current->getX()] != current->via())
            {
                img3.setPixelColor(current->getX(),current->getY()-offset,blue);
                offset++;
            }

        }

        //moving down!
        if(current->via() == current->getNB())
        {
            int offset = 0;
            while(tree[current->getY()+offset][current->getX()] != current->via())
            {
                img3.setPixelColor(current->getX(),current->getY()+offset,blue);
                offset++;
            }

        }
        current = current->via();
    }
    img3.setPixelColor(start->getX(),start->getY(),red);
    img3.setPixelColor(finish->getX(),finish->getY(),red);
    container->showBar(false);
    return img3;

}

/*mazenode* maze::follow(mazenode* node, int direction= -1)
{
    //1,2,3,4 = N,E,S,W
switch(direction)
{
case 1:
    if()
                //if not, find where to go and follow.
    break;

case 2:

    break;

case 3:

    break;


case 4:
    break;

default:

break;
}
return node;
}
*/
