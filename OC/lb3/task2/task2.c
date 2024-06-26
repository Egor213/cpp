#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    int* mass = malloc(12); // создается массив на 3 элемента
    pid = fork();  // с помощью функции fork() порождаем дополнительный процесс
    printf("значение mass[0]: %d\n", mass[0]);
    
    if (pid == -1) // проверяем на корректность создания процесса
    {
        perror("fork"); // выводим сообщение об ошибке
        exit(1);       // выходим из программы
    }
    if (pid == 0) // если процесс порожден корректно и это процесс родитель
    {
        printf("new pid = %d, ppid =%d \n", getpid(), getppid()); // выводим pid процесса и его родителя
        mass[0]++; // совершаем некоторое вычисление в процессе
        printf("Адресс первого элемента массива mass[0]: %p\n", (void *)&mass[0]);
        printf("значение mass[0]: %d\n", mass[0]);
    }
    else // если процесс порожден корректно и это процесс порожденный родительским процессом
    {
        printf("parent pid = %d, ppid =%d \n", getpid(), getppid()); // выводим pid процесса и его родителя
        mass[0]++;
        printf("Адресс первого элемента массива mass[0]: %p\n", (void *)&mass[0]); 
        printf("значение mass[0]: %d\n", mass[0]);
    }
    printf("Финальное значение mass[0]: %d\n", mass[0]); // выводим результат вычисления
    printf("Завершение процесса\n"); // выводим сообщение о завершинии
    free(mass);
    exit(0);
}