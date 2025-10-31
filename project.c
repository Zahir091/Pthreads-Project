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


struct Task tasks[5]; // Array to hold tasks, 5 maximum
int numOfTasks = 0; // Number of tasks counter

/* Function declartion for scheduling algorithms */
void *fcfs(void, *param); 
void *sjf(void *param);
void *priority_Scheduling(void *param);

/* Function to read tasks from a file */
void readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    // Countries Reading from file until 4 inputs are read
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
    srand(time(NULL)); //  random number generation using time for complete randomness
    readFile("tasks.txt"); //Reading for our input file

    //Declaring and creating the threads for each scheduling algorithm
    pthread_t t1, t2, t3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&t1, &attr, fcfs, NULL);
    pthread_create(&t2, &attr, sjf, NULL);
    pthread_create(&t3, &attr, priority_Scheduling, NULL);

    //Making sure it waits for all threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}

void *fcfs(void *param) {
    int waitingTime[5]; //Holds waiting times for each task
    int turnaroundTime[5]; //Holds turnaround times for each task
    int totalWaiting = 0, TotalTurnaroundTime = 0;

    waitingTime[0] = 0; //Waiting time for first task is 0
    
    //Caculating waiting time for each task afterwards
    for(int i=1; i < numOfTasks; i++) {
        waitingTime[i] = tasks[i-1].burstTime + waitingTime[i-1];
    }

    //Calculating turnaround time for each task 
    for(int i=0; i < numOfTasks; i++) {
        turnaroundTime[i] = tasks[i].burstTime + waitingTime[i];
    }

    //Printing the Gnatt Chard
    printf("\n--- FCFS Scheduling ---\n");
    printf("Gnatt Chart: ");
    for(int i=0; i < numOfTasks; i++) {
        printf("[T%d]", tasks[i].taskID); //Printing for each task
    }
    printf("\n"); //New Line

    //Loop through tasks again and find Total Waiting and Turnaround times
    for(int i=0; i<numOfTasks; i++) {
        printf("Task %d: Waiting = %d, Turnaround = %d\n", 
            tasks[i].taskID, waitingTime[i], turnaroundTime[i]);
        totalWaiting += waitingTime[i]; //Adding the wait times into total
        TotalTurnaroundTime += turnaroundTime[i]; //Adding the turnaround times into total
    }

     //Calculating average waiting time/turnaround time and rounding
    printf("Average Waiting Time: %.2f\n", (float)totalWaiting/numOfTasks);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround/numOfTasks);
    pthread_exit(0);
}

