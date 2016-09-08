#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid > 0) { // is the parent
        printf("Process 1 = %d, parent = %d.\n", getpid(), getppid());
        wait();
    }
    else if (pid == 0) { // is the child
        printf("Process 2 = %d, parent = %d.\n", getpid(), getppid());
        pid = fork();
        if (pid > 0)
            wait();
        else if (pid == 0)
            printf("Process 3 = %d, parent = %d.\n", getpid(), getppid());
    }
    return 0;
}
