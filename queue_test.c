/* Philip Massouh */

#include "queue.h"
#include "globals.h"
#include <stdio.h>

int main() {
    int i;

    bufferFill = 0;
    
    enqueue("adam");
    enqueue("brenda");
    enqueue("cameron");
    enqueue("daniel");
    enqueue("elizabeth");
    enqueue("frank");
    enqueue("gary");
    enqueue("helena");
    enqueue("ian");
    enqueue("jacob");

    for (i = 0; i < bufferFill; i++) {
            printf("%s\n", histBuffer[i]);
    }

    return 0;
}