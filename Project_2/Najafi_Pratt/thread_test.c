//
//  thread_test.c
//  queue
//
//  Created by Jason Pratt, Darius Najafi  on 2/25/15.
//  Copyright (c) 2015 Jason Pratt. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include "threads.h"
#define SLEEP_TIME 1

TCB_t *RunQ;
int globalVar=1;

void function1(){
    int localvar=1;
    while(1){
        sleep(SLEEP_TIME);
        printf("\r\t\033[31;42m  \033[0m\t%d\t\t\033[31;41m  \033[0m\t\t\t%d ",localvar, globalVar);
	fflush(stdout);        
	localvar++;
        globalVar++;
        yield();
        sleep(SLEEP_TIME);
        printf("\r\t\033[31;42m  \033[0m\t%d\t\t\033[31;41m  \033[0m\t\t\t%d ",localvar, globalVar);
fflush(stdout);        
	localvar++;
        globalVar++;
        yield();
    }
    
}

void function2(){
    int localvar=1;
    while(1){
        sleep(SLEEP_TIME);
        printf("\r\t\033[31;41m  \033[0m\t\t\t\033[31;42m  \033[0m\t%d\t\t%d ",localvar, globalVar);
	fflush(stdout);        
	localvar++;
        globalVar++;
        yield();
        sleep(SLEEP_TIME);
        printf("\r\t\033[31;41m  \033[0m\t\t\t\033[31;42m  \033[0m\t%d\t\t%d",localvar, globalVar);
	fflush(stdout);        
	localvar++;
        globalVar++;
        yield();
    }
}



void main(){
printf("\n\n\n");
printf("\t\t\tCSE 430\n");
printf("\t\tPROJECT #2: Thread Mania\n");
printf("*********************************************************************\n");
printf("\tT1\tT1\t\tT2\tT2\t\tGlobal\n");
printf("\tActive\tcount\t\tActive\tcount\t\tcount\n");
	
    InitQueue(&RunQ);
    start_thread(function1);
    start_thread(function2);
    run();
    
        
}

/*
 Declare a global RunQ.
 
 Write a few functions with infinite loops (put a yield in each loop). Note: try to write thread functions that are meaningful, use global and local variables
 
 In main, initialize RunQ, start threads using the functions you defined using start_thread.
 
 Call run() and watch.
*/
