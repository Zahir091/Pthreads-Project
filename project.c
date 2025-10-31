#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

/*This is the definiton for each task to identify info about them*/
struct Task{
    int taskID;
    int burstTime;
    int priority;
    int arrivalTime;
};


struct Task tasks[5]; // Array to hold tasks
int numOfTasks = 0; // Number of tasks

void *fcfs(void, *param);
void *sjf(void *param);
void *priority_Scheduling(void *param);

void readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    while(fscanf(fp, "%d %d %d %d", 
        &tasks[numOfTasks].taskID, 
        &tasks[numOfTasks].burstTime, 
        &tasks[numOfTasks].priority, 
        &tasks[numOfTasks].arrivalTime) == 4) {
        numOfTasks++;
    }
    fclose(fp);
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    readFile("tasks.txt");

    pthread_t t1, t2, t3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&t1, &attr, fcfs, NULL);
    pthread_create(&t2, &attr, sjf, NULL);
    pthread_create(&t3, &attr, priority_Scheduling, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}


