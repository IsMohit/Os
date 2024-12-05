#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int r, hp, req[50], s, i, j;
    char cont;

    do {
        s = 0;

        // Input
        printf("Enter the size of the request queue: ");
        scanf("%d", &r);

        printf("Enter the request queue: ");
        for (i = 0; i < r; i++) {
            scanf("%d", &req[i]);
        }

        printf("Enter the initial head position: ");
        scanf("%d", &hp);

        printf("\nChoose the Disk Scheduling Algorithm:\n");
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. CSCAN\n");
        int ch;
        scanf("%d", &ch);

        if (ch == 1) {
            // FCFS
            printf("\nSequence: %d -> ", hp);
            for (i = 0; i < r; i++) {
                printf("%d -> ", req[i]);
                s += abs(hp - req[i]);
                hp = req[i];
            }
        } else if (ch == 2) {
            // SSTF
            int completed[50] = {0};
            printf("\nSequence: %d -> ", hp);
            for (i = 0; i < r; i++) {
                int min = 9999, pos = -1;
                for (j = 0; j < r; j++) {
                    if (!completed[j] && abs(hp - req[j]) < min) {
                        min = abs(hp - req[j]);
                        pos = j;
                    }
                }
                completed[pos] = 1;
                s += abs(hp - req[pos]);
                hp = req[pos];
                printf("%d -> ", req[pos]);
            }
        } else if (ch == 3 || ch == 4) {
            // SCAN and CSCAN
            int left[50], right[50], l = 0, r1 = 0;

            for (i = 0; i < r; i++) {
                if (req[i] < hp)
                    left[l++] = req[i];
                else
                    right[r1++] = req[i];
            }
            sort(left, l);
            sort(right, r1);

            printf("\nSequence: %d -> ", hp);

            if (ch == 3) { // SCAN
                for (i = 0; i < r1; i++) {
                    printf("%d -> ", right[i]);
                    s += abs(hp - right[i]);
                    hp = right[i];
                }
                for (i = l - 1; i >= 0; i--) {
                    printf("%d -> ", left[i]);
                    s += abs(hp - left[i]);
                    hp = left[i];
                }
            } else { // CSCAN
                for (i = 0; i < r1; i++) {
                    printf("%d -> ", right[i]);
                    s += abs(hp - right[i]);
                    hp = right[i];
                }
                s += abs(hp - 0);
                printf("0 -> ");
                hp = 0;
                for (i = 0; i < l; i++) {
                    printf("%d -> ", left[i]);
                    s += abs(hp - left[i]);
                    hp = left[i];
                }
            }
        } else {
            printf("Invalid choice!\n");
            continue;
        }

        printf("\nTotal seek time: %d\n", s);

        // Continue or exit
        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y');

    printf("\nExiting program. Goodbye!\n");
    return 0;
}
