#include <stdio.h>
#define EMPTY 0
#define LEFT 0
#define RIGHT 1
#define NB_MONKS 3
#define NB_DEMONS 3


typedef struct {
    int nbMonks;
    int nbDemons;
} Side;

typedef struct {
    Side left, right;
    int boatPosition;
} State;

State makeState(Side left, Side right, int boat){
    State state;
    state.left = left;
    state.right = right;
    state.boatPosition = boat;
    return state;
}

void printState(State state){
    printf("-------------------------------------\n");
    printf("Left side: %d monks, %d demons\n", state.left.nbMonks, state.left.nbDemons);
    printf("Right side: %d monks, %d demons\n", state.right.nbMonks, state.right.nbDemons);
    printf("%s\n", state.boatPosition==LEFT? "The boat is on the left side": "The boat is on the right side");
    printf("-------------------------------------\n");
}

int equals(State a, State b){
    return (
        a.left.nbMonks == b.left.nbMonks &&
        a.left.nbDemons == b.left.nbDemons &&
        a.right.nbMonks == b.right.nbMonks &&
        a.right.nbDemons == b.right.nbDemons &&
        a.boatPosition == b.boatPosition
    );
}

char actions[][50] = {
    "Move a monk to the other side",
    "Move a demon to the other side",
    "Move 2 monks to the other side",
    "Move 2 demons to the other side",
    "Move a monk and a demon to the other side",
};

#define NB_OPERATORS 5
#define MOVE_A_MONK_TO_THE_OTHER_SIDE 0
#define MOVE_A_DEMON_TO_THE_OTHER_SIDE 1
#define MOVE_2_MONKS_TO_THE_OTHER_SIDE 2
#define MOVE_2_DEMONS_TO_THE_OTHER_SIDE 3
#define MOVE_MONK_DEMON_TO_THE_OTHER_SIDE 4

int isValidState(State state){
    if (state.left.nbMonks != 0 && state.left.nbMonks < state.left.nbDemons) return 0;
    if (state.right.nbMonks != 0 && state.right.nbMonks < state.right.nbDemons) return 0;
    return 1;
}

int move(State state, State* result, int nbMonksInBoat, int nbDemonsInBoat){
    *result = state;
    if (state.boatPosition == LEFT && state.left.nbMonks >= nbMonksInBoat && state.left.nbDemons >= nbDemonsInBoat){
        state.left.nbMonks -= nbMonksInBoat;
        state.left.nbDemons -= nbDemonsInBoat;
        state.right.nbMonks += nbMonksInBoat;
        state.right.nbDemons += nbDemonsInBoat;
        if (isValidState(state)){
            result->left = state.left;
            result->right = state.right;
            result->boatPosition = RIGHT;
            return 1;
        }
    }
    if (state.boatPosition == RIGHT && state.right.nbMonks >= nbMonksInBoat && state.right.nbDemons >= nbDemonsInBoat){
        state.left.nbMonks += nbMonksInBoat;
        state.left.nbDemons += nbDemonsInBoat;
        state.right.nbMonks -= nbMonksInBoat;
        state.right.nbDemons -= nbDemonsInBoat;
        if (isValidState(state)){
            result->left = state.left;
            result->right = state.right;
            result->boatPosition = LEFT;
            return 1;
        }
    }
    return 0;
}

int useOperator(int opid, State state, State* result){
    switch (opid) {
        case MOVE_A_MONK_TO_THE_OTHER_SIDE:
            return move(state, result, 1, 0);
        case MOVE_A_DEMON_TO_THE_OTHER_SIDE:
            return move(state, result, 0, 1);
        case MOVE_2_MONKS_TO_THE_OTHER_SIDE:
            return move(state, result, 2, 0);
        case MOVE_2_DEMONS_TO_THE_OTHER_SIDE:
            return move(state, result, 0, 2);
        case MOVE_MONK_DEMON_TO_THE_OTHER_SIDE:
            return move(state, result, 1, 1);
    }
}

int checkGoal(State state){
    Side right = {3, 3};
    Side left = {0, 0};
    State goal = makeState(left, right, RIGHT);
    return equals(state, goal);
}


