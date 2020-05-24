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

const int arrayInStructSize = 500;
const int arraySize = 10;
const int numForShort = 10;
short shortArr[arraySize];

struct labStruct {
    int intArr[arrayInStructSize];
    float floatArr[arrayInStructSize];
    char charArr[arrayInStructSize];
};

labStruct myStruct[arraySize];
const short shift = sizeof(short) * arraySize;

void writingToMemoryShort(char* shiftPointer);
void writingToMemoryStruct(SYSTEM_INFO sysInfo, char* pointer, char* pointerForSt);
void readingFromMemory(char* pointerS, char* pointer, char* pointerForSt);

int main()
{
    srand(time(NULL));
    SYSTEM_INFO sysInfo;

    GetSystemInfo(&sysInfo);

    printf("Hardware information: \n");
    printf("  Page size: %u\n", sysInfo.dwPageSize);
    printf("  Allocation granularity: %u\n\n", sysInfo.dwAllocationGranularity);

    // Fulfilling with data
    for (int i = 0; i < arraySize; i++) {
        shortArr[i] = rand() % numForShort + 1;

        myStruct[i].intArr[arrayInStructSize - 2] = i;
        myStruct[i].floatArr[arrayInStructSize - 2] = i;
        myStruct[i].charArr[arrayInStructSize - 2] = (char)(97 + i);
    }

    char* startPointer = (char*)VirtualAlloc(
            NULL,                               // System selects address for start pointer
            sysInfo.dwAllocationGranularity,    // Size of allocation
            MEM_RESERVE,                        // Allocate reserved pages
            PAGE_READWRITE);                    // Protection

    startPointer = (char*)VirtualAlloc(startPointer, sysInfo.dwPageSize, MEM_COMMIT, PAGE_READWRITE);

    char* shiftPointer = startPointer;

    if (shiftPointer == NULL) {
        printf("VirtualAlloc failed.");
    }
    else {        
        // Operations
        printf("Write operations:\n");
        printf("  Pointer created at 0x%p\n", shiftPointer);

        writingToMemoryShort(shiftPointer);

        char* structPointer = startPointer + shift;
        shiftPointer = structPointer;
        printf("\n  Struct pointer at 0x%p\n\n", structPointer);
        structPointer = startPointer;

        writingToMemoryStruct(sysInfo, shiftPointer, structPointer);
        printf("\nRead operations:\n");
        readingFromMemory(startPointer, shiftPointer, structPointer);
    }

    if (!VirtualFree(startPointer, 0, MEM_RELEASE))
        printf("Memory release failed.");

	return 0;
}

void writingToMemoryShort(char* shiftPointer) {
    printf("\n  Array of shorts:\n");
    for (int i = 0; i < arraySize; i++) {
        *(short*)shiftPointer = shortArr[i];
        shiftPointer += sizeof(short);
        printf("    Pointer %d at 0x%p\n", i, shiftPointer);
    }
}

void writingToMemoryStruct(SYSTEM_INFO sysInfo, char* shiftPointer, char* structPointer) {
    for (int i = 0; i < arraySize; i++) {
        shiftPointer += shortArr[i];

        printf("  Pointer shifted, struct %d located at 0x%p\n", i, shiftPointer);

        // Handling here
        if (shiftPointer - structPointer + sizeof(labStruct) + arraySize > sysInfo.dwPageSize) {
            structPointer = (char*)VirtualAlloc(shiftPointer + sysInfo.dwPageSize + 1, sysInfo.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
            if (structPointer == NULL) {
                printf("  VirtualAlloc failed.");
            }
            else {
                printf("    New page allocated\n");
            }
        }

        *(labStruct*)shiftPointer = myStruct[i];
        shiftPointer += sizeof(labStruct);
    }
}

void readingFromMemory(char* startPointer, char* shiftPointer, char* structPointer) {
    shiftPointer = startPointer;
    structPointer = shiftPointer + shift;

    for (int i = 0; i < arraySize; i++) {
        short shortValue = *(short*)shiftPointer;

        printf("  Data from short pointer at 0x%p\n", shiftPointer);
        printf("    Short value: %d\n", shortValue);

        structPointer += shortValue;
        shiftPointer += sizeof(short);

        int intValue = *(int*)(structPointer + arrayInStructSize * sizeof(int) - 2 * sizeof(int));
        float floatValue = *(float*)(structPointer + arrayInStructSize * (sizeof(int) + sizeof(float)) - 2 * sizeof(float));
        char charValue = *(char*)(structPointer + arrayInStructSize * (sizeof(int) + sizeof(float) + sizeof(char)) - 2 * sizeof(char));

        printf("  Data from structure pointer at 0x%p", structPointer);
        printf("\n    Int value: %d", intValue);
        printf("\n    Float value: %f", floatValue);
        printf("\n    Char value: %c\n", charValue);

        structPointer += sizeof(labStruct);
        printf("\n");
    }
}