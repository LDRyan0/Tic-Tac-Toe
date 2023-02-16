/* File: Settings.c
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 01/10/19
 * Last Modified: 16/10/19
 * Purpose: Handles all I/O and error checking for the settings of the TicTacToe program
 */

#include "Settings.h"

/* - loads the settings from a given file name into the 3 parameters: m, n and k
 * - returns true (1) if error or false (0) if no error*/
int loadSettings(char* fileName, int* m, int* n, int* k)
{
    FILE * settingsFile; /*pointer to the settings file*/
    char character, upper, equals;
    int* tempPtr; /*stores the value of the current dimension "in question"*/
    
    int error = FALSE; /*keeps track of whether an error has occured*/
    int mcount = 0, ncount = 0, kcount = 0; /*allows for checking of duplicate settings*/
    int dimension; /*stores the integer number to be assigned to m, n, or k*/
    
    /*initialising all dimensions to 0*/
    *m = 0;
    *n = 0;
    *n = 0; 

    /*opneing the settings file*/
    settingsFile = fopen(fileName, "r");

    if (settingsFile == NULL) /*checking that the file exists*/
    {
        perror("The stated settings file does not exist");
    }
    else
    {
        character = fgetc(settingsFile); /*get the first character in the file*/
        while ((error == FALSE) && (character != EOF))
        {
            /*convert character to uppercase, allows for case insensitivty*/
            upper = toUppercase(character);
            if (upper == 'M')
            {
                tempPtr = m;  
                mcount++;
            }
            else if (upper == 'N')
            {
                tempPtr = n;
                ncount++;
            }
            else if (upper == 'K')
            {
                tempPtr = k;
                kcount++;
            }
            else /*if not m, n or k*/
            {
                perror("ERROR: file contains an invalid dimension - valid dimensions are m, n or k");
                error = TRUE;
            }
            
            /*checking for duplicated settings, only one entry for each allowed*/ 
            if ((mcount > 1) || (ncount > 1) || (kcount > 1))
            {
                perror("ERROR: cannot have duplicated settings"); 
                error = TRUE;
            }
           
            /*getting the second character in the line, should be an '='*/
            equals = getc(settingsFile); 

            /*checking that there is an equals sign*/
            if (equals != '=')
            {
                perror("ERROR: each line must be in form <character>=<integer> eg: M=4"); 
                error = TRUE;
            }
            
            /*scanning in the value for the dimension, must be an integer*/
            if(fscanf(settingsFile, "%d\n", &dimension) != 1)
            {
                perror("ERROR: the dimension value must be a valid integer");
                error = TRUE;
            }
    
            /*checking that the dimension is from 1-26*/
            if (validateDimension(dimension) == FALSE)
            {
                perror("ERROR: all dimensions must be from 1-26");
                error = TRUE;                 
            }
            else
            {
                /*set the m, n or k to this value*/
                *tempPtr = dimension;
            }

            character = fgetc(settingsFile); /*get the next character*/
        }
    }

    /*checking that k is not greater than both m and n*/
    if ((*k > *m) && (*k > *n))
    {
        perror("ERROR: the k value must be less than or equal to at least one dimension");
        error = TRUE;
    } 

    /*checking for one of each*/         
    if ((mcount != 1) || (ncount != 1) || (kcount != 1))
    {
        perror("ERROR: the file must have one entry for m, n and k");
        error = TRUE;
    }

    fclose(settingsFile);

    return error;              
}

/* - validates a dimension specified in the settings file: must be greater than 0*
 * - returns TRUE (1) if valid and FALSE (0) if invalid*/
int validateDimension(int dimension)
{
    return ((dimension > 0) && (dimension < 27)); /*< 27 for the A-Z formatting*/
}















   
