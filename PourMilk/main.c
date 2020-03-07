#include "mylist.h"

void printResult(Node* node){
    List stack;
    makeNull(&stack);
    int i,j;
    Node* p = node;
    while (p != NULL){
        push(&stack, p);
        p = p->parent;
    }
    while(!empty(stack)){
        p = pop(&stack);
        if (p->action != -1) printf("%s\n", actions[p->action]);
        printState(p->state);
    }
}

void bfs(Node* root){
    List openList;
    List closedList;
    makeNull(&openList);
    makeNull(&closedList);
    push(&openList, root);
    while(!empty(openList)){
        Node* node = pop(&openList);
        push(&closedList, node);
        State currentState = node->state;
        if (checkGoal(currentState)){
            // printf(">>");
            printResult(node);
            break;
        }
        int opid;
        for (opid = 0; opid < NB_OPERATORS; opid++){
            State newState;
            if (useOperator(opid, currentState, &newState)){
                Node* newNode = makeNode(newState, node, opid);
                if (!findNode(openList, newNode) && !findNode(closedList, newNode)){
                    push(&openList, newNode);
                }
            }
        }
    }
}

int main(){
    //| 8 | 0 | 0 |
    State beginState = {8, 0, 0};
    Node* root = makeNode(beginState, NULL, -1);
    bfs(root);
    return 0;
}

