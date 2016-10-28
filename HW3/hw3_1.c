#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80

int main(void) {
    int exit = 0;

    char *args[MAX_LINE/2 + 1]; // input buffer
    
    while(!exit) {
        char line[50];
        int background = 0;
        int i = 0;
        pid_t pid;
        printf("-> ");

        gets(line);
        args[0] = strtok(line, " ");
        while (args[i] != NULL) {
            args[++i] = strtok(NULL, " ");
            if (!strcmp(args[i-1], "&")) {
                background = 1;
            }
        }

        pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            exit = 1;
        }
        else if (!background) {
            wait();
        }
    }
    return 0;
}