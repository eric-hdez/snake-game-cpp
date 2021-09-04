#ifndef __SNAKE_H__
#define __SNAKE_H__

#define NIL -1

class Snake {

public:

    // holds an x,y coordinate
    struct coordinate {
        int x, y;
    };

    // the body pieces of a Snake and apple are Nodes
    struct Node {
        //Rectangle image;
        coordinate position;
        Node *next, *prev;

        Node(int x, int y);
        void move(int x_pix, int y_pix);
    };

    Node *head, *tail;
    int length;

    Snake(int x, int y);

    ~Snake();

    void reset();

    void grow();

    void move(int x_pix, int y_pix);

    bool snakeEatApple(Node *apple);

    bool outOfBounds(int len, int wid);

    bool snakeEatSelf();
};

#endif
