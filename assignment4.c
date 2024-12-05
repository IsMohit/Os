 #include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 101

typedef struct {
    int id;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
    int ct;  // Completion Time
} Process;

void printDetails(Process p[], int n);
void FCFS(Process p[], int n);
void SJF(Process p[], int n);
void RR(Process p[], int n, int q);

void calculateAvgTimes(Process p[], int n) {
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.3f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.3f\n", (float)total_tat / n);
}

void printDetails(Process p[], int n) {
    printf("\nProcess ID | Arrival Time | Burst Time | Completion Time | Turn Around Time  | Waiting Time\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("    %d       |      %d       |     %d      |        %d        |       %d       |       %d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

void FCFS(Process p[], int n) {
    int ct = 0;

    for (int i = 0; i < n; i++) {
        if (ct < p[i].at) {
            ct = p[i].at;
        }
        p[i].ct = ct + p[i].bt;
        p[i].wt = ct - p[i].at;
        p[i].tat = p[i].ct - p[i].at;
        ct = p[i].ct;
    }

    printDetails(p, n);
    calculateAvgTimes(p, n);
}

void SJF(Process p[], int n) {
    Process temp;
    int ct = 0;
    int completed = 0;
    int i, j;

    // Sort processes based on arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    while (completed < n) {
        int idx = -1;
        int min_bt = __INT_MAX__;  // Initialize with a large value
        for (i = 0; i < n; i++) {
            // Find the process with the smallest burst time that has arrived and is not yet completed
            if (p[i].at <= ct && p[i].ct == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].ct = ct + p[idx].bt;
            p[idx].wt = ct - p[idx].at;
            p[idx].tat = p[idx].ct - p[idx].at;
            ct += p[idx].bt;
            completed++;
        } else {
            ct++;
        }
    }

    printDetails(p, n);
    calculateAvgTimes(p, n);
}

void RR(Process p[], int n, int q) {
    int rb[MAX_PROCESSES];
    int ct = 0;
    int completed = 0;
    int i;

    for (i = 0; i < n; i++) {
        rb[i] = p[i].bt;
        p[i].wt = 0;
        p[i].ct = 0;
    }

    while (completed < n) {
        int done = 0;
        for (i = 0; i < n; i++) {
            if (p[i].at <= ct && rb[i] > 0) {
                done = 1;
                if (rb[i] > q) {
                    rb[i] -= q;
                    ct += q;
                } else {
                    ct += rb[i];
                    p[i].ct = ct;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    rb[i] = 0;
                    completed++;
                }
            }
        }
        if (!done) {
            ct++;
        }
    }

    printDetails(p, n);
    calculateAvgTimes(p, n);
}

int main() {
    int n, choice, q;
    char continue_choice;
    Process p[MAX_PROCESSES];

    do {
        printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
        scanf("%d", &n);

        if (n > MAX_PROCESSES) {
            printf("Error: Number of processes exceeds the maximum allowed.\n");
            return 1;
        }

        for (int i = 0; i < n; i++) {
            p[i].id = i;
            printf("Enter arrival time and burst time for process %d: ", i);
            scanf("%d %d", &p[i].at, &p[i].bt);
            p[i].wt = 0;
            p[i].tat = 0;
            p[i].ct = 0;
        }

        printf("Choose Scheduling Algorithm:\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. RR\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS(p, n);
                break;
            case 2:
                SJF(p, n);
                break;
            case 3:
                printf("Enter time quantum for RR: ");
                scanf("%d", &q);
                RR(p, n, q);
                break;
            default:
                printf("Invalid choice!\n");
                return 1;
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continue_choice);  // Note: the space before %c is to consume any leftover whitespace
    } while (continue_choice == 'y' || continue_choice == 'Y');

    return 0;
}
