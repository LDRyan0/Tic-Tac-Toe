/*File: GameManager.h
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 02/10/19
 * Last Modified: 21/10/19
 * Purpose: header file for GameManager.c
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define FALSE 0
#define TRUE !FALSE

#include <stdlib.h>
#include <stdio.h>
#include "Input.h"
#include "AI.h"


/*struct for a game of tic-tac-toe*/
typedef struct {
    int cols;
    int rows;
    int win;
    int mode;
    int total;
    int turn;
    int** board;
} Game;


Game* createGame(int, int, int);
void freeGame(Game*);
void runGame(Game*);
void displayGame(Game*);
int checkFinished(Game*);
int checkCell(Game*, int, int, int); 
int checkHorizontal(Game*, int, int, int); 
int checkVertical(Game*, int, int, int); 
int checkDiag1(Game*, int, int, int); 
int checkDiag2(Game*, int, int, int); 
int placeToken(Game*, int, int);

#endif
