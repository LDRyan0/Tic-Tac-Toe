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
    int menu; /*holds the menu selection from the user*/
    menu = 1;
    char* menuString; /*the string for the menu output, depends on mode*/
    Game* curGame; /*stores the current game in play*/

    /*the linked list to store all of the logs of the games*/
    LinkedList* log = createLinkedList();
    
    menuString = (char*)malloc(512*sizeof(char));
    
    /*creates the string for the menu output based on what mode/s the program is in*/   
    makeMenuString(menuString);

    /*welcome message*/
    printf("\n");
    printf("==============================================\n");
    printf("WELCOME TO THE ULTIMATE TIC-TAC-TOE EXPERIENCE\n");

    Game* egGame;
    egGame = createGame(4,4,3);

    srand(time(NULL));
    int i,j;
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            egGame->board[i][j] = (rand() % 4) % 3; 
        }
    }

    displayGame(egGame);
    freeGame(egGame);
    
    printf("==============================================\n");

    while (menu != 6) /*while user hasn't selected exit*/
    {
        /*input the user's menu selection with validation*/
        menu = inputInt(1, 6, menuString); 
        if (menu == 1)
        {
            /*create a new game with the current settings*/
            curGame = createGame(m, n, k);           

            /*run the new game until completion (includes freeing of game struct)*/
            runGame(curGame, log);
        }
        else if (menu == 2)
        {
            printf("Rows = %d\nColumns = %d\nWin = %d\n", m, n, k);
        }
        else if (menu == 3)
        {
            viewLog(log, m, n, k); 
        }
        else if (menu == 4)
        {
            /*if we're not in secret mode then allow saving of logs*/ 
            #ifndef SECRET   
            saveLog(log, m, n, k);
            #endif
        }
        else if (menu == 5)
        {
            /*if we're in editor mode allow for values to be changed dynamically*/
            #ifdef EDITOR
            int exit = FALSE;
            printf("Enter the new settings in form <m> <n> <k> (Eg: 5 5 3)\n");
            while (exit == FALSE)
            {
                exit = FALSE;
                
                /*keep giving prompt until user inputs in correct format*/
                while (scanf("%d %d %d", &m, &n, &k) != 3)
                {
                    printf("Invalid: Please enter settings in the form <m> <n> <k> (EG: 5 5 3)");
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
            #endif
        }
    }

    /*freeing*/
    freeLinkedList(log, &freeData);
    free(menuString);

    /*exit message*/
    printf("\nThank you for using the TicTacToe program, goodbye\n"); 
}

/*  - exports the string for the menu prompt based off what mode/s program is in
 *  - I seperated this into its own method to reduce size of menu */
void makeMenuString(char* menuString)
{    
    strcpy(menuString, "\n1: Start a new game\n2: View the settings of the game\n3: View the current logs\n");
    #ifndef SECRET
    strcat(menuString, "4: Save the logs to a file\n");
    #endif
    #ifdef EDITOR
    strcat(menuString, "5: Edit settings\n");
    #endif
    strcat(menuString, "6: Exit the application\n\n");
}


