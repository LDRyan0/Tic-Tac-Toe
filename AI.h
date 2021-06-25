/* Header file for AI.c */

#ifndef AI_H
#define AI_H

#define FALSE 0
#define TRUE !FALSE

#include <stdlib.h>
#include <stdio.h>
#include "GameManager.h"


int max(int a, int b);
int min(int a, int b);
int score(Game*);
int minimax(Game* game);
void makeBestMove(Game*)

#endif
