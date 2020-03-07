#include "state.h"
#include <stdlib.h>

typedef struct node{
    State state;
    struct node *parent;
    int action;
} Node;

Node* makeNode(State state, Node* parent, int action){
    Node* p = (Node*)malloc(sizeof(Node));
    p->state = state;
    p->parent = parent;
    p->action = action;
    return p;
}

