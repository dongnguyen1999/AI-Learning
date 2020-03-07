#include "node.h"
#define MAX_LENGTH 99999

typedef struct {
    int front, rear;
    Node* data[MAX_LENGTH];
} List;


void makeNull(List* L){
    L->front = 0;
    L->rear = -1;
}

int empty(List L){
    return (L.rear < L.front);
}

void push(List* L, Node* node){
    L->data[++L->rear] = node;
}

Node* pop(List* L){
    return L->data[L->rear--];
}

Node* shift(List* L){
    return L->data[L->front++];
}

int findNode(List L, Node* node){
    int i;
    for(i = L.front; i <= L.rear; i++){
        if (equals(L.data[i]->state, node->state)) return 1;
    }
    return 0;
}

void printList(List L){
    int i;
    for (i = L.front; i <= L.rear; i++){
        printState(L.data[i]->state);
    }
}