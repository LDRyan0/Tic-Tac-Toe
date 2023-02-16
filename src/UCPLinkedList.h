/*
FILE: UCPLinkedList.h
PROGRAM: UCPLinkedList
AUTHOR: Liam Ryan 
ID: 19769811
DATE CREATED: 25/09/2019
PURPOSE: header for UCPLinkedList.c

REFERENCE: This file was entirely created in Practical 7 of UCP by Liam Ryan

*/

#ifndef UCPLINKEDLIST_H
#define UCPLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

/*struct for a node in a linked list*/
typedef struct ListNode {
    struct ListNode* next;
    struct ListNode* prev;
    void* data;
} ListNode;

/*struct for the linked list itself:
 * - pointer to head (start)
 * - pointer to tail (end)
 */
typedef struct {
    ListNode* head;
    ListNode* tail;
} LinkedList;

/*linked list is generalised, so for freeing and print we must pass in a 
 * pointer to a function that describes how to free/print the data in the
 * specific implementation
 */
typedef void (freeFuncPtr)(void*);
typedef void (printFuncPtr)(void*);

LinkedList* createLinkedList();
void insertFirst(LinkedList* list, void* newData);
void* removeFirst(LinkedList* list);
void* peekFirst(LinkedList* list);
void insertLast(LinkedList* list, void* newData);
void* removeLast(LinkedList* list);
void* peekLast(LinkedList* list);
void printLinkedList(LinkedList* list, printFuncPtr);
void freeLinkedList(LinkedList* list, freeFuncPtr);

#endif

