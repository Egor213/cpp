#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

int main()
{
    int pid, ppid;
    pid = getpid();                                    // получаем pid текущего процесса
    ppid = getppid();                                  // получаем pid родителя
    printf("SON PARAMS: pid=%i ppid=%i\n", pid, ppid); // выводим информацию про pid
    sleep(15);                                         // имитируем рабоут 15 секунд
    return 0;
}
