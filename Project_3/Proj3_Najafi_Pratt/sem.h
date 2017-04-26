#include <stdio.h>
#include "threads.h"

typedef struct semaphore{

   int value;
   TCB_t * Q;   

}semaphore;

void InitSem(semaphore * s, int value)
{
    InitQueue(&(s->Q));
  s->value = value;
    
}

void P(semaphore * s)
{
   s->value--; 

//blocking thread  
   if(s->value < 0)
   {
//remove thread from runQ
      TCB_t * temp = DelQueue(&RunQ);
//add to semaphore queue
      AddQueue(&(s->Q), temp);
//load next thread in queue
      swapcontext(&(temp->context), &(RunQ->context));
   }
}

void V(semaphore * s)
{
   s->value++;

//if there are blocked  threads
   if(s->value <= 0)
   {
//remove thread from semaphore queue
      TCB_t * temp = DelQueue(&(s->Q));
//add thread back to runQ
      AddQueue(&(RunQ), temp);
//load next thread in runQ
       yield();
	
   }

 
}
