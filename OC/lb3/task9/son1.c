#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("SON1 PARAMS: pid=%i ppid=%i\n", pid, ppid);
    sleep(50);
    return 0;
}