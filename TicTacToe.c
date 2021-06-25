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
    
    if (argc > 2) {
        perror("Please enter the name of the settings file as CLA");
    } else if (argc == 2) { /*settings file specified*/
        readFailure = loadSettings(argv[1], &m, &n, &k);

        if(readFailure == FALSE) { /*the setttings file is "all-clear"*/
            menu(m, n, k); /*run the menu with the settings*/
        } 
    } else if (argc == 1) { /*no settings file specified*/
		menu(3, 3, 3); /*default game*/
	}
    return 0;
} 



