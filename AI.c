/* File: AI.c
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 25/06/21
 * Last Modified: 25/06/21
 * Purpose: Handles the AI for the game
 */

#include "AI.h"

int max(int a, int b) {
	int ret;
	if (a > b) {
		ret = a;
	} else {
		ret = b;
	}
}

int min(int a, int b) {
	int ret;
	if (a < b) {
		ret = a;
	} else {
		ret = b;
	}
}
/*returns the score of the input game state*/
int score(Game* game)
{
	int score;
    int ret;
	score = checkFinished(game);
	
	if (score == 1) { //win player 1
		ret = 10;
	} else if (score == 2) { //win player 2 (computer)
		ret = -10;
	} else if (score == 3) { //draw
		ret = 0;
	}
	return ret;
}

//minimax algorithm, determines the score of a certain board state
int minimax(Game* game)
{
	
	int ret, result, i, j, best, curScore;

	result = score(game);
	
	if (result != 0) {
		ret = result;
	} else if (game->turn == 1) { //player 1 is max
		best = -100 
		for(i = 0; i < game->rows; i++) {
			for(j =0; j < game->cols; j++) {
				if(board[i][j] == 0) {
					game->board[i][j] = 1;
					game->turn = 2;
					best = min(best, minimax(board));
					game->board[i][j] = 0; //undo move
					game->turn = 1; //reset turn
				}
			}
		}
		ret = best;
	} else if (game->turn == 2) { //player 2 is min
		best = 100
		for(i = 0; i < game->rows; i++) {
			for(j =0; j < game->cols; j++) {
				if(board[i][j] == 0) {
					game->board[i][j] = 2;
					game->turn = 1;
					best = max(best, minimax(board))
					game->board[i][j] = 0; //undo move
					game->turn = 2; //reset turn
				}
			}
		}
		ret = best;
	}
	return ret;
}

//finds the best move for the player who's turn it currently is
void makeBestMove(Game* game) {
	int bestVal, moveVal;

	if (game->turn == 1) { //player 1, max
		bestVal = -20;
		for(i = 0; i < game->rows; i++) {
			for(j = 0; j < game->cols; j++) {
				if(board[i][j] == 0) {
					game->board[i][j] = 1;
					game->turn = 2;
					moveVal = minimax(game);
					if (moveVal > bestVal) {
						game->board[i][j] = 1;
						game->turn = 2;
					}
				}  
			}
		}
	}
	else if (game->turn == 2) { //player 2 (computer), min
		bestVal = 20;
		for(i = 0; i < game->rows; i++) {
			for(j = 0; j < game->cols; j++) {
				if(board[i][j] == 0) {
					game->board[i][j] = 2;
					game->turn = 1;
					moveVal = minimax(game);
					if (moveVal > bestVal) {
						game->board[i][j] = 2;
						game->turn = 1;
					}
				}  
			}
		}
	}
}
				


	



