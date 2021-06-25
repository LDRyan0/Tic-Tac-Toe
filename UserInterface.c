/* File: UserInterface.c
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 01/10/19
 * Last Modified: 21/10/19
 * Purpose: holds the main menu system for the TicTacToe program
 */

#include "UserInterface.h"

void menu(int m, int n, int k) /*the menu starts with the settings loaded in*/
{
    int menu = 1; /*holds the menu selection from the user*/
    char* menuString; /*the string for the menu output, depends on mode*/
    Game* curGame; /*stores the current game in play*/
    
    menuString = (char*)malloc(512*sizeof(char));
    menuString = "\n1: Start new game\n2: View the settings of the game\n3: Edit settings\n4: Exit the application\n";
    
    /*welcome message*/
    printf("==================================================\n");
    printf("||WELCOME TO THE ULTIMATE TIC-TAC-TOE EXPERIENCE||\n");
    printf("==================================================\n");
 
    while (menu != 4) /*while user hasn't selected exit*/
    {
        /*input the user's menu selection with validation*/
        menu = inputInt(1, 6, menuString); 
        if (menu == 1)
        {
			int menu2;
			printf("1: Player 1 vs. Player 2\nPlayer 2 vs. Computer\n\n");
			if (menu2 == 1) {
            	/*create a P1 vs. P2 game with the current settings*/
            	curGame = createGame(m, n, k, 0);
	 		} else {
				curGame	= createGame(m, n, k, 1);
			}

            /*run the new game until completion (includes freeing of game struct)*/
            runGame(curGame);
        }
        else if (menu == 2)
        {
            printf("\nSETTINGS:\n\tRows = %d\n\tColumns = %d\n\tWin = %d\n", m, n, k);
        }
        else if (menu == 3)
        {
            /*if we're in editor mode allow for values to be changed dynamically*/
            int exit = FALSE;
            printf("Enter the new settings in form <rows> <cols> <win> (Eg: 5 5 3)\n");
            while (exit == FALSE)
            {
                exit = FALSE;
                
                /*keep giving prompt until user inputs in correct format*/
                while (scanf("%d %d %d", &m, &n, &k) != 3)
                {
                    printf("Invalid: Please enter settings in the form <rows> <cols> <win> (EG: 5 5 3)");
                }

                /*checking for a variety of conditions that would be invalid*/
                if (!(validateDimension(m) && validateDimension(n) && validateDimension(k)))
                {
                    printf("Invalid: each dimension must be from 1-26\n");
                }
                else if ((k > m) && (k > n))
                {
                    printf("Invalid: k  must be greater than m and n\n");
                }
                else
                {
                    exit = TRUE;
                }
            }
        }
    }

    free(menuString);

    /*exit message*/
    printf("\nThank you for using the TicTacToe program, goodbye\n"); 
}



