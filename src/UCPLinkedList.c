/*
FILE: UCPLinkedList.c
PROGRAM: UCPLinkedList
AUTHOR: Liam Ryan 
ID: 19769811
DATE CREATED: 25/09/2019
PURPOSE: generic linked list

REFERENCE: This file was entirely created in Practical 7 of UCP by Liam Ryan

*/

#include "UCPLinkedList.h"

LinkedList* createLinkedList()
{
    LinkedList* list;

    list = (LinkedList*)malloc(sizeof(LinkedList));

    (*list).head = NULL;
    (*list).tail = NULL;
    return list;   
}

ListNode* createListNode()
{
    ListNode* node;

    node = (ListNode*)malloc(sizeof(ListNode));
    
    (*node).data = NULL;
    (*node).next = NULL;
    (*node).prev = NULL;
    return node;
}

int isEmpty(LinkedList* list)
{
    return ((*list).head == NULL);
}

void insertFirst(LinkedList* list, void* newData)
{
    ListNode* newNode = createListNode();
    (*newNode).data = newData;
    
    if (isEmpty(list))
    {
        (*list).head = newNode;
        (*list).tail = newNode;
    }
    else
    {
        (*newNode).next = (*list).head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void* removeFirst(LinkedList* list)
{
    void* value;
    ListNode* temp;

    if (isEmpty(list))
    {
        perror("Unable to remove first: empty linked list");
    }
    if (list->head->next == NULL)
    {
    
        temp = list->head;
        
        value = list->head->data;

        list->head = NULL;
        list->head = NULL; 

        free(temp); 
    }
    else
    {
        temp = list->head;
        
        value = list->head->data;

        list->head = list->head->next;
        list->head->prev = NULL; 

        free(temp); 
    } 
    return value;
}

void* peekFirst(LinkedList* list)
{
    if (isEmpty(list))
    {
        perror("Unable to peek first: empty linked list");
    }
    return list->tail->data;
}

void insertLast(LinkedList* list, void* newData)
{
    ListNode* newNode = createListNode();
    (*newNode).data = newData;
    
    if (isEmpty(list))
    {
        (*list).head = newNode;
        (*list).tail = newNode;
    }
    else
    {
        (*newNode).prev = (*list).tail;
        list->tail->next = newNode;
        (*list).tail = newNode;
    }
}

void* removeLast(LinkedList* list)
{
    void* value = NULL;
    ListNode* temp;  

    if (isEmpty(list))
    {
        perror("Unable to remove last: empty linked list");
    }
    else if (list->head->next == NULL) /*only one value*/
    {
        temp = list->tail;   
        value = list->tail->data;
        
        list->tail = NULL;
        list->head = NULL;

        free(temp); 
    }
    else
    {
        temp = list->tail; 
        value = list->tail->data;
        
        list->tail = list->tail->prev;
        list->tail->next = NULL;

        free(temp);
    }
    return value;
}

void* peekLast(LinkedList* list)
{
    if (isEmpty(list))
    {
        perror("Unable to peek first: empty linked list");
    }
    return list->tail->data;
}

void printLinkedList(LinkedList* list, printFuncPtr printFunc)
{

    ListNode *node, *nextNode;
    
    node = (*list).head;
    
    while(node != NULL)
    {
        nextNode = (*node).next;
        (*printFunc)(node->data);
        node = nextNode; 
    }

}

void freeLinkedList(LinkedList* list, freeFuncPtr freeFunc)
{
    ListNode *node, *nextNode;
    
    node = (*list).head;
    
    while(node != NULL)
    {
        nextNode = (*node).next;
        (*freeFunc)(node->data); /*freeing the data using the specified function*/
        free(node);
        node = nextNode;
    }
    
    free(list);
}
