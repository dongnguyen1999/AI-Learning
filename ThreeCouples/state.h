#include <stdio.h>
#include <string.h>
#define LEFT 0
#define RIGHT 1
#define NB_COUPLES 3


typedef struct {
    int wife;
    int husband;
} Couple;

typedef struct {
    Couple couples[NB_COUPLES];
    int boatPosition;
} State;

State makeState(Couple arr[], int boat){
    State state;
    int i;
    for (i = 0;i < NB_COUPLES; i++){
        state.couples[i] = arr[i];
    }
    state.boatPosition = boat;
    return state;
}

void printState(State state){
    printf("-------------------------------------\n");
    char men[][10] = {"man1 ", "man2 ", "man3 "};
    char women[][10] = {"woman1 ", "woman2 ", "woman3 "};
    int i;
    char left[100] = "";
    char right[100] = "";
    for (i = 0;i < NB_COUPLES; i++){
        if (state.couples[i].wife == LEFT) strcat(left, women[i]);
        else strcat(right, women[i]);
        if (state.couples[i].husband == LEFT) strcat(left, men[i]);
        else strcat(right, men[i]);
    }
    printf("Left side: %s\n", left);
    printf("Right side: %s\n", right);
    printf("%s\n", state.boatPosition==LEFT? "The boat is on the left side": "The boat is on the right side");
    printf("-------------------------------------\n");
}

int equals(State a, State b){
    int i;
    for (i = 0; i < NB_COUPLES; i++){
        Couple coupleA = a.couples[i];
        Couple coupleB = b.couples[i];
        if (coupleA.wife != coupleB.wife || coupleA.husband != coupleB.husband) return 0;
    }
    return a.boatPosition==b.boatPosition?1:0;
}

State cloneState(State state){
    State newState;
    newState.boatPosition = state.boatPosition;
    int i;
    for (i = 0;i < NB_COUPLES; i++){
        newState.couples[i] = state.couples[i];
    }
    return newState;
}

char actions[][50] = {
    "Move man1 to the other side",
    "Move man2 to the other side",
    "Move man3 to the other side",
    "Move woman1 to the other side",
    "Move woman2 to the other side",
    "Move woman3 to the other side",
    "Move man1 and man2 to the other side",
    "Move man1 and man3 to the other side",
    "Move man2 and man3 to the other side",
    "Move man1 and woman1 to the other side",
    "Move man2 and woman2 to the other side",
    "Move man3 and woman3 to the other side",
    "Move woman1 and woman2 to the other side",
    "Move woman1 and woman3 to the other side",
    "Move woman2 and woman3 to the other side",
};

#define NB_OPERATORS 15
#define MOVE_MAN1 0
#define MOVE_MAN2 1
#define MOVE_MAN3 2
#define MOVE_WOMAN1 3
#define MOVE_WOMAN2 4
#define MOVE_WOMAN3 5
#define MOVE_MAN1_MAN2 6
#define MOVE_MAN1_MAN3 7
#define MOVE_MAN2_MAN3 8
#define MOVE_MAN1_WOMAN1 9
#define MOVE_MAN2_WOMAN2 10
#define MOVE_MAN3_WOMAN3 11
#define MOVE_WOMAN1_WOMAN2 12
#define MOVE_WOMAN1_WOMAN3 13
#define MOVE_WOMAN2_WOMAN3 14

int isValidState(State state){
    int i,j;
    for (i = 0; i < NB_COUPLES; i++){
        Couple couple = state.couples[i];
        for(j = 0; j < NB_COUPLES; j++){
            if (j != i){
                Couple otherCouple = state.couples[j];
                if (couple.wife != couple.husband && couple.wife == otherCouple.husband) return 0;
            }
        }
    }
    return 1;
}

int moveMan(State state, State* result, int coupleIndex){
    *result = cloneState(state);
    int manPosition = state.couples[coupleIndex].husband;
    if (manPosition == state.boatPosition){
        result->boatPosition = !state.boatPosition;
        result->couples[coupleIndex].husband = result->boatPosition;
        if (!isValidState(*result)){
            result->boatPosition = state.boatPosition;
            result->couples[coupleIndex].husband = manPosition;
            return 0;
        }
        return 1;
    }
    return 0;
}

