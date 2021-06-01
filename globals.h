#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
#define MAX_HISTORY 10
#define FILENAME "./massouh.3.history"

char histBuffer[MAX_HISTORY][MAX_LINE]; 
int bufferFill, historyRequested;
