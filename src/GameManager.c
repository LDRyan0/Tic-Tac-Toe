/* File: GameManager.c
 * Author: Liam Ryan
 * Date Created: 02/10/19
 * Purpose: Handles the creation, running and other functionality related to
 *  the game of tic-tac-toe
 */

#include "GameManager.h"

/*creates and returns a pointer to a new game with the specified values*/
Game* createGame(int m, int n, int k)
{
	int i; /*index used for the iterative memory allocation of 2D array of the board*/
	Game* newGame;

	newGame = (Game*)malloc(sizeof(Game));
	    
	newGame->cols = m;
	newGame->rows = n;
	newGame->win = k;
	newGame->total = 0;
	     
	/*allocating the memory for the 2D array representing the board*/
	newGame->board = (int**)calloc(n, sizeof(int*));

	for (i = 0; i < n; i++) {
		/*calloc used to set all values to 0 => cell hasn't been played yet*/
		newGame->board[i] = (int*)calloc(m, sizeof(int));
	}

	return newGame;
}

/*frees the game in the game pointer passed in*/
void freeGame(Game* game)
{
	int i;

	for (i = 0; i < game->rows; i++) {
		free(game->board[i]);
	}
	free(game->board);
	free(game);
}
    

/*runs the game of TicTacToe until completion*/
void runGame(Game* game, LinkedList* log)
{
	enum gameStatus status = ACTIVE; /*value for whether the game has finished*/
	    
	/*values to store the "unchecked" input of various variables*/
	char inChar;
	int inCol, inRow;

	int placeError; /*boolean value, stores return (error) value of placeToken function*/
	enum players player = X; /*whose turn it is, always start with Player 1 (X)*/
	
	displayGame(game);
    
	while (status == ACTIVE) {
		do { 
			if (player == X) {
				printf("Player 1's (X) turn\n");
			} else {
				printf("Player 2's (O) turn\n");
			}
         
			/*get the user input for their proposed move*/   
			inChar = inputChar('A','A' + game->cols - 1, "Enter the column (letter) for your move\n");
			inCol = inChar - 65; /* turn uppercase letter into column index*/
			inRow = inputInt(1, game->rows, "Enter the row (number) for your move\n") - 1;
	            
			/*places a token, will return TRUE (1) if space already occupied*/
			placeError = placeToken(game, inCol, inRow, player);

			if (placeError) {
				printf("\nOOPS! The cell is already occupied, please select another cell\n");
			}
		} while (placeError); /*repeats until valid move entered*/

		game->total++; /*there has been a successful move so increment the total moves*/
	
		/*add the successful move to the log*/
		addMove(log, game->total, playerToken(player), inCol, inRow);
	 
		/*alternate between X and O, whose turn it is*/
		if (player == X) {
			player = O;
		} else { 
			player = X;
		}
        
		/* returns ACTIVE if still going, WIN_X if Player 1 won, WIN_O if player 2 won, DRAW if draw*/
		status = checkFinished(game);

		displayGame(game); /*display the game after each move*/
	}
       
	/*the loop has been exited so the game has g*/ 
	/*print statements for the 3 different ways that the game could have g*/
	if (status == WIN_X) {
		printf("Player 1 (X) has won the game!\n");
		addMove(log, -1, 0, 0, 0); /*indicate player 1 has won game in log*/
	} else if (status == WIN_O) {
		printf("Player 2 (O) has won the game!\n");
		addMove(log, -2, 0, 0, 0); /*indicate player 2 has won game in log*/
	} else if (status == DRAW) {
		printf("Game over, it's a tie!\n"); 
		addMove(log, -3, 0, 0, 0); /*indicate game ended in draw in log*/
	}        
    /*NOTE: I chose to indicate that a game was g in the log linked list
        by having a Move with total being negative. I chose 3 different numbers
        so that statements of how the game g (win P1, win P2, tie) could
        be added including by adjusting the algorithm in Logging.c
    */

	freeGame(game); /*frees the game, all info is stored in log*/
}

