#include <stdio.h>
#define EMPTY 0
#define GOAL 4
#define CAPACITY_X 8
#define CAPACITY_Y 5
#define CAPACITY_Z 3

typedef struct {
    int x, y, z;
} State;

void printState(State state){
    printf("| %d | %d | %d |\n", state.x, state.y, state.z);
}

int equals(State a, State b){
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

char actions[][50] = {
    "Pour milk from X to Y",
    "Pour milk from Y to X",
    "Pour milk from Y to Z",
    "Pour milk from Z to Y",
    "Pour milk from X to Z",
    "Pour milk from Z to X",
};

int min(int a, int b){
    return a<b? a: b;
}

int max(int a, int b){
    return a>b? a: b;
}

#define NB_OPERATORS 6
#define X_TO_Y 0
int pourMilkXY(State state, State* result){
    *result = state;
    if (state.x != EMPTY && state.y < CAPACITY_Y){
        result->x = max(state.x - (CAPACITY_Y - state.y), EMPTY);
        result->y = min(state.x + state.y, CAPACITY_Y);
        return 1;
    }
    return 0;
}

#define Y_TO_X 1
int pourMilkYX(State state, State* result){
    *result = state;
    if (state.y != EMPTY && state.x < CAPACITY_X){
        result->x = min(state.x + state.y, CAPACITY_X);
        result->y = max(state.y - (CAPACITY_X - state.x), EMPTY);
        return 1;
    }
    return 0;
}

#define Y_TO_Z 2
int pourMilkYZ(State state, State* result){
    *result = state;
    if (state.y != EMPTY && state.z < CAPACITY_Z){
        result->y = max(state.y - (CAPACITY_Z - state.z), EMPTY);
        result->z = min(state.y + state.z, CAPACITY_Z); 
        return 1;
    }
    return 0;
}

#define Z_TO_Y 3
int pourMilkZY(State state, State* result){
    *result = state;
    if (state.z != EMPTY && state.y < CAPACITY_Y){
        result->y = min(state.y + state.z, CAPACITY_Y);
        result->z = max(state.z - (CAPACITY_Y - state.y), EMPTY);
        return 1;
    }
    return 0;
}

#define X_TO_Z 4
int pourMilkXZ(State state, State* result){
    *result = state;
    if (state.x != EMPTY && state.z < CAPACITY_Z){
        result->x = max(state.x - (CAPACITY_Z - state.z), EMPTY);
        result->z = min(state.x + state.z, CAPACITY_Z);
        return 1;
    }
    return 0;
}

#define Z_TO_X 5
int pourMilkZX(State state, State* result){
    *result = state;
    if (state.z != EMPTY && state.x < CAPACITY_X){
        result->x = min(state.x + state.z, CAPACITY_X);
        result->z = max(state.z - (CAPACITY_X - state.x), EMPTY);
        return 1;
    }
    return 0;
}

int useOperator(int opid, State state, State* result){
    switch (opid) {
        case X_TO_Y:
            return pourMilkXY(state, result);
        case Y_TO_X:
            return pourMilkYX(state, result);
        case Y_TO_Z:
            return pourMilkYZ(state, result);
        case Z_TO_Y:
            return pourMilkZY(state, result);
        case X_TO_Z:
            return pourMilkXZ(state, result);
        case Z_TO_X:
            return pourMilkZX(state, result);
    }
}

int checkGoal(State state){
    return (state.x == GOAL || state.y == GOAL || state.z == GOAL);
}


