#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

int n = 0;

int main()
{
    int pid;
    cpu_set_t mask;
    CPU_ZERO(&mask);   // Очищаем маску
    CPU_SET(0, &mask); // Устанавливаем CPU 0

    clock_t start, end;
    double cpu_time_used;

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
    {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    } 

    pid = fork();  // с помощью функции fork() порождаем дополнительный процесс
    if (pid == -1) // проверяем на корректность создания процесса
    {
        perror("fork"); // выводим сообщение об ошибке
        exit(1);        // выходим из программы
    }
    if (pid == 0) // если процесс порожден корректно и это процесс родитель
    {
        // printf("new pid = %d, ppid =%d \n", getpid(), getppid()); // выводим pid процесса и его родителя
        printf("new pid = %d, ppid =%d \n", getpid(), getppid());
        for (size_t i = 0; i < 5 * 1e9; i++, n++) // цикл на 10 итерации для имитации работы
        {
        } // запустим длительную функцию
    }
    else // если процесс порожден корректно и это процесс порожденный родительским процессом
    {
        // printf("parent pid = %d, ppid =%d \n", getpid(), getppid()); // выводим pid процесса и его родителя
        printf("new pid = %d, ppid =%d \n", getpid(), getppid());
        for (size_t i = 0; i < 5 * 1e9; i++, n++) // цикл на 10 итерации для имитации работы
        {
        } // запустим длительную функцию
    }

    printf("Завершение процесса pid = %d\n", getpid());
    exit(0);
}