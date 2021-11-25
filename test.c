// C Program to print the elements of a
// Two-Dimensional array

#include<stdio.h>
#include "GameManager.h"


int main()
{
	// an array with 3 rows and 2 columns.
	int newBoard[4][4] = {
        {0,0,0,0}, 
        {0,2,2,0}, 
        {1,0,0,1}, 
        {0,1,1,0}, 
    };

	// output each array element's value
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("Element at x[%d][%d]:", i, j);
			printf("%d\n",newBoard[i][j]);
		}
	}

    Game* newGame;
    newGame = createGame(4,4,3);
    newGame->board = newBoard;
    displayGame(newGame);



	return 0;
}
