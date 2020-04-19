#include <iostream>
#include <windows.h>
using namespace std;

// 14. В текущем каталоге программно создать файл subMape.dat. 
// Записать в данный файл имена подкаталогов С:\Program Files\. 
// Реализовать функцию просмотра содержания файла.

int main()
{
	HANDLE hfile;
	DWORD nb;

	//hfile = CreateFileW(L"subMape.dat", GENERIC_WRITE, 0, NULL, 
	//				OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//SetFilePointer(hfile, 4, NULL, FILE_END);
	//for (int i = 0; i < 10; i++)
	//{
	//	WriteFile(hfile, &i, sizeof(int), &nb, NULL);
	//}
	//CloseHandle(hfile);


	hfile = CreateFile(L"subMape.dat", GENERIC_READ, 0, NULL,
					OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int m;
	ReadFile(hfile, &m, sizeof(int), &nb, NULL);
	cout << endl;
	while (nb != 0)
	{
		ReadFile(hfile, &m, sizeof(int), &nb, NULL);
		cout << m << " ";
	}
	cout << endl;
	CloseHandle(hfile);

	return 0;
}
