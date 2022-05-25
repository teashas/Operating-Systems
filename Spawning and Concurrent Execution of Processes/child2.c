#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("Process #%d, now running program 'child2.exe' My parent's PID is %d\n", getpid(), getppid());
}
