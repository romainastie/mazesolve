#ifndef MAZENODE_H
#define MAZENODE_H


class mazenode
{
public:
    mazenode(int yC, int xC, mazenode* leftN = nullptr, mazenode* topN = nullptr);

    void setNR(mazenode* node);
    void setNT(mazenode* node);
    void setNL(mazenode* node);
    void setNB(mazenode* node);
    int getD();
    void setD(int dist);
    mazenode* via();
    void setVia(mazenode* node);


    mazenode* getNR();
    mazenode* getNT();
    mazenode* getNL();
    mazenode* getNB();
    bool visited();
    void setVisited(bool TF);
    bool complete();
    mazenode* consider(int i);

    int getX();
    int getY();


private:

    mazenode* right;
    mazenode* left;
    mazenode* top;
    mazenode* bottom;
    mazenode* shortest;
    unsigned long int distance;
    bool visit;
    int x;
    int y;

};

#endif // MAZENODE_H