int moveWoman(State state, State* result, int coupleIndex){
    *result = cloneState(state);
    int womanPosition = state.couples[coupleIndex].wife;
    if (womanPosition == state.boatPosition){
        result->boatPosition = !state.boatPosition;
        result->couples[coupleIndex].wife = result->boatPosition;
        if (!isValidState(*result)){
            result->boatPosition = state.boatPosition;
            result->couples[coupleIndex].wife = womanPosition;
            return 0;
        }
        return 1;
    }
    return 0;
}

int move2Men(State state, State* result, int coupleIndex1, int coupleIndex2){
    *result = cloneState(state);
    int man1Position = state.couples[coupleIndex1].husband;
    int man2Position = state.couples[coupleIndex2].husband;
    if (man1Position == state.boatPosition && man2Position == state.boatPosition){
        result->boatPosition = !state.boatPosition;
        result->couples[coupleIndex1].husband = result->boatPosition;
        result->couples[coupleIndex2].husband = result->boatPosition;
        if (!isValidState(*result)){
            result->boatPosition = state.boatPosition;
            result->couples[coupleIndex1].husband = man1Position;
            result->couples[coupleIndex2].husband = man2Position;
            return 0;
        }
        return 1;
    }
    return 0;
}

int move2Women(State state, State* result, int coupleIndex1, int coupleIndex2){
    *result = cloneState(state);
    int woman1Position = state.couples[coupleIndex1].wife;
    int woman2Position = state.couples[coupleIndex2].wife;
    if (woman1Position == state.boatPosition && woman2Position == state.boatPosition){
        result->boatPosition = !state.boatPosition;
        result->couples[coupleIndex1].wife = result->boatPosition;
        result->couples[coupleIndex2].wife = result->boatPosition;
        if (!isValidState(*result)){
            result->boatPosition = state.boatPosition;
            result->couples[coupleIndex1].wife = woman1Position;
            result->couples[coupleIndex2].wife = woman2Position;
            return 0;
        }
        return 1;
    }
    return 0;
}

int moveCouple(State state, State* result, int coupleIndex){
    *result = cloneState(state);
    int manPosition = state.couples[coupleIndex].husband;
    int womanPosition = state.couples[coupleIndex].wife;
    if (manPosition == state.boatPosition && womanPosition == state.boatPosition){
        result->boatPosition = !state.boatPosition;
        result->couples[coupleIndex].husband = result->boatPosition;
        result->couples[coupleIndex].wife = result->boatPosition;
        if (!isValidState(*result)){
            result->boatPosition = state.boatPosition;
            result->couples[coupleIndex].husband = manPosition;
            result->couples[coupleIndex].wife = womanPosition;
            return 0;
        }
        return 1;
    }
    return 0;
}


int useOperator(int opid, State state, State* result){
    switch (opid) {
        case MOVE_MAN1:
            return moveMan(state, result, 0);
        case MOVE_MAN2:
            return moveMan(state, result, 1);
        case MOVE_MAN3:
            return moveMan(state, result, 2);
        case MOVE_WOMAN1:
            return moveWoman(state, result, 0);
        case MOVE_WOMAN2:
            return moveWoman(state, result, 1);
        case MOVE_WOMAN3:
            return moveWoman(state, result, 2);
        case MOVE_MAN1_MAN2:
            return move2Men(state, result, 0, 1);
        case MOVE_MAN1_MAN3:
            return move2Men(state, result, 0, 2);
        case MOVE_MAN2_MAN3:
            return move2Men(state, result, 1, 2);
        case MOVE_WOMAN1_WOMAN2:
            return move2Women(state, result, 0, 1);
        case MOVE_WOMAN1_WOMAN3:
            return move2Women(state, result, 0, 2);
        case MOVE_WOMAN2_WOMAN3:
            return move2Women(state, result, 1, 2);
        case MOVE_MAN1_WOMAN1:
            return moveCouple(state, result, 0);
        case MOVE_MAN2_WOMAN2:
            return moveCouple(state, result, 1);
        case MOVE_MAN3_WOMAN3:
            return moveCouple(state, result, 2);
    }
}

int checkGoal(State state){
    Couple arr[] = {
        {RIGHT, RIGHT},
        {RIGHT, RIGHT},
        {RIGHT, RIGHT},
    };
    State goal = makeState(arr, RIGHT);
    return equals(state, goal);
}


