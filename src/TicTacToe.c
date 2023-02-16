/* File: TicTacToe.c
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 01/10/19
 * Last Modified: 21/10/19
 * Purpose: holds the main method for the TicTacToe program, handles all UI
 */

#include "TicTacToe.h"

int main (int argc, char* argv[])
{
    int readFailure; /*receives whether settings have read successfully or not*/
    int m, n, k; /*the settings of the game: rows, columns and win condition*/
    
    if (argc != 2)
    {
        fprintf(stderr, "The program must import the filename of the settings file\n");
    }
    else
    {
        readFailure = loadSettings(argv[1], &m, &n, &k);

        if(readFailure == FALSE)/*the setttings file is "all-clear"*/
        {
            menu(m, n, k); /*run the menu with the settings*/
        } 

    }
    return 0;
} 



