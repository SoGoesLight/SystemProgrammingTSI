#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <time.h>

using namespace std;

/* 14 % 5 + 1 = 5 вариант

1) Создать массив short размером 10 и заполнить его случайными числами от 1
до 10;
2) Создать структуру, содержащую массивы int, char и float, каждый размером
500;
3) Создать массив структуры выше, размером 10, где предпоследний элемент
int и float содержат индекс своей структуры в массиве, а предпоследний
элемент char букву A - Z(у нулевого элемента A и так далее);
4) Записать массив short, а далее записать массив структуры, делая перед
каждой записью сдвиг указателя на величину, указанную в массиве short под
тем же индексом, что и структура;
5) При считывании сдвиги брать из массива, считаного из памяти;
Вывести на экран предпоследние элементы каждого массива каждой структуры.

*/
const int magicNumber = 500;

struct labStruct {
    int intArr[magicNumber];
    char charArr[magicNumber];
    float floatArr[magicNumber];
};

int main()
{
    srand(time(NULL));
    SYSTEM_INFO sysInfo;
    LPVOID lp;

    GetSystemInfo(&sysInfo);

    printf("Hardware information: \n");
    printf("  Page size: %u\n", sysInfo.dwPageSize);
    printf("  Allocation granularity: %u\n", sysInfo.dwAllocationGranularity);

    lp = VirtualAlloc(
        NULL,                 // System selects address
        sysInfo.dwPageSize,   // Size of allocation
        MEM_RESERVE,          // Allocate reserved pages
        PAGE_NOACCESS);       // Protection = no access

    if (lp == NULL)
        printf("VirtualAlloc reserve failed.");

    // 3 - fulfilling with data
    short arr[10];
    for (int i = 0; i < 10; i++)
        arr[i] = rand() % 10 + 1;

    labStruct myStruct[10];
    for (int i = 0; i < 10; i++) {
        myStruct[i].intArr[magicNumber - 1] = i;
        myStruct[i].floatArr[magicNumber - 1] = i;
        myStruct[i].charArr[magicNumber - 1] = (char)(97 + i);
    }

    // VirtualAlloc short arr
    // VirtualAlloc myStruct

    // перед каждой записью сдвиг на arr[i]




    if (!VirtualFree(lp, 0, MEM_RELEASE))
        printf("Memory release failed."); 

	return 0;
}
