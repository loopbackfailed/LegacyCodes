#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char input[100];
    int fd1, fd2;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    fd1 = open(FIFO1, O_WRONLY);
    fd2 = open(FIFO2, O_RDONLY);

    while (1) {
        printf("Enter a sentence (or 'exit' to quit): ");
        fgets(input, 100, stdin);

        write(fd1, input, strlen(input) + 1);

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        char output[100];
        read(fd2, output, 100);
        printf("Output from second process: %s\n", output);
    }

    close(fd1);
    close(fd2);
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}