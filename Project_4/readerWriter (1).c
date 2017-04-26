//
//  readerWriter.c
//
//
//  Created by Jason Pratt, Darius Najafi on 4/1/15.
//
//

#include <stdio.h>

#include "sem.h"
#include <stdio.h>
#include <unistd.h>

struct semaphore Sreader, Swriter, mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0, threadCount=0;

void reader_entry(int thread)
{
    printf(" reader %d at entry\n", thread);
    P(&mutex);
    if (wwc > 0 || wc > 0)
    {
        printf("read thread %d blocked\n", thread);
        rwc++;
        V(&mutex);
        P(&Sreader);

        rwc--;
    }
    rc++;
    if (rwc > 0)
        V(&Sreader);
    else
    {
        V(&mutex);
    }
}

void reader_exit(int thread)
{
    P(&mutex);
    rc--;
    if (rc == 0 && wwc > 0)
    {
        V(&Swriter);
    }
else
    {
        V(&mutex);
    }
}

void writer_entry(int thread)
{
    printf("Writer thread %d at entry point\n",thread);
    P(&mutex);
    if (rc > 0 || wc > 0)
    {
        printf("write thread: %d blocked.\n", thread);
        wwc++;
        V(&mutex);
        P(&Swriter);

        wwc--;
    }
    wc++;
    V(&mutex);
}

void writer_exit(int thread)
{
printf("write thread %d is in exit\n\n", thread);
    P(&mutex);
    wc--;

    if (rwc > 0)
    {
        V(&Sreader);
    }
else if (wwc > 0)
    {
        V(&Swriter);
    }
else
    {
        V(&mutex);
    }
}

void reader(void)
{
    P(&mutex);
    int thread = threadCount++;
    V(&mutex);
printf("read thread %d started\n\n",thread);
    while(1)
    {

        reader_entry(thread);
        printf("Thread %d is reading\n\n", thread);
        sleep(2);
        reader_exit(thread);
    };
}

void writer(void)
{

    P(&mutex);
    int thread = threadCount++;
    V(&mutex);
printf("write thread %d start\n", thread);
    while(1)
    {
        writer_entry(thread);
        printf("write thread: %d is writing\n\n", thread);
        sleep(2);
        writer_exit(thread);
    };
}




//-------------------------------------------------------

int main()
{
printf("**************************************************");
    int readers = 4;
    int writers = 2;
    int i;
   InitSem(&Swriter,0);
   InitSem(&Sreader,0);
   InitSem(&mutex,1);



    for(i = 0; i < writers; i++)
        start_thread(writer);

for(i = 0; i < readers; i++)
        start_thread(reader);


   run();
    while (1) sleep(1);
}
