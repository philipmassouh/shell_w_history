/* Philip Massouh */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "globals.h"
#include "io.h"

int main(void) {
    int i;

    printf("Clearing histBuffer \n");
    
    printf("Populating histBuffer with 1-5\n");
    strcpy(histBuffer[0], "one\n");
    strcpy(histBuffer[1], "two\n");
    strcpy(histBuffer[2], "three\n");
    strcpy(histBuffer[3], "four\n");
    strcpy(histBuffer[4], "five\n");
    printf("Writing histBuffer into file.\n");
    write_history(5);

    printf("Clearing histBuffer\n");
    strcpy(histBuffer[0], "");
    strcpy(histBuffer[1], "");
    strcpy(histBuffer[2], "");
    strcpy(histBuffer[3], "");
    strcpy(histBuffer[4], "");

    printf("Reading file into histBuffer\n");
    read_history();

    printf("Printing histBuffer\n");
    for (i = 0; i < 5; i++) {
        printf("%s\n", histBuffer[i]);
    }

    return 0;
}