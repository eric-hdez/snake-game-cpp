#include "snake.h"

// Node Constructor and Functions --------------------------------------------------

// Constructor for a Node
//
Snake::Node::Node(int x, int y) {
    position = { x, y };
    next = prev = nullptr;
}

// moves a Node along a 2-D plane
//
void Snake::Node::move(int x_pix, int y_pix) {
    position.x += x_pix;
    position.y += y_pix;
}

// Snake Constructors and Functions ------------------------------------------------

// Constructor for a Snake Object
//
Snake::Snake(int x, int y) {
    head = new Node(x, y);
    tail = new Node(NIL, NIL);

    head->next = tail;
    tail->prev = head;
    length = 1;
}

// Destructor for a Snake Object
//
Snake::~Snake() {
    Snake::reset();
    delete head;
    delete tail;
    head = tail = nullptr;
}

// resets a Snake Object to head and tail only
//
void Snake::reset() {
    for (Node *curr = head->next; curr != tail;) {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }

    head->next = tail;
    tail->prev = head;
}

// grows the body of a Snake Object
//
void Snake::grow() {
    for (int k = 0; k < 4; k++) {
        Node *n = new Node(head->position.x, head->position.y);

        n->prev = tail->prev;
        n->next = tail;

        tail->prev->next = n;
        tail->prev = n;
        length++;
    } 
}

// moves a Snake Object along a 2-D plane
//
void Snake::move(int x_pix, int y_pix) {
    coordinate last = { head->position.x, head->position.y };
    head->move(x_pix, y_pix);

    for (Node *curr = head->next; curr != tail; curr = curr->next) {
        coordinate currs_last = { curr->position.x, curr->position.y };
        curr->position = last;
        last = currs_last;
    }
}

bool Snake::snakeEatApple(Node *apple) {
    if (head->position.x == apple->position.x && head->position.y == apple->position.y) {
        return true;
    }

    return false;
}

bool Snake::snakeEatSelf() {
    for (Node *curr = head->next; curr != tail; curr = curr->next) {
        if (head->position.x == curr->position.x && head->position.y == curr->position.y) {
            return true;
        }
    }

    return false;
}

bool Snake::outOfBounds(int len, int wid) {
    if (head->position.x >= len || head->position.x < 0) {
        return true;
    }
    if (head->position.y >= wid || head->position.y < 0) {
        return true;
    }

    return false;
}

