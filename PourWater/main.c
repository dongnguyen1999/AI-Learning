#include <stdio.h>
#include "mylist.h"

#define CAPACITY_X 9
#define CAPACITY_Y 4
#define GOAL 6

#define MAX_LENGTH 100
#define EMPTY 0

int min(int a, int b){
	return (a<b? a: b);
}

int max(int a, int b){
	return (a>b? a: b);
}

#define FULL_X 0
void pourWaterFullX(State state, State* result){
	result->x = CAPACITY_X;
	result->y = state.y;
}

#define FULL_Y 1
void pourWaterFullY(State state, State* result){
	result->x = state.x;
	result->y = CAPACITY_Y;
}

#define EMPTY_X 2
void pourWaterEmptyX(State state, State* result){
	result->x = EMPTY;
	result->y = state.y;
}

#define EMPTY_Y 3
void pourWaterEmptyY(State state, State* result){
	result->x = state.x;
	result->y = EMPTY;
}

#define X_TO_Y 4
void pourWaterXY(State state, State* result){
	*result = state;
	if (state.x != EMPTY && state.y != CAPACITY_Y){
		result->x = max(state.x - (CAPACITY_Y - state.y), EMPTY);
		result->y = min(state.x + state.y, CAPACITY_Y);
	}
}

#define Y_TO_X 5
void pourWaterYX(State state, State* result){
	*result = state;
	if (state.y != EMPTY && state.x != CAPACITY_X){
		result->x = min(state.x + state.y, CAPACITY_X);
		result->y = max(state.y - (CAPACITY_X - state.x), EMPTY);
	}
}

int useOperator(int opid, State state, State* result){
	char *message;
	switch (opid){
		case FULL_X:
			pourWaterFullX(state, result);
			break;
		case FULL_Y:
			pourWaterFullY(state, result);
			break;
		case EMPTY_X:
			pourWaterEmptyX(state, result);
			break;
		case EMPTY_Y:
			pourWaterEmptyY(state, result);
			break;
		case X_TO_Y:
			pourWaterXY(state, result);
			break;
		case Y_TO_X:
			pourWaterYX(state, result);
			break;
	}
	if (result->x == state.x && result->y == state.y) return 0;
	return 1;
}

int checkGoal(State state){
	return (state.x == GOAL || state.y == GOAL);
}


void printResult(State* endedState){
	List stack;
	makeNull(&stack);
	State *p = endedState;
	while (p != NULL){
		push(&stack, p);
		p = p->parent;
	}
	while (!empty(stack)){
		printState(*pop(&stack));
	}	
}

void dfs(State* firstState){
	List openList;
	List closedList;
	makeNull(&openList);
	makeNull(&closedList);
	push(&openList, firstState);
	while (!empty(openList)){
		State* currentState = pop(&openList);
		push(&closedList, currentState);
		if (checkGoal(*currentState)) {
			printResult(currentState);
			break;
		}
		int i;
		for(i = 0;i <= 5; i++){
			State* newState = (State*) malloc(sizeof(State));
			if (useOperator(i, *currentState, newState)){
				if (!isInList(openList, *newState) && !isInList(closedList, *newState)){
					newState->parent = currentState;
					push(&openList, newState);
				}
			}
		}
	}
}

void bfs(State* firstState){
	List openList;
	List closedList;
	makeNull(&openList);
	makeNull(&closedList);
	push(&openList, firstState);
	while (!empty(openList)){
		State* currentState = shift(&openList);
		push(&closedList, currentState);
		if (checkGoal(*currentState)) {
			printResult(currentState);
			break;
		}
		int i;
		for(i = 0;i <= 5; i++){
			State* newState = (State*) malloc(sizeof(State));
			if (useOperator(i, *currentState, newState)){
				if (!isInList(openList, *newState) && !isInList(closedList, *newState)){
					newState->parent = currentState;
					push(&openList, newState);
				}
			}
		}
	}
}


int main(){
	State state = {0, 0};
	bfs(&state);
}
