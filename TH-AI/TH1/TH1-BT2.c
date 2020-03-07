#include <stdio.h>
#include <stdlib.h>

#define TANKCAPACITY_X 9
#define TANKCAPACITY_Y 4
#define EMPTY 0
#define GOAL 6
#define MAX_LENGTH 100
#define NON_ACTION 0

const char* actions[] = {
    "First state",
    "Pour water full X",
    "Pour water full Y",
    "Empty X",
    "Empty Y",
    "Pour water X to Y",
    "Pour water Y to X",
};

typedef struct {
    int x, y;
} State;

void printState(State state){
    printf("X:%d --- Y:%d\n", state.x, state.y);
}

int equals(State state1, State state2){
    return state1.x == state2.x && state1.y == state2.y;
}

int pourWaterFullX(State state, State* result){
    if (state.x < TANKCAPACITY_X){
        *result = state;
        result->x = TANKCAPACITY_X;
        return 1;
    }
    return 0;
}

int pourWaterFullY(State state, State* result){
    if (state.y < TANKCAPACITY_Y){
        *result = state;
        result->y = TANKCAPACITY_Y;
        return 1;
    }
    return 0;
}

int pourWaterEmptyX(State state, State* result){
    if (state.x != EMPTY){
        *result = state;
        result->x = EMPTY;
        return 1;
    }   
    return 0;
}

int pourWaterEmptyY(State state, State* result){
    if (state.y != EMPTY){
        *result = state;
        result->y = EMPTY;
        return 1;
    }   
    return 0;
}

int min(int a, int b){
    return a<b?a:b;
}

int max(int a, int b){
    return a>b?a:b;
}

int pourWaterXY(State state, State* result){
    if (state.x != EMPTY && state.y < TANKCAPACITY_Y){
        *result = state;
        result->x = max(state.x-(TANKCAPACITY_Y-state.y), EMPTY);
        result->y = min(state.x + state.y, TANKCAPACITY_Y);
        return 1;
    }
    return 0;
}

int pourWaterYX(State state, State* result){
    if (state.y != EMPTY && state.x < TANKCAPACITY_X){
        *result = state;
        result->x = min(state.x + state.y, TANKCAPACITY_X);
        result->y = max(state.y-(TANKCAPACITY_X-state.x), EMPTY);
        return 1;
    }
    return 0;
}

#define NB_OPERATORS 6
int useOperator(State state, State* result, int opid){
    switch (opid){
        case 1: return pourWaterFullX(state, result);
        case 2: return pourWaterFullY(state, result);
        case 3: return pourWaterEmptyX(state,result);
        case 4: return pourWaterEmptyY(state, result);
        case 5: return pourWaterXY(state, result);
        case 6: return pourWaterYX(state, result);
        default:
            printf("Error when use operator\n");
            return 0;
    }
}

typedef struct node{
    State state;
    struct node* parent;
    int action;
} Node;

Node* makeNode(State state, Node* parent, int action){
    Node* p = (Node*)malloc(sizeof(Node));
    p->state = state;
    p->parent = parent;
    p->action = action;
    return p;
}

typedef struct{
    Node* data[MAX_LENGTH];
    int size;
} Stack;

void makeNullStack(Stack* s){
    s->size = EMPTY;
}

int emptyStack(Stack s){
    return s.size == 0;
}

void push(Stack *s, Node* node){
    s->data[s->size++] = node;
}

Node* pop(Stack* s){
    return s->data[--s->size];
}

int findInStack(Stack s, State state){
    int i;
    for (i = 0; i < s.size; i++){
        State stateI = s.data[i]->state;
        if (equals(state, stateI)) return 1;
    }
    return 0;
}

void printResult(Node* endPoint){
    Node *p = endPoint;
    Stack s;
    makeNullStack(&s);
    while (p != NULL){
        push(&s, p);
        p = p->parent;
    }
    while (!emptyStack(s)){
        Node* top = pop(&s);
        printf("%s\n",actions[top->action]);
        printState(top->state);
    }
}

int checkGoal(State state){
    return state.x == GOAL || state.y == GOAL;
}

void dfs(Node* root){
    Stack openStack;
    Stack closedStack;
    makeNullStack(&openStack);
    makeNullStack(&closedStack);
    push(&openStack, root);
    while (!emptyStack(openStack)){
        Node* node = pop(&openStack);
        push(&closedStack, node);
        State currentState = node->state;
        // printState(currentState);
        if (checkGoal(currentState)){
            // printf(">>");
            printResult(node);
            break;
        }
        int opid;
        for (opid = 1; opid <= NB_OPERATORS; opid++){
            State nextState;
            if (useOperator(currentState, &nextState, opid)){
                if (!findInStack(openStack, nextState) && !findInStack(closedStack, nextState)){
                    Node* newNode = makeNode(nextState, node, opid);
                    push(&openStack, newNode);
                }
            }
        }
    }
}



int main(){
    State beginState = {0, 0};
    Node* root = makeNode(beginState, NULL, NON_ACTION);
    dfs(root);
}
