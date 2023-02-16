/* File: GameManager.h
 * Author: Liam Ryan
 * Date Created: 02/10/19
 * Purpose: header file for GameManager.c
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define FALSE 0
#define TRUE !FALSE

#include <stdlib.h>
#include <stdio.h>
#include "GameManager.h"
#include "Input.h"
#include "Logging.h"
#include "UCPLinkedList.h"

enum players { X, O };
enum gameStatus { ACTIVE, WIN_X, WIN_O, DRAW };

/*struct for a game of tic-tac-toe*/
typedef struct {
    int cols;
    int rows;
    int win;
    int total;
    int** board;
} Game;

 
Game* createGame(int, int, int);
void freeGame(Game*);
void runGame(Game*, LinkedList*);
void displayGame(Game*);
enum gameStatus checkFinished(Game*);
enum gameStatus checkCell(Game*, int, int); 
enum gameStatus checkLine(Game*, int, int, int, int);
int placeToken(Game*, int, int, char);
char playerToken(enum players);
#endif
