#include <iostream>
#include <windows.h>
#include<tchar.h>

using namespace std;

/*
Задача. (14 вариант)
1. Составить программу для консольного процесса, который состоит из двух потоков : main и worker.

Поток main должен выполнить следующие действия :
	1. Создать массив целых чисел, размерность и элементы которого вводятся с консоли.
	2. Создать поток worker.
	3. Найти минимальный и максимальный элементы массива и вывести их на консоль. После каждого сравнения элементов «спать» 7 миллисекунд.
	4. Дождаться завершения потока worker.
	5. Подсчитать количество элементов в массиве, значение которых больше среднего значения элементов массива, и вывести его на консоль.
	6. Завершить работу.

Поток worker должен выполнить следующие действия :
	14) Поток worker должен найти значение суммы нечетных элементов массива и минимального элемента. 
		Для синхронизации потоков использовать семафор.
	2. Завершить свою работу.

*/

DWORD WINAPI ThreadProc1(LPDWORD lpData, int* arr);
void findMinAndMax(int* arr, int arrSize);
void numOfElemsBiggerThanAvg(int* arr, int arrSize);
float avgOfElements(int* arr, int arrSize);

int main()
{	
	int arrSize;
	cout << "Set the size of your array, please: ";
	cin >> arrSize;

	int* arr = new int[arrSize];

	cout << "Would you mind filling your array with numbers?\n";
	for (int i = 0; i < arrSize; i++) {
		cout << i + 1 << ") ";
		cin >> arr[i];
	}

	DWORD tid;
	HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc1, NULL, 0, &tid);

	findMinAndMax(arr, arrSize);

	CloseHandle(thread1);

	numOfElemsBiggerThanAvg(arr, arrSize);

	//for (int i = 0; i < arrSize; i++)
	//	cout << i + 1 << ") " << arr[i] << " ";

	delete[] arr;
	cout << "\n\n";
	return 0;
}

DWORD WINAPI ThreadProc1(LPDWORD lpData, int* arr)
{
	HANDLE sem = CreateSemaphore(NULL, 3, 3, _TEXT("Sm"));
	WaitForSingleObject(sem, INFINITE);

	return 0;
}

void findMinAndMax(int* arr, int arrSize) {

	int min, max, i;

	max = arr[0];
	for (i = 0; i < arrSize; i++)
	{
		if (max < arr[i])
			max = arr[i];
		Sleep(7);
	}

	min = arr[0];

	for (i = 0; i < arrSize; i++)
	{
		if (min > arr[i])
			min = arr[i];
		Sleep(7);
	}

	cout << "\nSmallest value is " << min;
	cout << "\nLargest value is " << max;
}


void numOfElemsBiggerThanAvg(int* arr, int arrSize) {
	int counter = 0;
	float avg = avgOfElements(arr, arrSize);

	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] > avg)
			counter++;
	}

	cout << "\nNumber of elements in array, that are bigger than average is " << counter;
}

float avgOfElements(int* arr, int arrSize) {
	float sumOfElems = 0;

	for (int i = 0; i < arrSize; i++)
	{
		sumOfElems += arr[i];
	}

	return sumOfElems / arrSize;
}