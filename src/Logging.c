/* File: Logging.c
 * Author: Liam Ryan
 * Date Created: 03/10/19
 * Last Modified: 16/10/19
 * Purpose: controls all aspects of the program that relate to logging, including
 *  required FileIO
 */

/*Parts of this file comprise extenally-obtained code*/

#include "Logging.h"

/*creates a move struct object by using malloc and returns a pointer to this*/
Move* createMove(int inTurn, char inPlayer, int inColIdx, int inRowIdx)
{
    Move* newMove;
    newMove = (Move*)malloc(sizeof(Move));
    
    newMove->turn = inTurn;
    newMove->player = inPlayer;
    newMove->rowIdx = inRowIdx;
    newMove->colIdx = inColIdx;
    
    return newMove;
}

/*adds a move to the linked list of moves for the log*/
void addMove(LinkedList* log, int turn, char player, int colIdx, int rowIdx)
{    
    /*create a Move struct for the new move to be added to the log*/
    Move* newMove;
    
    newMove = createMove(turn, player, colIdx, rowIdx);
 
    insertLast(log, newMove);
}

/*saves the log LinkedList to a file*/
void saveLog(LinkedList* log, int m, int n, int k)
{
    ListNode* curr; /*stores the current ListNode in the linked list*/
    Move* curMove; /*stores the data (Move struct) in curr*/
    FILE* f;
    int i = 1; /*stores which game it is, game 1, game 2 etc...*/
    char fileOut[30];

    /* Based on code from Techie Delight
     * https://www.techiedelight.com/print-current-date-and-time-in-c/
     * (Accessed 14/10/19) */
    time_t now;
    struct tm* local;
    time(&now); /*obtain current time*/
    local = localtime(&now); /*convert to calendar time*/
    
    sprintf(fileOut, "MNK_%d_%d_%d_%02d-%02d_%02d-%02d.log", m, n, k, local->tm_hour, local->tm_min,
        local->tm_mday, local->tm_mon + 1);
    /* End of code based from Techie Delight */
    
    
   /*start at the head of the list*/
    f = fopen(fileOut,"w"); /*open the output file for writing*/ 
    
    
    curr = log->head;
    
    /*if the first entry is NULL then there is nothing to save*/
    if (curr == NULL)
    {
        /*did not use perror as there is not error message, will annoyingly
            print ": SUCCESS" which does not look good*/
        printf("No data currently stored in system: nothing to save\n");
    }
    else
    {
        fprintf(f, "SETTINGS:\n\tM: %d\n\tN: %d\n\tK: %d\n\n", m, n, k); 
        /*while still more moves to go*/
        while (curr != NULL)
        {
            curMove = (Move*)curr->data;
            fprintf(f, "GAME %d:\n", i);
            
            /*while still more moves to go overall AND the current game hasn't finished*/
            /*the end of a game is indicated by having a negative value for turn in a Move*/
            while ((curr != NULL) && (curMove->turn > 0))
            {
                fprintf(f, "\tTurn: %d\n\tPlayer: %c\n\tLocation: %d,%d\n\n",
                    curMove->turn, curMove->player, curMove->colIdx, curMove->rowIdx);
                
                
                curr = curr->next;
                curMove = (Move*)curr->data;    
            }
            i++;

            /*if the loop was exited becuase the game was finished skip over the 
            Move that signals that the game has been completed*/
            if (curMove->turn <= 0)
            {
                curr = curr->next;
            }
        }
        
        if (ferror(f))
        {
            perror("Error writing to file\n");
        }
        else
        {
            /*so that the user knows that the save was successful*/
            printf("Save sucessful\n");
        }
        fclose(f);
    }/*end if*/
}

/*prints the current state of the log to the terminal*/
void viewLog(LinkedList* log, int m, int n, int k)
{
    ListNode* curr; /*stores the current ListNode in the linked list*/
    Move* curMove; /*stores the data (Move struct) in curr*/
    int i = 1; /*stores which game it is, game 1, game 2 etc...*/
  
    curr = log->head; /*start at the head of linked list*/
    
    /*if the first entry is NULL then there is nothing to save*/
    if (curr == NULL)
    {
        /*did not use perror as there is not error message, will annoyingly
            print ": SUCCESS" which does not look good*/
        printf("No data currently stored in system: nothing to view\n");
    }
    else
    {
        printf("SETTINGS:\n\tM: %d\n\tN: %d\n\tK: %d\n\n", m, n, k); 
        /*while still more moves to go*/
        while (curr != NULL)
        {
            curMove = (Move*)curr->data;
            printf("GAME %d:\n", i);
            
            /*while still more moves to go overall AND the current game hasn't finished*/
            /*the end of a game is indicated by having a negative value for turn in a Move*/
            while ((curr != NULL) && (curMove->turn > 0))
            {
                printf("\tTurn: %d\n\tPlayer: %c\n\tLocation: %d,%d\n\n",
                    curMove->turn, curMove->player, curMove->colIdx, curMove->rowIdx);
                
                
                curr = curr->next;
                curMove = (Move*)curr->data;    
            }
            i++;

            /*if the loop was exited becuase the game was finished skip over the 
            Move that signals that the game has been completed*/
            if (curMove->turn <= 0)
            {
                curr = curr->next;
            }
        }    
   } 

}

/* We have a generalised version for the linked list, so to free the linked list
 * need to pass in a function that describes how to free the data (the Move object)*/
void freeData(void* game)
{
    free(game);
}   
    
        
    
       
