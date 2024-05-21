#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

int main()
{
    int pid, ppid, status;
    pid = getpid();                                                // получаем pid текущего процесса
    ppid = getppid();                                              // получаем pid родителя
    printf("FATHER PARAM: pid=%i ppid=%i\n", pid, ppid);           // выводим информацию про pid
    if (fork() == 0)                                               // создаем новый поток
        execl("son", "son", NULL);                                 // "конструйруем" его. Вызываем программу son
    system("ps xf > file.txt");                                    // записываем информацию о потоках в file.txt
    wait(&status);                                                 // ожидаем завершения работы порожденного процесса
    printf("Child proccess is finished with status %d\n", status); // выводим статус завершенного процесса

    return 0;
}
