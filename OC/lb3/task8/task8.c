#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *args[] = {"test", "1", "2", "3", "4", "5", "6", NULL}; // задаем список аргументов
    char *args2[] = {"ls", "-l", "-a", "-h", NULL};              // задаем список аргументов
    char *env[] = {
        "USER=egor",
        "HOME=/home/egor",
        "PATH=/home/egor/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/egor/OC/lb3/task8",
        NULL}; // задаем характеристики среды

    int pid;
    if ((pid = fork()) == 0) // создаем второй поток
    {
        switch ((int)argv[1][0]) // считываем поданные аргумент
        {
        case (int)'1':
            execl("/home/egor/OC/lb3/task8/test", "test", "1", (char *)NULL); // используем list для подачи утилиты и флагов к ней, так же используется полный путь
            break;
        case (int)'2':
            execl("/home/egor/OC/lb3/task8/test", "test", "1", "2", "l", "b", (char *)NULL); //  используем большее количество аргументов
            break;
        case (int)'3':
            execlp("ls", "ls", "-l", (char *)NULL); // поиск пути будет производиться среди путей PATH.
            break;
        case (int)'4':
            execle("test", "test", "1", (char *)NULL, env); // в данном варианте можно задать собственное окружение
            break;
        case (int)'5':
            execv("/home/egor/OC/lb3/task8/test", args); // тут аргументы передаются с помощью вектора args, указывается полный путь
        case (int)'6':
            execvp("ls", args2); // путь берется из PATH, список аргументов и утилита из вектора args2  
            break;
        }
    }
}