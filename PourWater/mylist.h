#include <stdlib.h>
#define MAX_LENGTH 100

typedef struct State {
	int x, y;
    struct State* parent;
} State;

typedef struct {
    struct State* data[100];
    int size;
} List;

void makeNull(List *L){
    L->size = 0;
}

int empty(List L){
    return L.size == 0;
}

void push(List *L, State* state){
    L->data[L->size++] = state;
}

State* pop(List *L){
    State* popedState;
    if (!empty(*L)){
        popedState = L->data[--L->size];
    }
    return popedState;
}

State* shift(List *L){
    State* shiftedState;
    if (!empty(*L)){
        int i;
        shiftedState = L->data[0];
        for (i = 1; i < L->size; i++){
            L->data[i-1] = L->data[i];
        }
        L->size--;
    }
    return shiftedState;
}

void unshift(List *L, State* state){
    int i;
    for (i = L->size-1; i >= 0; i--){
        L->data[i+1] = L->data[i];
    }
    L->data[0] = state;
    L->size++;
}

void printState(State state){
	printf("%d %d\n", state.x, state.y);
}

void printList(List L){
    if (empty(L)){
        printf("[]\n");
        return;
    }
    int i;
    for (i = 0;i < L.size; i++){
        if (i == 0) printf("[");
        printf("{%d,%d}", L.data[i]->x, L.data[i]->y);
        if (i == L.size-1) printf("]\n"); else printf(", ");
    }
}

int isInList(List L, State state){
    int i;
    for (i = 0; i < L.size; i++){
        State* data = L.data[i];
        if (state.x == data->x && state.y == data->y){
            return 1;
        }
    }
    return 0;
}




