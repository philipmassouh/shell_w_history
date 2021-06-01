/*
  
  Philip Massouh -- CSE 2431: lab5 

  Run with MAKE -- instructions in README

*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "io.h"         /* file in/output and history printing */
#include "globals.h"    /* global variables and defines */
#include "queue.h"      /* data structure for histBuffer */

#define SA_RESTART      0x000004

void handle_SIGINT();
void setup(char inputBuffer[], char *args[], int *background);
void history_then_execvp(char inputBuffer[], char *args[]);

int main(void)
{    
	int pid, background, waitIndicator, numCommands;   
	char inputBuffer[MAX_LINE]; 	
    char *args[MAX_LINE/2+1];		
		
	struct sigaction handler;					
	handler.sa_handler = handle_SIGINT; 	
    handler.sa_flags = SA_RESTART;					
										
	numCommands = 0;
    bufferFill = 0;
	read_history(&numCommands);

    sigaction(SIGINT, &handler, NULL);	
	while (1) {			     /* Program terminates normally inside setup */
    	background = 0;
    	printf("COMMAND->");
       	fflush(0);
        setup(inputBuffer, args, &background);       /* get next command */
		    
    	pid = fork();

	    if (!pid) history_then_execvp(inputBuffer, args);
	    if (pid) {
		    if(!background) wait(NULL);
            else sleep(1);
	    }
    }
}

/* signal handling function */
void handle_SIGINT() {
    int i, a, b;

    i = 0;
    a = strlen("\nHISTORY: type 'r + space' followed by first letter of desired command.\n");
    b = strlen("\nCOMMAND->");

    write(STDOUT_FILENO, "\nHISTORY: type 'r + space' followed by first letter of desired command.\n", a);
	while (i < bufferFill) {
		write(STDOUT_FILENO, histBuffer[i], strlen(histBuffer[i]));
        write(STDOUT_FILENO, "\n", 1);
    	i++;
	}
    write(STDOUT_FILENO, "\nCOMMAND->", b);
}

/**
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters. setup() sets the args parameter as a 
 * null-terminated string.
 */
void setup(char inputBuffer[], char *args[], int *background) {
    int length, /* # of characters in the command line */
        i,      /* loop index for accessing inputBuffer array */
        start,  /* index where beginning of next command parameter is */
        ct;     /* index of where to place the next parameter into args[] */

    ct = 0;
    
    /* read what the user enters on the command line */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);  

    start = -1;
    if (length == 0)
        exit(0);            /* ^d was entered, end of user command stream */
    if (length < 0){
        if (errno == EINTR) {
            length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
        } else {
            perror("error reading the command");
		    exit(-1);           /* terminate with error code of -1 */
        }
    }
	
    /* examine every character in the inputBuffer */
    for (i = 0; i < length; i++) { 
        switch (inputBuffer[i]){
        case ' ':
        case '\t' :               /* argument separators */
            if(start != -1){
                args[ct] = &inputBuffer[start];    /* set up pointer */
                ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;
            
        case '\n':                 /* should be the final char examined */
            if (start != -1){
                args[ct] = &inputBuffer[start];     
                ct++;
            }
            inputBuffer[i] = '\0';
            args[ct] = NULL; /* no more arguments to this command */
            break;

        case '&':
            *background = 1;
            inputBuffer[i] = '\0';
            break;
            
        default :             /* some other character */
            if (start == -1)
                start = i;
		} 
    }    
    args[ct] = NULL; /* just in case the input line was > 80 */
} 

/* Does history and then runs command */
void history_then_execvp(char inputBuffer[], char *args[]) {
    int i;
    char command[MAX_LINE];

    if (strcmp(args[0], "r") == 0) {
        if (args[1] == NULL) {
            fflush(0);
            system(histBuffer[bufferFill]);
        } else {
            fflush(0);
            for (i = bufferFill - 1; i > -1; i--) {
                fflush(0);
                if (histBuffer[i][0] == args[1][0]) break;
            }
            if (i == -1) {
                printf("No recent commands match your query.\n");
                fflush(0);
            } else {
                memset(command,'\0',MAX_LINE);
                strcpy(command, histBuffer[i]);
                fflush(0);
                dequeue();
                enqueue(command);
                system(histBuffer[i]);
            }
        }
    } else {
        memset(command,'\0',MAX_LINE);
        i = 0;
        while (args[i] != NULL) {
            strcat(command, args[i]);
            if (args[i+1] != NULL) strcat(command, " ");
            i++;
        }
        dequeue();
        enqueue(command);
        execvp(inputBuffer, args);
    }
}
