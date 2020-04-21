#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// Вариант 2. Написать консольное приложение, выводящие на экран хранящиеся в заданном ключе реестра переменные, их типы и значения. 
//            Имена корневого и заданного ключей вводится в программу с клавиатуры.

//HKEY_CLASSES_ROOT
//HKEY_CURRENT_USER
//HKEY_LOCAL_MACHINE
//HKEY_USERS
//HKEY_CURRENT_CONFIG

int main()
{
    //DWORD dwRet, cbData, type;
    DWORD dwType;
    char buffer[255] = { 0 };
    DWORD dwBufferSize = sizeof(buffer);
    HKEY hKey = 0;
    const char* subkey;
    const char* anotherKey;
    //HKEY rootKey = "", setKey = "";
    //cout << "Enter root key: ";
    //cin >> rootKey;
    //cout << "Enter set key: ";
    //cin >> setKey;
    //dwRet = RegQueryValueExW(HKEY_PERFORMANCE_DATA, TEXT("GLOBAL"), NULL, &type, (LPBYTE)PerfData, &cbData);
    //cout << dwRet;
    //LPTSTR lpData = "";
    //TCHAR value[255];

    //cout << qwe;
    //HKEY rKey;
    //TCHAR Reget[256] = { 0 };
    //DWORD RegetPath = sizeof(Reget);
    //LSTATUS rc;
    //DWORD l;
    //rc = RegEnumValueW(HKEY_LOCAL_MACHINE, 11, value, &l, NULL, NULL, NULL, NULL);
    //cout << "rc = " << rc << endl;
    //RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"\SOFTWARE\\Microsoft\\Internet Explorer", NULL, KEY_QUERY_VALUE, &rKey);
    //RegQueryValueExW(rKey, L"Version", NULL, NULL, (LPBYTE)&Reget, &RegetPath);
    //printf("%s", Reget);
    //getchar();
    subkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    anotherKey = "GLOBAL";
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, anotherKey, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
    {
        dwType = REG_SZ;
        if (RegQueryValueExW(hKey, L"AVG_TRAY", 0, &dwType, (BYTE*)buffer, &dwBufferSize) == ERROR_SUCCESS)
        {
            cout << "key value is'" << buffer << "'\n";
        }
        else
            cout << "can not query for key value\n";
    }
    //RegEnumKeyExW();
    //RegQueryInfoKeyW();
    //RegQueryValueExW();

    return 0;
}