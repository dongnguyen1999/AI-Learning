#include <stdio.h>
#define EMPTY 0
#define UP 1
#define DOWN 0

typedef struct {
    int a, b, c, x, y, z;
} State;

void printState(State state){
    char text[][10] = {"DOWN", "UP"};
    printf("| %s | %s | %s | %s | %s | %s |\n", text[state.a], text[state.b], text[state.c], text[state.x], text[state.y], text[state.z]);
}

int equals(State a, State b){
    return (a.a == b.a && a.b == b.b && a.c == b.c && a.x == b.x && a.y == b.y && a.z == b.z);
}

char actions[][50] = {
    "Change the first 3 glasses",
    "Change the second 3 glasses",
    "Change the third 3 glasses",
    "Change the last 3 glasses",
};

int min(int a, int b){
    return a<b? a: b;
}

int max(int a, int b){
    return a>b? a: b;
}

#define NB_OPERATORS 4
#define CHANGE_FIRST 0
int changeTheFirst3Glasses(State state, State* result){
    *result = state;
    result->a = !state.a;
    result->b = !state.b;
    result->c = !state.c;
    return 1;
}

#define CHANGE_SECOND 1
int changeTheSecond3Glasses(State state, State* result){
    *result = state;
    result->x = !state.x;
    result->b = !state.b;
    result->c = !state.c;
    return 1;
}

#define CHANGE_THIRD 2
int changeTheThird3Glasses(State state, State* result){
    *result = state;
    result->x = !state.x;
    result->y = !state.y;
    result->c = !state.c;
    return 1;
}

#define CHANGE_LAST 3
int changeTheLast3Glasses(State state, State* result){
    *result = state;
    result->x = !state.x;
    result->y = !state.y;
    result->z = !state.z;
    return 1;
}

int useOperator(int opid, State state, State* result){
    switch (opid) {
        case CHANGE_FIRST:
            return changeTheFirst3Glasses(state, result);
        case CHANGE_SECOND:
            return changeTheSecond3Glasses(state, result);
        case CHANGE_THIRD:
            return changeTheThird3Glasses(state, result);
        case CHANGE_LAST:
            return changeTheLast3Glasses(state, result);
    }
}

int checkGoal(State state){
    State goal = {UP, UP, UP, UP, UP, UP};
    return equals(state, goal);
}


