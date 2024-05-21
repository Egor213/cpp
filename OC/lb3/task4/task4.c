#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int n = 0;

int main()
{
    int pid;
    struct sched_param param;
    cpu_set_t mask;
    CPU_ZERO(&mask);   // Очищаем маску
    CPU_SET(0, &mask); // Устанавливаем CPU 0

    printf("Изначальный приоритет: %d\n", param.sched_priority); // получаем значение текущего приоритета
    printf("Изначальная политика: ");                            // получаем текущую схему планирования
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1)
    {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }
    switch (sched_getscheduler(0))
    {
    case SCHED_FIFO:
        printf("SCHED_FIFO\n");
        break;
    case SCHED_RR:
        printf("SCHED_RR\n");
        break;
    case SCHED_OTHER:
        printf("SCHED_OTHER\n");
        break;
    case -1:
        perror("SCHED_GETSCHEDULER");
        break;
    default:
        printf("Неизвестная политика планирования\n");
    }

    pid = fork(); // с помощью функции fork() порождаем дополнительный процесс

    if (pid == -1) // проверяем на корректность создания процесса
    {
        perror("fork"); // выводим сообщение об ошибке
        exit(1);        // выходим из программы
    }
    if (pid == 0) // если процесс порожден корректно и это процесс родитель
    {
        param.sched_priority = sched_get_priority_max(SCHED_FIFO); // устанавливаем новое значение приоритета для потомка процесса
        sched_setscheduler(getpid(), SCHED_FIFO, &param);          // устанавливаем новое значение приоритета
        printf("Текущий приоритет потомка после: %d\n", param.sched_priority); // получаем текущий приоритет
        printf("Политика потомка после: ");                                    // получаем текущую схему планирования
        switch (sched_getscheduler(getpid()))
        {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case -1:
            perror("SCHED_GETSCHEDULER");
            break;
        default:
            printf("Неизвестная политика планирования\n");
        }

        printf("new pid = %d, ppid =%d \n", getpid(), getppid()); // выводим pid процесса и его родителя
        for (size_t i = 0; i < 1 * 1e9; i++, n++)                 // цикл на 10 итерации для имитации работы
        {
        } // запустим длительную функцию                                          // запустим длительную функцию
    }
    else // если процесс порожден корректно и это процесс порожденный родительским процессом
    {
        printf("Текущий приоритет родителя после: %d\n", param.sched_priority);
        printf("Политика родителя после: "); // получаем текущую схему планирования
        switch (sched_getscheduler(getpid()))
        {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case -1:
            perror("SCHED_GETSCHEDULER");
            break;
        default:
            printf("Неизвестная политика планирования\n");
        }

        printf("parent pid = %d, ppid =%d \n", getpid(), getppid()); // выводим pid процесса и его родителя
        for (size_t i = 0; i < 1 * 1e9; i++, n++)                    // цикл на 10 итерации для имитации работы
        {
        } // запустим длительную функцию                                               // запустим длительную функцию
    }
    printf("Завершение процесса pid = %d\n", getpid());
    exit(0);
}