#include<stdio.h>
#include<stdlib.h>
#include "tcb.h"


/*
  Initializes Queue by setting head and tail pointers to NULL
*/
void InitQueue(TCB_t ** head)
{
    (*head) = NULL; //sets the pointer head to NULL since Queue is empty
}

 

/*
  Initializes new memoery for an item. Does not intialize fields of item. Only returns a pointer to that item.
*/
TCB_t  * NewItem()
{
    TCB_t  * new_item = (TCB_t *)malloc(sizeof(TCB_t ));
    
    return new_item;
}

/*
 Inserts item at head->prev(tail of Queue)
*/
void AddQueue(TCB_t  ** addr_head, TCB_t  * newItem)
{
    
    
    if(*addr_head == NULL) //Queue is empty
    {
        *addr_head = newItem; //setting head equal to newItem
        newItem->prev = newItem; //set prev equal to itself since only 1 element in Queue
        newItem->next = newItem; //set next equal to itself since only 1 element in Queue
    }
    else //there is at least 1 element in the Queue
    {
        newItem->prev = (*addr_head)->prev;
        newItem->next = (*addr_head);
        (*addr_head)->prev = newItem;
        newItem->prev->next = newItem;
    }
    
}

/*
 Deletes item at head of Queue
*/
TCB_t  * DelQueue(TCB_t  ** addr_head)
{
    if((*addr_head) == NULL) //if Queue is empty
    {
        return NULL;
    }
    else if((*addr_head) == (*addr_head)->next) //if there is only one element in Queue
    {
        TCB_t  * del_item = (*addr_head);
        (*addr_head) = NULL;
        return del_item;
    }
    else
    {
        TCB_t  * del_item = (*addr_head);
        
        (*addr_head)->next->prev = (*addr_head)->prev;
        (*addr_head)->prev->next = (*addr_head)->next;
        
        *addr_head = (*addr_head)->next;
        
        return del_item;
    }
}


/*
 Moves head pointer to point at next element in Queue
*/
void RotateQ(TCB_t  ** addr_head)
{
    if((*addr_head) == NULL) //if Queue is empty
    {
        *addr_head = NULL;
    }
    else //Queue is not empty
    {
        *addr_head = (*addr_head)->next;
    }
}


