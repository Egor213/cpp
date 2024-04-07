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