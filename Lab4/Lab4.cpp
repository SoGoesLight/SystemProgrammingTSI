#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string.h>

#define BUFFER_SIZE 1024

using namespace std;

// 14. В текущем каталоге программно создать файл subMape.dat. 
// Записать в данный файл имена подкаталогов С:\Program Files\. 
// Реализовать функцию просмотра содержания файла.

int main()
{
	HANDLE hFind, hFile;
	WIN32_FIND_DATA lpFile;
	char buff[BUFFER_SIZE] = { 0 };
	DWORD dwBytesRead, dwBytesWritten;

	// Find & Write
	hFile = CreateFile(_TEXT("subMape.dat"), GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	SetCurrentDirectory(_TEXT("C:\\Program Files\\"));
	hFind = FindFirstFile(_TEXT("*.*"), &lpFile);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		sprintf_s(buff, "%ws\n", lpFile.cFileName);
		WriteFile(hFile, buff, (DWORD)strlen(buff), &dwBytesWritten, NULL);
	}
	else
	{
		printf("File was not opened. Error %u", GetLastError());
		return EXIT_FAILURE;
	}

	while (FindNextFile(hFind, &lpFile))
	{
		sprintf_s(buff, "%ws\n", lpFile.cFileName);
		WriteFile(hFile, buff, (DWORD)strlen(buff), &dwBytesWritten, NULL);
	}
	FindClose(hFind);
	CloseHandle(hFile);

	//Read
	SetCurrentDirectory(_TEXT("C:\\Projects\\SystemProgramming\\Lab4\\"));
	hFile = CreateFile(_TEXT("subMape.dat"), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &buff, BUFFER_SIZE, &dwBytesRead, NULL);

		for (int i = 0; i < dwBytesRead; i++)
			cout << buff[i];
	}
	else
	{
		printf("File was not read correctly. Error %u", GetLastError());
		return EXIT_FAILURE;
	}

	CloseHandle(hFile);

	return 0;
}