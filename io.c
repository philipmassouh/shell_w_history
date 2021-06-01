/* Philip Massouh */

#include "globals.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Clears FILENAME and writes histBuffer to it  */
void write_history(int numCommands) {
    int i;
    int fd = open("./massouh.3.history", O_CREAT | O_TRUNC |  O_RDWR ,0666);

    for (i = 0; i < numCommands; i++) {
        write(fd,histBuffer[i],strlen(histBuffer[i]));
    }

    close(fd);
}

/* Reads FILENAME into histBuffer */
void read_history() {
    int i, j, fd, sz;
    char c;

    fd = open(FILENAME, O_RDONLY, 0666);
    if (fd == -1) exit(-1);

    i = 0;
    j = 0;
    while (read(fd, &c, 1) != 0) {
        histBuffer[j][i] = c;
        i++;
        if (c == '\n') {
            histBuffer[j][i-1] = '\0';
            j++;
            i = 0;
            bufferFill++;
        } 
    }
    close(fd);
}

/* Prints history-- this is for debugging history */
void display_history() {
    int i;
    for (i = 0; i < bufferFill; i++) {
        printf("|%s|\n", histBuffer[i]);
    }
}
