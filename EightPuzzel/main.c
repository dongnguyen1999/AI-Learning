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

void bfs(Node* root, State goal){
    List openList;
    List closedList;
    makeNull(&openList);
    makeNull(&closedList);
    push(&openList, root);
    while(!empty(openList)){
        // printf("%d\n", count);
        Node* node = shift(&openList);
        push(&closedList, node);
        State currentState = node->state;
        // printf("Current state: %p\n", node->parent);
        // printf("State: %p\n", node);
        // printState(currentState);
        // printf("Open:\n");
        // printList(openList);
        // printf("Close:\n");
        // printList(closedList);
        // printf("%d\n", openList.front);
        // if (count == 5000) break;
        // printf("%d\n", count);
        if (equals(currentState, goal)){
            // printf(">>");
            printResult(node);
            break;
        }
        int opid;
        for (opid = 0; opid < 4; opid++){
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
    // -------------
    // | 1 | 2 | 3 |
    // | 8 | 0 | 4 |
    // | 7 | 6 | 5 |
    // -------------
    int inputs[] = {1, 2, 3, 8, 4, 7, 6, 5};
    State state = makeState(inputs, 1, 1);

    // -------------
    // | 2 | 3 | 4 |
    // | 1 | 8 | 0 |
    // | 7 | 6 | 5 |
    // -------------
    int arr[] = {2, 3, 4, 1, 8, 7, 6, 5};
    State goal = makeState(arr, 1, 2);
    Node* root = makeNode(state, NULL, -1);
    bfs(root, goal);
    return 0;
}

