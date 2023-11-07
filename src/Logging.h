/* File: Logging.h
 * Author: Liam Ryan
 * Date Created: 03/10/19
 * Last Modified: 16/10/19
 * Purpose: header file for Logging.c
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LinkedList.h"

/*struct for a single move in a tic-tac-toe game, used for logging purposes:
 * each entry into the log is a Move struct*/
typedef struct {
    int turn;
    char player;
    int colIdx;
    int rowIdx;
} Move;

Move* createMove(int, char, int, int);
void freeData(void*);
void addMove(LinkedList*, int, char, int, int);
void saveLog(LinkedList*, int, int, int);
void viewLog(LinkedList*, int, int, int);

#endif
