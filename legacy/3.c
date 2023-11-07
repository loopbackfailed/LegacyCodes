// 3.c
// CPU Scheduling SJF, RR
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100
#define INT_MAX 10
#define CPU_TIME_QUANTUM 2

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

void SJF_Preemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int shortest = -1;
    int shortest_time = INT_MAX;

    while(completed <n){
        // Find the process with the shortest remaining burst time

        shortest = -1;
        shortest_time = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_time && processes[i].remaining_time > 0) {
                shortest = i;
                shortest_time = processes[i].remaining_time;
            }
        }
        if (shortest == -1) {
            current_time++;}
            else{
            // Execute the process for 1 time unit (preemptive)
            processes[shortest].remaining_time--;
            if (processes[shortest].remaining_time == 0) {
                // Process completed
                completed++;
                printf("Process %d completed at time %d\n", processes[shortest].id, current_time);
            }
            current_time++;
            }

    }

}

void RoundRobin(struct Process processes[], int n, int time_quantum) {
    int remaining_time[n];
    int current_time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= time_quantum) {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    printf("Process %d completed at time %d\n", processes[i].id, current_time);
                    completed++;
                } else {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }
}

int main() {
    int n, t;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("1.SJF\n2.RR\n");
    scanf("%d", &t);
    switch (t)
    {
    case 1:
        printf("Shortest Job First (Preemptive) Scheduling:\n");
        SJF_Preemptive(processes, n);
        break;
    
    case 2:
        printf("Round Robin Scheduling:\n");
        RoundRobin(processes, n,CPU_TIME_QUANTUM);
    
    default:
        break;
    }
    return 0;
}