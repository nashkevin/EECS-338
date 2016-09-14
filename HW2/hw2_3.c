#include <stdio.h>
#include <unistd.h>

/* This process creates two children
 * The parent and its children print their pids and their parent's pids
 * The print order is descending by recency of instantiation
 */
int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0) { // is the child
        pid = fork();
        if (pid == 0)
            printf("Process 3 = %d, parent = %d.\n", getpid(), getppid());
        else if (pid > 0) {
            wait();
            printf("Process 2 = %d, parent = %d.\n", getpid(), getppid());
        }
    }
    else if (pid > 0) { // is the parent
        wait();
        printf("Process 1 = %d, parent = %d.\n", getpid(), getppid());
    }
    return 0;
}
