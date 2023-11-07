#include <stdio.h>

int main() {
    int processes, resources, i, j, k;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int allocated[processes][resources], max[processes][resources], need[processes][resources];
    int available[resources], total[resources];

    printf("Enter the allocated resources for each process:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }

    printf("Enter the maximum resources needed for each process:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    printf("Enter the total available resources:\n");
    for (i = 0; i < resources; i++) {
        scanf("%d", &total[i]);
        available[i] = total[i];
    }

    int finish[processes];
    for (i = 0; i < processes; i++) {
        finish[i] = 0;
    }

    int safe_sequence[processes], index = 0;
    int work[resources];
    for (i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < processes; i++) {
        int found = 0;
        for (j = 0; j < processes; j++) {
            if (finish[j] == 0) {
                int safe = 1;
                for (k = 0; k < resources; k++) {
                    if (need[j][k] > work[k]) {
                        safe = 0;
                        break;
                    }
                }
                if (safe) {
                    safe_sequence[index++] = j;
                    finish[j] = 1;
                    found = 1;
                    for (k = 0; k < resources; k++) {
                        work[k] += allocated[j][k];
                    }
                    break;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state. Deadlock may occur.\n");
            return 0;
        }
    }

    printf("System is in a safe state. Safe sequence is: ");
    for (i = 0; i < processes - 1; i++) {
        printf("P%d -> ", safe_sequence[i]);
    }
    printf("P%d\n", safe_sequence[processes - 1]);

    return 0;
}