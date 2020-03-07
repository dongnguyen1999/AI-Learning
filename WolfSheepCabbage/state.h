#include <stdio.h>
#define LEFT 0
#define RIGHT 1


typedef struct {
    int wolf, sheep, cabbage;
    int boatPosition;
} State;

void printState(State state){
    printf("-------------------------------------\n");
    printf("Left side: %s%s%s%s\n", state.wolf==LEFT?"wolf ":"", state.sheep==LEFT?"sheep ":"", state.cabbage==LEFT?"cabbage ":"",state.boatPosition==LEFT?"boat ":"");
    printf("Right side: %s%s%s%s\n", state.wolf==RIGHT?"wolf ":"", state.sheep==RIGHT?"sheep ":"", state.cabbage==RIGHT?"cabbage ":"",state.boatPosition==RIGHT?"boat ":"");
    printf("-------------------------------------\n");
}

int equals(State a, State b){
    return (
        a.wolf == b.wolf &&
        a.sheep == b.sheep &&
        a.cabbage == b.cabbage &&
        a.boatPosition == b.boatPosition
    );
}

char actions[][50] = {
    "Move the wolf to the other side",
    "Move the sheep to the other side",
    "Move the cabbage to the other side",
    "Move to the other side",
};

#define NB_OPERATORS 4
#define MOVE_WOLF_TO_OTHER_SIDE 0
#define MOVE_SHEEP_TO_OTHER_SIDE 1
#define MOVE_CABBAGE_TO_OTHER_SIDE 2
#define MOVE_TO_OTHER_SIDE 3

int isValidState(State state){
    if (state.wolf == state.sheep && state.wolf != state.boatPosition) return 0;
    if (state.sheep == state.cabbage && state.sheep != state.boatPosition) return 0;
    return 1;
}

int moveWolf(State state, State* result){
    *result = state;
    if (state.boatPosition == state.wolf){
        state.boatPosition = !state.boatPosition;
        state.wolf = state.boatPosition;
        if (isValidState(state)){
            result->wolf = state.wolf;
            result->boatPosition = state.boatPosition;
            return 1;
        }
    }
    return 0;
}

int moveSheep(State state, State* result){
    *result = state;
    if (state.boatPosition == state.sheep){
        state.boatPosition = !state.boatPosition;
        state.sheep = state.boatPosition;
        if (isValidState(state)){
            result->sheep = state.sheep;
            result->boatPosition = state.boatPosition;
            return 1;
        }
    }
    return 0;
}

int moveCabbage(State state, State* result){
    *result = state;
    if (state.boatPosition == state.cabbage){
        state.boatPosition = !state.boatPosition;
        state.cabbage = state.boatPosition;
        if (isValidState(state)){
            result->cabbage = state.cabbage;
            result->boatPosition = state.boatPosition;
            return 1;
        }
    }
    return 0;
}

int moveBoat(State state, State* result){
    *result = state;
    state.boatPosition = !state.boatPosition;
    if (isValidState(state)){
        result->boatPosition = state.boatPosition;
        return 1;
    }
    return 0;
}

int useOperator(int opid, State state, State* result){
    switch (opid) {
        case MOVE_WOLF_TO_OTHER_SIDE:
            return moveWolf(state, result);
        case MOVE_SHEEP_TO_OTHER_SIDE:
            return moveSheep(state, result);
        case MOVE_CABBAGE_TO_OTHER_SIDE:
            return moveCabbage(state, result);
        case MOVE_TO_OTHER_SIDE:
            return moveBoat(state, result);
    }
}

int checkGoal(State state){
    State goal = {RIGHT, RIGHT, RIGHT, RIGHT};
    return equals(state, goal);
}


