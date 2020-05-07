#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

// 14 % 10 + 1 = 5 вариант
/*
1. Написать программу SLAVE, которая выводит день недели по дате, переданной в качестве
параметра.Если параметр не передан, вывести об этом сообщение и закончить программу.
Если программа запущена из приложения MASTER, вывести на экран уникальный
идентификатор приложения MASTER Если программа запущена сама по себе, вывести об
этом информацию.

2. Написать приложение MASTER, которое:
а) генерирует дату (день, месяц, год – 2000...2010), запускает приложение SLAVE и
передает в качестве параметров сгенерированную дату и уникальный идентификатор
процесса (MASTER). При завершении программы SLAVE завершается MASTER

3. Продемонстрировать совместную работу двух приложений. Для этого на экран должна
выводиться достаточно подробная информация о ходе выполнения каждого из процессов.
*/

void printWeekDay(int day, int month, int year);

int main(int argc, char* argv[])
{
    if (argc > 1) {
        DWORD parentalID = atoi(argv[4]);
        _cprintf("\n\nExecuted by %d", parentalID);
        _cprintf("\n\nDate is %s/%s/%s, and it is ", argv[1], argv[2], argv[3]);
        printWeekDay(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    }
    else
        _cputs("\n\nExecuted by myself");

    _cputs("\n\nPress any key to finish.\n");
    _getch();

    return 0;
}

void printWeekDay(int day, int month, int year) {
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    int weekDay = (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;

    switch (weekDay) {
    case 1:
        _cputs("Monday");
        break;
    case 2:
        _cputs("Tuesday");
        break;
    case 3:
        _cputs("Wednesday");
        break;
    case 4:
        _cputs("Thursday");
        break;
    case 5:
        _cputs("Friday");
        break;
    case 6:
        _cputs("Saturday");
        break;
    case 7:
        _cputs("Sunday");
        break;
    default:
        cout << weekDay;
        _cputs("Something went terribly wrong");
        break;
    }
}