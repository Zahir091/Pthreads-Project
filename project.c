#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


typedef struct {
    char name[10];
    int burstTime;
    int priority;
    int arrivalTime;
}
