#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) // проходимся по всем заданным аргументам
    {
        switch ((int)argv[i][0]) // определяем аргумент
        {
        case (int)'1':
            printf("Была подана цифра 1\n");
            break;
        case (int)'2':
            printf("Была подана цифра 2\n");
            break;
        case (int)'3':
            printf("Была подана цифра 3\n");
            break;
        case (int)'4':
            printf("Была подана цифра 4\n");
            break;
        case (int)'5':
            printf("Была подана цифра 5\n");
            break;
        case (int)'l':
            printf("Появился какая буква l\n");
            break;
        default:
            printf("Что-то непонятное: %c\n", (int)argv[i][0]);
            break;
        }
    }

    return 0;
}