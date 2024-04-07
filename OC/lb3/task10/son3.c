#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("SON3 STARTED PARAMS: pid=%i ppid=%i\n", pid, ppid);
    for (int i = 0; i < 1 * 1e9; i++) {} // имитируем работу
    printf("SON3 FINISHED PARAMS: pid=%i ppid=%i\n", pid, ppid);
    
    return 0;
}