#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status, result;
    int pid_multi_process[3]; // массив для pid процессов
    pid_multi_process[0] = getpid(); // устанавливаем родительский pid
    printf("FATHER PARAMS: pid=%i", pid_multi_process[0]);
    if ((pid_multi_process[1] = fork()) == 0) // создаем процесс и запускаем скрипт son1
        execl("son1", "son1", NULL);
    if ((pid_multi_process[2] = fork()) == 0) // создаем процесс и запускаем скрипт son2
        execl("son2", "son2", NULL);
    system("ps xf > file.txt"); // фиксируем значение системы
    for (int i = 1; i < 3; i++) // проходимся по всем процессам
    {
        result = waitpid(pid_multi_process[i], &status, WUNTRACED); // получаем по очереди информацию о процессах
        if (WIFEXITED(status)) // проверка на успешное завершение процесса
        {
            printf("pid = %d завершен, status = %d\n", pid_multi_process[i], WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) // проверка на смерть процесса от сигнала
        {
            printf("pid = %d умер от сигнала: %d\n", pid_multi_process[i], WTERMSIG(status));
        }
        else if (WIFSTOPPED(status)) // проверка на остановку процесса от сигнала
        {
            printf("pid = %d остановлен сигналом: %d\n", pid_multi_process[i], WSTOPSIG(status));
        }
    }
    return 0;
}