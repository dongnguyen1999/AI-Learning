#include <stdio.h>
#define EMPTY 0
#define NB_COLUMNS 3
#define NB_ROWS 3

typedef struct {
    int cells[NB_ROWS][NB_COLUMNS];
    int emptyColumn, emptyRow;
} State;

State makeState(int inputs[],int empRow,int empCol){
    int i,j,t = 0;
    State state;
    for (i = 0;i < NB_ROWS; i++){
        for (j = 0; j < NB_COLUMNS; j++){
            if (i != empRow || j != empCol){
                state.cells[i][j] = inputs[t++];
            }
        }
    }
    state.cells[empRow][empCol] = 0;
    state.emptyRow = empRow;
    state.emptyColumn = empCol;
    return state;
}

void printState(State state){
    int i,j;
    printf("-------------\n");
    for (i = 0; i < NB_ROWS; i++){
        for (j = 0; j < NB_COLUMNS; j++){
            printf("| %d ", state.cells[i][j]);
        }
        printf("|\n");
    }
    printf("-------------\n");
}

int equals(State a, State b){
    int i,j;
    for (i = 0; i < NB_ROWS; i++){
        for (j = 0; j < NB_COLUMNS; j++){
            if (a.cells[i][j] != b.cells[i][j]) return 0;
        }
    }
    return 1;
}

char actions[][10] = {
    "UP", "DOWN", "LEFT", "RIGHT"
};

#define UP 0
int up(State state, State* result){
    *result = state;
    if (state.emptyRow > 0){
        result->cells[state.emptyRow][state.emptyColumn] = state.cells[state.emptyRow-1][state.emptyColumn];
        result->emptyRow = state.emptyRow-1;
        result->emptyColumn = state.emptyColumn;
        result->cells[result->emptyRow][result->emptyColumn] = EMPTY;
        return 1;
    }
    return 0;
}

#define DOWN 1
int down(State state, State* result){
    *result = state;
    if (state.emptyRow < NB_ROWS-1){
        result->cells[state.emptyRow][state.emptyColumn] = state.cells[state.emptyRow+1][state.emptyColumn];
        result->emptyRow = state.emptyRow+1;
        result->emptyColumn = state.emptyColumn;
        result->cells[result->emptyRow][result->emptyColumn] = EMPTY;
        return 1;
    }
    return 0;
}

#define LEFT 2
int left(State state, State* result){
    *result = state;
    if (state.emptyColumn > 0){
        result->cells[state.emptyRow][state.emptyColumn] = state.cells[state.emptyRow][state.emptyColumn-1];
        result->emptyRow = state.emptyRow;
        result->emptyColumn = state.emptyColumn-1;
        result->cells[result->emptyRow][result->emptyColumn] = EMPTY;
        return 1;
    }
    return 0;
}

#define RIGHT 3
int right(State state, State* result){
    *result = state;
    if (state.emptyColumn < NB_COLUMNS-1){
        result->cells[state.emptyRow][state.emptyColumn] = state.cells[state.emptyRow][state.emptyColumn+1];
        result->emptyRow = state.emptyRow;
        result->emptyColumn = state.emptyColumn+1;
        result->cells[result->emptyRow][result->emptyColumn] = EMPTY;
        return 1;
    }
    return 0;
}

int useOperator(int opid, State state, State* result){
    switch (opid) {
        case UP:
            return up(state, result);
        case DOWN:
            return down(state, result);
        case LEFT:
            return left(state, result);
        case RIGHT:
            return right(state, result);
    }
}


