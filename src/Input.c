/* File: Input.c
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 02/10/19
 * Last Modified: 02/10/19
 * Purpose: holds the generalised methods for inputting data types with
 *  validation/error checking
 */

#include "Input.h"

/* - takes in a minimum value, a maximum value and a message/prompt for the integer
 * - ASSERTION: returns an integer value between the min and max
 *      - includes trapping for characters/strings */
int inputInt(int min, int max, char* message)
{
    int integer = min - 1;
    char string[128];
    
    printf("%s", message);
    scanf("%s", string);
    integer = atoi(string);

    while ((integer < min) || (integer > max))
    {
        printf("Invalid value\n");
        printf("%s", message);
        scanf("%s", string);
        integer = atoi(string);
    }
    return integer;  
}

/* - takes in a minimum value, a maximum value and a message/prompt
 * - ASSERTION: returns an uppercase character between the min and max NON-CASE SENSITIVE
 *      - if between 'A' and 'F' then 'b' will be allowed, will be returned as 'B'
 */
char inputChar(char min, char max, char* message)
{
    char character = min - 1;
    char string[128];
    
    printf("%s", message);
    scanf("%s", string);
    character = string[0];
    
    /*if it's a lowercase letter convert it to uppercase*/
    if ((character >= min + 32) && (character <= max + 32))
    {
        character = character - 32;
    }
    
    while ((character < min) || (character > max) || (string[1] != 0))
    {
        printf("Invalid value\n");
        printf("%s", message);
        scanf("%s", string); 
        character = string[0];
   
        /*if it's a lowercase letter convert it to uppercase*/
        if ((character >= min + 32) && (character <= max + 32))
        {
            character = character - 32;
        }
    }
    return character;  
}    

/* - converts a character to uppercase if not already
 * - modified version of a string toUppercase method created ini
 *      Practical 4 of UCP by Liam Ryan */
char toUppercase(char character)
{
    if ((character >= 'a') && (character < 'z')) /*if lowercase*/
    {
        character = character - 32; /*converts to uppercase using ASCII standard*/   
    }
    return character;
}
