#include <stdio.h>
#include <stdlib.h>

#define TANKCAPACITY_X 9
#define TANKCAPACITY_Y 4
#define EMPTY 0
#define GOAL 6
#define MAX_LENGTH 100

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

int main(){
    State beginState = {5, 4};
    printf("Trang thai bat dau\n");
    printState(beginState);
    int opid;
    for (opid = 1; opid <= NB_OPERATORS; opid++){
        State nextState;
        if (useOperator(beginState, &nextState, opid)){
            printf("%s successfully\n", actions[opid]);
            printState(nextState);
        } else printf("%s failed\n", actions[opid]);
    } 
}
