#include <stdio.h>
#include "sem.h"
#include <stdio.h>
#include <unistd.h>

TCB_t * RunQ;
semaphore mutex;
int global_var = 1;


void f1()
{
    int local_var = 1;

    while(1)
    {
        P(&mutex);

        local_var++;
        global_var++;

        V(&mutex);

        printf("\nf1: local variable = %d\t", local_var);
        printf("f1: global variable = %d\n", global_var);

        sleep(1);

    }


}

void f2()
{
    int local_var=1;

    while(1)
    {
        P(&mutex);

        local_var++;
        global_var++;

        V(&mutex);

        printf("\nf2: local variable = %d\t", local_var);
        printf("f2: global variable = %d\n", global_var);

        sleep(1);

    }

}

int main()
{
    InitQueue(&RunQ);
    InitSem(&mutex,1);
    start_thread(f1);
    start_thread(f2);
    run();
}