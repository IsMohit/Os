#include <stdio.h>

// Function prototypes
void fifo(int n, int str[], int nf);
void lru(int n, int str[], int nf);

int main() {
    int i, n, str[50], nf, choice;
    char cont; // Variable to store the user's choice to continue or not

    do {
        // Input the length of the reference string
        printf("\nEnter the length of reference string:\n");
        scanf("%d", &n);

        // Input the page numbers string
        printf("\nEnter the page numbers string:\n");
        for (i = 1; i <= n; i++)
            scanf("%d", &str[i]);

        // Input the number of frames
        printf("\nEnter the number of frames: ");
        scanf("%d", &nf);

        // Choose the page replacement algorithm
        printf("Choose the Page Replacement Algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(n, str, nf);
                break;

            case 2:
                lru(n, str, nf);
                break;

            default:
                printf("Invalid choice\n");
        }

        // Ask the user if they want to continue
        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y'); // Repeat if the user enters 'y' or 'Y'

    printf("\nExiting program. Goodbye!\n");
    return 0;
}

// FIFO Page Replacement Algorithm
void fifo(int n, int str[], int nf) {
    int i, j = 0, k, frame[nf], flag, hit = 0, fault = 0;

    // Initialize frame array
    for (i = 0; i < nf; i++)
        frame[i] = -1;

    printf("\tRef String\tPage Frames\n");
    for (i = 1; i <= n; i++) {
        printf("%d\t\t", str[i]);
        flag = 0;
        for (k = 0; k < nf; k++) {
            if (frame[k] == str[i]) {
                flag = 1;
                hit++;
                break;
            }
        }
        if (flag == 0) {
            frame[j] = str[i];
            j = (j + 1) % nf;
            fault++;
        }

        // Display current page frames
        for (k = 0; k < nf; k++) {
            printf("%d\t", frame[k]);
        }
        printf("\n");
    }
    printf("Page Faults: %d\n", fault);
    printf("Page Hits: %d\n", hit);
}

// LRU Page Replacement Algorithm
void lru(int n, int str[], int nf) {
    int i, k, timer = 1, time[5], pos = 0, min = 0, frame[nf], hit = 0, fault = 0;

    // Initialize frame and time arrays
    for (k = 0; k < nf; k++) {
        frame[k] = -1;
        time[k] = 0;
    }

    for (i = 1; i <= n; i++) {
        int flag = 0;
        for (k = 0; k < nf; k++) {
            if (str[i] == frame[k]) { // page found
                flag = 1;
                time[k] = timer;
                timer++;
                hit++; // Increment page hit count
                break;
            }
        }

        if (flag == 0) { // page not found
            fault++;
            // Increment page fault count
            int min_time = time[0];
            pos = 0;
            for (k = 1; k < nf; k++) {
                if (time[k] < min_time) {
                    min_time = time[k];
                    pos = k;
                }
            }
            frame[pos] = str[i];
            time[pos] = timer;
            timer++;
        }

        // Display current page frames
        printf("%d\t\t", str[i]);
        for (k = 0; k < nf; k++) {
            printf("%d\t", frame[k]);
        }
        printf("\n");
    }

    printf("Number of Page Faults: %d\n", fault);
    printf("Number of Page Hits: %d\n", hit);
}
