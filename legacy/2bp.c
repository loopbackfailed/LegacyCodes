// 2bp.c
// parent
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// For parent process
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
        char *program = "./2bc";
        char *args[2];
        args[0] = program;
        args[1] = NULL;
        execve(program, args, NULL);
        perror("execve failed");
        exit(1);
    }
    else{
        // parent
        printf("\nparent process id=%d\n",getppid());
        printf("\nThis is parent process using selection sort");
        printf("\nElements Sorted Using selection Sort");
        selectionSort(arr,n);
        printf("\n");
        for(i=0;i<n;i++){
            printf("%d,",arr[i]);
        }
        char *program = "./2bc";
        char *args[n + 2];
        args[0] = program;
        args[n+1] =NULL;
        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(16); // Allocate space for each element
            snprintf(args[i + 1], 16, "%d", arr[i]);
        }
        execve(program, args,NULL);
        perror("execve failedddd");
        exit(1);
    }
    
    return 0;
}