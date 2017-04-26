//
//  threads.h
//  queue
//
//  Created by Jason Pratt on 2/25/15.
//  Copyright (c) 2015 Jason Pratt. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include "q.h"
TCB_t *RunQ;

void start_thread(void (*function)(void))
{ // begin pseudo code
   // allocate a stack (via malloc) of a certain size (choose 8192)
    //allocate a TCB (via malloc)
    //call init_TCB with appropriate arguments
  
    void *stackP = malloc(8192);
    TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));
    init_TCB (tcb,function, stackP, 8192);
    AddQueue(&RunQ, tcb);
   
    
    //call addQ to add this TCB into the “RunQ” which is a global header pointer
    //end pseudo code
}

void run()
{   // real code
    
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->context));  // start the first thread
    
}

void yield() // similar to run
{
    
    TCB_t *curr = RunQ;
    RotateQ( &RunQ);
    swapcontext(&(curr -> context), &(RunQ->context));

   // rotate the run Q;
    //swap the context, from previous thread to the thread pointed to by RunQ
}
