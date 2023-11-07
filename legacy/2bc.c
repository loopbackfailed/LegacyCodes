// 2bc.c 
// child
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    printf("Child process replaced via execv call:- \n");

    for (int i = argc - 1; i > 0; i--) {
        printf("%s\n", argv[i]);
    }

    return 0;
}
