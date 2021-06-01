#include "globals.h"
#include <string.h>

/* 
    Inserts an item at the end of the list and updates the counter.
*/
int enqueue(char arg[]) {
    if (bufferFill >= MAX_HISTORY) return 0;

    strcpy(histBuffer[bufferFill], arg);
    bufferFill++;
    return 1;
}



/* 
    Removes the item at the front of the list and updates the counter.
*/
int dequeue() {
    int i;
    if (bufferFill < 1) return 0;

    bufferFill--;
    
    for (i = 1; i < bufferFill; i++) {
        strcpy(histBuffer[i-1], histBuffer[i]);
    }
          
    return 1;
}