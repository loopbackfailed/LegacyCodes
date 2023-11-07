// 2a.c
// SYSTEM CALLS FORK, WAIT, ZOMBIE AND ORPHAN PROCESSES
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// For parent process
void bubbleSort(int arr[], int n) {
    int temp;
    int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // Mark that a swap occurred
            }
        }
        // If no two elements were swapped in this pass, the array is already sorted
        if (swapped == 0) {
            break;
        }
    }
}

// for child process
void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main(){
    int arr[25], arr1[25], n,i,temp, status;
    printf("Enter number of elements:- ");
    scanf("%d",&n);
    printf("\nEnter the array elements");
    for(i =0; i < n; i++ ){
        scanf("%d", &temp);
        arr[i] = temp;
        arr1[i] = temp;
    }
    int pid = fork();
    if(pid == 0){
        // child
        printf("This is child process using selection sort");
        sleep(10); //simulate a delay
        printf("\nElements Sorted Using selection Sort");
        printf("\n");
        selectionSort(arr1, n);
        for(i=0;i<n;i++){
            printf("%d,",arr[i]);
        }
        printf("\nchild process id=%d\n",getpid());
    }
    else{
        // parent
        // printf("orphan state demo");
        // exit(0);
        printf("\nThis is parent process using bubble sort");
        printf("\nElements Sorted Using bubble Sort");
        // printf("Zombie state demo");
        // sleep(10);
        bubbleSort(arr,n);
        printf("\n");
        for(i=0;i<n;i++){
            printf("%d,",arr[i]);
        }
        printf("\nparent process id=%d\n",getppid());
        printf("Parent process is waiting for the child to finish...\n");
        wait(NULL);
        printf("Child process has finished.\n");
    }
    
    return 0;
}