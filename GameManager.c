/* File: GameManager.c
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 02/10/19
 * Last Modified: 21/10/19
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
    for (i = 0; i < n; i++)
    {
        newGame->board[i] = (int*)calloc(m, sizeof(int));
    }

    /*calloc was used sets all values to 0 => cell hasn't been played yet*/

    return newGame;
}

/*frees the game in the game pointer passed in*/
void freeGame(Game* game)
{
    int i;
       
    for (i = 0; i < game->rows; i++)
    {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}
    

/*runs the game of TicTacToe until completion*/
void runGame(Game* game, LinkedList* log)
{
    int finished = FALSE; /*boolean value for whether the game has finished*/
    
    /*values to store the "unchecked" input of various variables*/
    char inChar;
    int inCol, inRow;
    
    int placeError; /*boolean value, stores return (error) value of placeToken function*/
    char player = 'X'; /*whose turn it is, always start with Player 1 (X)*/

    displayGame(game);
    
    while (finished == FALSE) /*while the game hasn't finished*/
    {
        do
        { 
            if (player == 'X')
            {
                printf("Player 1's (X) turn\n");
            }
            else
            {
                printf("Player 2's (O) turn\n");
            }
         
            /*get the user input for their proposed move*/   
            inChar = inputChar('A','A' + game->cols - 1, "Enter the column (letter) for your move\n");
            inCol = inChar - 65; /* turn uppercase letter into column index*/
            inRow = inputInt(1, game->rows, "Enter the row (number) for your move\n") - 1;
            
            /*places a token, will return TRUE (1) if space already occupied*/
            placeError = placeToken(game, inCol, inRow, player);
        
            if (placeError == TRUE)
            {
                printf("\nOOPS! The cell is already occupied, please select another cell\n");
            }
        } while (placeError == TRUE); /*repeats until valid move entered*/
        
        game->total++; /*there has been a successful move so increment the total moves*/
        
        /*add the successful move to the log*/
        addMove(log, game->total, player, inCol, inRow);
 
        /*alternate between X and O, whose turn it is*/
        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
        
        /* returns 0 if still going, 1 if Player 1 won, 2 if player 2 won, 3 if draw*/
        finished = checkFinished(game);
        
        displayGame(game); /*display the game after each move*/
    }
       
    /*the loop has been exited so the game has finished*/ 
    /*print statements for the 3 different ways that the game could have finished*/
    if (finished == 1)
    {
        printf("Player 1 (X) has won the game!\n");
        addMove(log, -1, 0, 0, 0); /*indicate player 1 has won game in log*/
    }
    else if (finished == 2)
    {
        printf("Player 2 (O) has won the game!\n");
        addMove(log, -2, 0, 0, 0); /*indicate player 2 has won game in log*/
    }
    else if (finished == 3)
    {
        printf("Game over, it's a tie!\n"); 
        addMove(log, -3, 0, 0, 0); /*indicate game ended in draw in log*/
    }        

    /*NOTE: I chose to indicate that a game was finished in the log linked list
        by having a Move with total being negative. I chose 3 different numbers
        so that statements of how the game finished (win P1, win P2, tie) could
        be added including by adjusting the algorithm in Logging.c
    */

    freeGame(game); /*frees the game, all info is stored in log*/
}

/*displays a game to the terminal*/
void displayGame(Game* game)
{
    int i, j, k;
    char character; 
    
    /*printing the top lettering*/
    printf("\n ");
    for (i = 0; i < game->cols; i++)
    {
        printf("   %c", 'A' + i);
    }
    /*top equals row*/
    printf("\n ==");
    for (i = 0; i < game->cols; i++)
    {
        printf("====");
    }
    printf("=\n");
   
    for (i = 0; i < game->rows; i++)
    {  
        /*print a row of entries*/ 
        printf(" ||");
        for (j = 0; j < game->cols; j++)
        {
            if (game->board[i][j] == 1)
            {
                character = 'X';
            }
            else if (game->board[i][j] == 2)
            {
                character = 'O';
            }
            else
            {
                character = ' ';
            }           
            printf(" %c |", character);

        }
        printf("| %d\n", i+1); /*print extra | and the row number*/
        /*print a horizontal line of dashes through board*/
        if (i < game->rows - 1)
        {
            printf(" --");
            for (k = 0; k < game->cols; k++)
            {
                printf("----");
            }
            printf("-\n");
        }
    }
    /*bottom equals row*/
    printf(" ==");
    for (i = 0; i < game->cols; i++)
    {
        printf("====");
    }
    printf("=\n\n");
    
}

/* - returns 0 if the game is not finished
 * - returns 1 if Player 1 (X) has won the game
 * - returns 2 if Player 2 (O) has won the game
 * - returns 3 if the game is a draw (the board is full)*/
int checkFinished(Game* game)
{
    int i = 0, j =0; /*indexes used for looping*/
    int finished = FALSE; /*boolean value for whether game has finished*/
    int val; /*stores the value in the current cell*/
    int max = game->rows * game->cols; /*the maximum number of entries*/
 

    /*iterate through all cells, if one is non-empty then checkCell()*/    
    while ((i < game->rows) && (finished == FALSE))
    {
        while ((j < game->cols) && (finished == FALSE))
        {
            val = game->board[i][j];
            if (val != 0)
            {
                finished = checkCell(game, i, j, val);
        
            }
            j++;
               
            /*if the board is full then stop the game*/
            if (game->total >= max)
            {
                finished = 3;
            }
        }
        j = 0;
        i++;
        
    }

/*right now finished is either:
 * 0 - the game is not yet finished
 * 1 - the game has been won by SOME player or
 * 3 - the game is a tie
 * val currently stores either 1 or 2, which player has won, so we will change
 * specify WHO (1 or 2... X or O) has won for out export
 */
    if (finished == 1)
    {
        finished = val;
    } 
    return finished; 
}


/*check an individual cell to see if it is part of a winning "line"*/
int checkCell(Game* game, int rowIdx, int colIdx, int val)
{
    int finished = FALSE;
 
    finished = checkHorizontal(game, rowIdx, colIdx, val);
    if (finished == FALSE)
    {
        finished = checkVertical(game, rowIdx, colIdx, val);
        if (finished == FALSE)
        {
            finished = checkDiag1(game, rowIdx, colIdx, val);
            if (finished == FALSE)
            {
                finished = checkDiag2(game, rowIdx, colIdx, val);
            }
        }
    }

    return finished;   
}

/* - checks horizontally from a given cell for a won game
 * - returns TRUE (1) or FALSE (0)*/
int checkHorizontal(Game* game, int rowIdx, int colIdx, int val)
{
    int i = rowIdx; /*the row index*/
    int j; /*the column index, stays constant in horizontal search*/
    int count = 1; /*stores the number of X's or O's there is currently is in a row*/
    int winCondition = game->win; /*the value required in a row for a win*/
    int exit; /*boolean value for whether a loop should be exited*/
    int finished = FALSE;
    
  
    j = colIdx - 1;
    exit = FALSE;    
    /*check to the left*/
    while ((j >= 0) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        j--;
    }

    j = colIdx + 1;
    exit = FALSE;    
    /*check to the right*/
    while ((j < game->cols) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        j++;
    }
    return finished;
}

/* - checks vertically from a given cell for a won game
 * - returns TRUE (1) or FALSE (0)*/
int checkVertical(Game* game, int rowIdx, int colIdx, int val)
{
    int i; /*the row index*/
    int j = colIdx; /*the column index, stays constant in horizontal search*/
    int count = 1; /*stores the number of X's or O's there is currently is in a row*/
    int winCondition = game->win; /*the value required in a row for a win*/
    int exit; /*boolean value for whether a loop should be exited*/
    int finished = FALSE;
    
  
    i = rowIdx - 1;
    exit = FALSE;    
    /*check to the left*/
    while ((i >= 0) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        i--;
    }

    i = rowIdx + 1;
    exit = FALSE;    
    /*check to the right*/
    while ((i < game->rows) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        i++;
    }
    return finished;
}

/* - checks the "down-right"/"up-left diagonal"
 * - returns TRUE (1) or FALSE (0)*/
int checkDiag1(Game* game, int rowIdx, int colIdx, int val)
{
    int i; /*the row index*/
    int j; /*the column index, stays constant in horizontal search*/
    int count = 1; /*stores the number of X's or O's there is currently is in a row*/
    int winCondition = game->win; /*the value required in a row for a win*/
    int exit; /*boolean value for whether a loop should be exited*/
    int finished = FALSE;
    
  
    i = rowIdx - 1;
    j = colIdx - 1;
    exit = FALSE;    
    /*check to the left*/
    while ((i >= 0) && (j >= 0) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        i--;
        j--;
    }

    i = rowIdx + 1;
    j = colIdx + 1;
    exit = FALSE;    
    /*check to the right*/
    while ((i < game->rows) && (j < game->cols) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        i++;
        j++;
    }
    return finished;
}

/* - checks the "up-left"/"down-right" diagonal
 * - returns TRUE (1) or FALSE (0)*/
int checkDiag2(Game* game, int rowIdx, int colIdx, int val)
{
    int i; /*the row index*/
    int j; /*the column index, stays constant in horizontal search*/
    int count = 1; /*stores the number of X's or O's there is currently is in a row*/
    int winCondition = game->win; /*the value required in a row for a win*/
    int exit; /*boolean value for whether a loop should be exited*/
    int finished = FALSE;
    
  
    i = rowIdx - 1;
    j = colIdx + 1;
    exit = FALSE;    
    /*check to the left*/
    while ((i >= 0) && (j < game->cols) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        i--;
        j++;
    }

    i = rowIdx + 1;
    j = colIdx - 1;
    exit = FALSE;    
    /*check to the right*/
    while ((i < game->rows) && (j >= 0) && (finished == FALSE) && (exit == FALSE))
    {
        if (game->board[i][j] == val)
        {
            count++;
        }
        else
        {
            exit = TRUE;
        }
        if (count == winCondition)
        {
            finished = TRUE;
        }
        i++;
        j--;
    }
    return finished;
}
       

/* - places a "token" (sets a value in the 2D array) on the given column index 
 * and row index.
 * - places a 1 if Player 1 (X's) turn
 * - places a 2 if Player 2 (O's) turn
 * - returns TRUE (1) or FALSE (0) whether the cell is already occupied */
int placeToken(Game* game, int colIdx, int rowIdx, char player)
{
    int set;
    int error = TRUE;

    /*if it's Player 1 (X's) (turn = 0) turn then we will set the cell to 1*/
    if (player == 'X')
    {
        set = 1;
    }
    else
    {
        set = 2;
    }
    
    if (game->board[rowIdx][colIdx] == 0)
    {
        game->board[rowIdx][colIdx] = set;
        error = FALSE;
    }    
    return error;
}
