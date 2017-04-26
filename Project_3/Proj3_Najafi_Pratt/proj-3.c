//

//  consumer producer code

//  

//

//  Created by Jason Pratt, Darius Najafi on 4/1/15.
//  

//

//


#include <stdio.h>
#include "sem.h"
#include <stdio.h>
#include <unistd.h>


struct semaphore empty, full, mutex;

int bufferSize=5, in=0, out=0;
int consumed=0;
int produced=0;

struct items{
char name[30];
int count;
};

struct items buffer[5];
struct items item; 

void producer(void)

{

while(1)
    {

//check to see if available space to produce
    P(&empty);

	 P(&mutex);
//******begin producer critical section*********
	produced++;
//update item number
	item.count=produced;
//put item in buffer	
	buffer[in]=item;
//increment to next element in buffer
	in=(in+1)%bufferSize;
	
	sleep(1);

        printf("Producer critical section : produced item number: %d\n\n",item.count);

//********end critical section******************************
        V(&mutex);
    
//increment full, ok to consume
    V(&full);
        
}
}


void consumer(void)

{

    while(1)

    {

//check to see if there are items to consume
    P(&full);

        P(&mutex);
//***********begin consumer critical section**************
	consumed++;
//pull item from buffer
	item=buffer[out];
//point to next element
    	out=(out+1)%bufferSize;
	sleep(1); 
       
        printf("Consumer Critical Section: consumed item number %d\n\n",item.count);

//****************end critical section********************
        V(&mutex);

//increment empty, ok to produce 
    V(&empty);

    }

}





//-------------------------------------------------------


int main()

{

    int producers = 2;

    int consumers = 2;

    int i;

InitSem(&empty,bufferSize);
    InitSem(&full,0);
    InitSem(&mutex,1);

    for(i = 0; i < producers; i++)

        start_thread(producer);

    

    for(i = 0; i < consumers; i++)

        start_thread(consumer);

    

    run();

    while (1) sleep(1);

}
	

	

