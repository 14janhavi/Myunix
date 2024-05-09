#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completed;
};

// Function to calculate waiting time and turnaround time for Priority scheduling
void priority_scheduling(struct Process processes[], int n) {
    int total_time = 0, i, j;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    // Sort processes by arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    // Execute processes
    for (i = 0; i < n; i++) {
        if (total_time < processes[i].arrival_time) {
            total_time = processes[i].arrival_time;
        }
        total_time += processes[i].burst_time;
        processes[i].turnaround_time = total_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    
    // Calculate averages
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    // Print averages
    printf("Average Waiting Time for Priority Scheduling: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time for Priority Scheduling: %.2f\n", avg_turnaround_time);
}

// Function to calculate waiting time and turnaround time for Round Robin scheduling
void round_robin_scheduling(struct Process processes[], int n, int quantum) {
    int total_time = 0, i, remaining_processes = n;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    // Execute processes
    while (remaining_processes > 0) {
        for (i = 0; i < n; i++) {
            if (processes[i].completed) continue;
            if (processes[i].remaining_time > quantum) {
                total_time += quantum;
                processes[i].remaining_time -= quantum;
            } else {
                total_time += processes[i].remaining_time;
                processes[i].waiting_time = total_time - processes[i].burst_time - processes[i].arrival_time;
                processes[i].turnaround_time = total_time - processes[i].arrival_time;
                avg_waiting_time += processes[i].waiting_time;
                avg_turnaround_time += processes[i].turnaround_time;
                processes[i].completed = 1;
                remaining_processes--;
            }
        }
    }
    
    // Calculate averages
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    // Print averages
    printf("Average Waiting Time for Round Robin Scheduling: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time for Round Robin Scheduling: %.2f\n", avg_turnaround_time);
}

// Function to print Gantt chart
void print_gantt_chart(struct Process processes[], int n) {
    int i;
    
    printf(" ");
    for (i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burst_time; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    
    for (i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burst_time - 1; j++) {
            printf(" ");
        }
        printf("P%d", processes[i].pid);
        for (int j = 0; j < processes[i].burst_time - 1; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    
    for (i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burst_time; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n, i, quantum;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input processes details
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter Priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    // Input time quantum for Round Robin
    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Perform Priority Scheduling
    priority_scheduling(processes, n);

    // Print Gantt chart for Priority Scheduling
    printf("\nGantt Chart for Priority Scheduling:\n");
    print_gantt_chart(processes, n);

    // Perform Round Robin Scheduling
    round_robin_scheduling(processes, n, quantum);

    // Print Gantt chart for Round Robin Scheduling
    printf("\nGantt Chart for Round Robin Scheduling:\n");
    print_gantt_chart(processes, n);

    return 0;
}