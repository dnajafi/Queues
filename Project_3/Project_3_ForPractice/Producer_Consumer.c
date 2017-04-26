#include <stdio.h>
#include "sem.h"
#include <stdio.h>
#include <unistd.h>

semaphore mutex, empty, full;

int buffer_size = 5;
int produced = 0,  consumed = 0;
int in = 0, out = 0;

struct items{
    int count;
};

struct items item;

struct items buffer[buffer_size];



void producer()
{
    while(1)
    {

        P(&empty);

        P(&mutex);

        produced++;

        item.count = produced;

        buffer[in] = item;

        in = (in+1)%buffer_size;

        sleep(1);

        printf("Producer critical section : produced item number: %d\n\n",item.count);


        V(&mutex);

        V(&full);
    }
}

void consumer()
{
    while(1)
    {

        P(&full);

        P(&mutex);

        consumed++;

        item = buffer[out];

        out = (out+1)%5;

        sleep(1);

         printf("Consumer Critical Section: consumed item number %d\n\n",item.count);

        V(&mutex);

        V(&empty);
    }
}

int main()
{
    int number_producers = 2;
    int number_consumers = 2;

    InitSem(&mutex, 1);
    InitSem(&empty, buffer_size);
    InitSem(&full, 0);

    for(int i=0; i<number_producers; i++)
    {
        start_thread(producer);
    }

    for(int i=0; i<number_consumers; i++)
    {
        start_thread(consumer);
    }

    run();


}