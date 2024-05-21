#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int pid = fork(); // создаем поток
    if (pid == 0)     // если это порожденный поток
    {
        printf("new pid = %d, ppid = %d\n", getpid(), getppid()); // выводим информацию о нем
        for (int i = 0; i < 1e9; i++){} // имитируем работу
        int status;
        printf("new - %d\n", wait(&status)); // вызываем функцию wait у потомка
        printf("new status: %d\n", status);  // выводим значение переменной status
        exit(1);
    }
    else
    {
        printf("parent pid = %d, ppid = %d\n", getpid(), getppid()); // выводим информацию об основном потоке
        int status;
        printf("1: parent - %d\n", wait(&status)); // вызывает wait() для первого потока
        printf("1: parent status: %d\n", status);  // выводим значение переменной status
        printf("2: parent - %d\n", wait(&status)); // вызываем wait() для эксперимента
        printf("2: parent status: %d\n", status);  // выводим значение переменной status
    }
}