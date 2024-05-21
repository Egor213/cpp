#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include <sys/wait.h>
int n = 0;

int main()
{
    int pid;
    cpu_set_t mask;
    CPU_ZERO(&mask);   // Очищаем маску
    CPU_SET(0, &mask); // Устанавливаем CPU 0

    clock_t start, end;
    double cpu_time_used;

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) // устанавливаем одно ядро
    {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }
    int pid1, pid2, pid3;
    printf("FATHER PARAMS: pid=%i\n", getpid());
    if ((pid1 = fork()) == 0) // создаем вложенные процессы
    {
        if ((pid2 = fork()) == 0)
        {
            if ((pid3 = fork()) == 0)
            {
                system("ps fx > text.txt"); // фиксируем состояние системы
                execl("son3", "son3", NULL); // конструйруем все процессы определенными файлами
            }
            execl("son2", "son2", NULL);
        }
        execl("son1", "son1", NULL);
  
        
        

    }
    for (int i = 0; i < 1 * 1e9; i++) {} // имитируем работу
    printf("Завершение родительского процесса pid = %d\n", getpid());
    exit(0);
}