/*displays a game to the terminal*/
void displayGame(Game* game) {
	int i, j, k;
	char character; 
    
	/*printing the top lettering*/
	printf("\n\t ");
	for (i = 0; i < game->cols; i++) {
		printf("   %c", 'A' + i);
	}
	/*top equals row*/
	printf("\n\t ==");
	for (i = 0; i < game->cols; i++) {
		printf("====");
	}
	printf("=\n");
	   
	for (i = 0; i < game->rows; i++) {  
		/*print a row of entries*/ 
		printf("\t ||");
		for (j = 0; j < game->cols; j++) {
			if (game->board[i][j] == 1) {
				character = 'X';
			} else if (game->board[i][j] == 2) {
				character = 'O';
			} else {
				character = ' ';
			}           
			printf(" %c |", character);
		}
		printf("| %d\n", i+1); /*print extra | and the row number*/
		/*print a horizontal line of dashes through board*/
		if (i < game->rows - 1) {
			printf("\t --");
			for (k = 0; k < game->cols; k++) {
				printf("----");
			}
			printf("-\n");
		}
	}
	/*bottom equals row*/
	printf("\t ==");
	for (i = 0; i < game->cols; i++) {
		printf("====");
	}
	printf("=\n\n");
}

/* - returns ACTIVE = 0 if the game is not g
 * - returns  WIN_X = 1 if Player 1 (X) has won the game
 * - returns  WIN_O = 2 if Player 2 (O) has won the game
 * - returns   DRAW = 3 if the game is a draw (the board is full)*/
enum gameStatus checkFinished(Game* game) {
	int i = 0, j =0; /*indexes used for looping*/
	enum gameStatus status = ACTIVE; /*value for status of the game*/
	int max = game->rows * game->cols; /*the maximum number of entries*/
	
	/*iterate through all cells, if one is non-empty then checkCell()*/    
	while ((i < game->rows) && (status == ACTIVE)) {
		while ((j < game->cols) && (status == ACTIVE)) {
			if (game->board[i][j] != 0) { /* only check cell if it has token */
				status = checkCell(game, i, j);
			}
			j++;

			/*if the board is full then stop the game*/
			if (game->total >= max) {
				status = DRAW;
			}
		}
		j = 0;
		i++;
	} 
	return status; 
}


/*check an individual cell to see if it is part of a winning "line"*/
enum gameStatus checkCell(Game* game, int rowIdx, int colIdx) {
	enum gameStatus status = ACTIVE;
 
	status = checkLine(game, rowIdx, colIdx, 1, 0); /* horizontal */
	if (status == ACTIVE) {
		status = checkLine(game, rowIdx, colIdx, 0, 1); /* vertical */
		if (status == ACTIVE) {
			status = checkLine(game, rowIdx, colIdx, 1, 1); /* diag 1 */
			if (status == ACTIVE) {
				status = checkLine(game, rowIdx, colIdx, 1, -1); /* diag 2 */
			}
		}
	}
	return status;   
}

/* - checks for a win condition in a generic fashion
 * - returns status {ACTIVE = 0, WIN_X = 1, WIN_O = 2, DRAW = 3} */
enum gameStatus checkLine(Game *game, int rowIdx, int colIdx, int xInc, int yInc) {
	int i, j, step;
	int count = 1;
	int val = game->board[rowIdx][colIdx]; /* which player are we checking for win */
	int winCondition = game->win;
	int exit = FALSE;
	enum gameStatus status = ACTIVE;

	for(step = 0; step < 2; step++) { 
		i = rowIdx + yInc;
		j = colIdx + xInc;
		while ((j >= 0) && (j < game->cols) && (i >= 0) && (i < game->rows) 
		&& (status == ACTIVE) && (exit == FALSE)) { 
			if (game->board[i][j] == val) { 
				count++;
			} else { 
				exit = TRUE;
			} 
			if (count == winCondition) { 
				/* val = 1 => status = 1 = WIN_X
				 * val = 2 => status = 2 = WIN_O */
				status = val;
			}
			j += xInc;
			i += yInc;
		}
		/* we have just checked forward so now check backward */
		yInc *= -1;
		xInc *= -1;
	}

	return status;
}

/* - places a "token" (sets a value in the 2D array) on the given column index 
 * and row index.
 * - places a 1 into board if Player 1 (X's) turn
 * - places a 2 into board if Player 2 (O's) turn
 * - returns TRUE (1) or FALSE (0) whether the cell is already occupied */
int placeToken(Game* game, int colIdx, int rowIdx, char player)
{
	int set;
	int error = TRUE;
	    
	/*if it's Player 1 (X's) (turn = 0) turn then we will set the cell to 1*/
	if (player == X) {
		set = 1;
	} else {
		set = 2;
	}
	
	if (game->board[rowIdx][colIdx] == 0) {
		game->board[rowIdx][colIdx] = set;
		error = FALSE;
	}    
	return error;
}

char playerToken(enum players player) { 
	char tok;
	if(player == X) {
		tok = 'X';
	} else { 
		tok = 'O';
	}
	return tok;
}
