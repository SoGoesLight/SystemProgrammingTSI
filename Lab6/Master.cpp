#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <tchar.h>
#include <string>

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

int main()
{
    int day = 0, month = 0, year = 0;

    srand(time(NULL));

    year = rand() % 11 + 2000; // 2000 < year < 2010 as requested by task
    month = rand() % 12 + 1;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        day = rand() % 31 + 1;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        day = rand() % 30 + 1;
    if (month == 2 && year % 4 == 0)
        day = rand() % 29 + 1;
    if (month == 2 && year % 4 != 0)
        day = rand() % 28 + 1;

    //_cprintf("\n\nDate: %d/%d/%d\t(day/month/year)", day, month, year);

    string AppNameAndArguments = "C:\\Projects\\SystemProgramming\\Debug\\Lab6_Slave.exe";

    STARTUPINFOA si;
    PROCESS_INFORMATION piApp;

    DWORD pid = GetCurrentProcessId();
    //_cprintf("\n\nPID = %d", pid);

    AppNameAndArguments += " " + to_string(day) + " " + to_string(month) + " " + to_string(year) + " " + to_string(pid);
    char* args = new char[AppNameAndArguments.length()];
    strcpy(args, AppNameAndArguments.c_str());

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcessA(NULL, args, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
        _cputs("The new process is not created, check a name of the process.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 0;
    }

    _cputs("The new process is created.\n");

    WaitForSingleObject(piApp.hProcess, INFINITE);

    cout << "All processes are finished\n\n";

    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);

    return 0;
}
