#include "mazenode.h"

mazenode::mazenode(int yC, int xC, mazenode* leftN, mazenode* topN)
{
    visit  = false;
    shortest = nullptr;
    distance = 0;
    top = nullptr;
    bottom = nullptr;
    right = nullptr;
    left = nullptr;
    x=xC;
    y=yC;
    setNL(leftN);
    if (leftN!=nullptr)
    {
        leftN->setNR(this);
    }
    setNT(topN);
    if(topN!=nullptr)
    {
        topN->setNB(this);
    }
}
int mazenode::getX()
{
    return x;
}
int mazenode::getY()
{
    return y;
}

mazenode* mazenode::getNB()
{
    return bottom;
}
mazenode* mazenode::getNL()
{
    return left;
}

mazenode* mazenode::getNR()
{
    return right;
}

mazenode* mazenode::getNT()
{
    return top;
}


void mazenode::setNB(mazenode* node)
{
    this->bottom=node;
}

void mazenode::setNR(mazenode* node)
{
    this->right=node;
}

void mazenode::setNL(mazenode* node)
{
    this->left=node;
}

void mazenode::setNT(mazenode* node)
{
    this->top=node;
}

void mazenode::setVia(mazenode *node)
{
    this->shortest=node;
}
void mazenode::setD(int dist)
{
    distance = dist;
}

int mazenode::getD()
{
    return distance;
}

mazenode* mazenode::via()
{
    return shortest;
}

void mazenode::setVisited(bool TF)
{
    visit = TF;
}

bool mazenode::visited()
{
    return visit;
}

bool mazenode::complete()
{
    if(top != nullptr)
    {
        if (top->getD() == 0)
        {
            return false;
        }
    }
    if(left != nullptr)
    {
        if (left->getD() == 0)
        {
            return false;
        }
    }
    if(right != nullptr)
    {
        if (right->getD() == 0)
        {
            return false;
        }
    }
    if(bottom != nullptr)
    {
        if (bottom->getD() == 0)
        {
            return false;
        }
    }
    if(distance == 0)
    {
        return false;
    }
    return true;
}

mazenode* mazenode::consider(int i)
{
    switch(i)
    {
    case 0:
        return top;
    case 1:
        return right;
    case 2:
        return bottom;
    case 3:
        return left;
    }
    return nullptr;
}
