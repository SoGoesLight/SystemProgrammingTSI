#include <iostream>
#include <windows.h>
#include <tchar.h>

#define MAX_VALUE_NAME 8191
#define MAX_KEY_LENGTH 255

using namespace std;

// Вариант 2. Написать консольное приложение, выводящие на экран хранящиеся в заданном ключе реестра переменные, их типы и значения. 
//            Имена корневого и заданного ключей вводится в программу с клавиатуры.

void ProcessKey(HKEY hKey);
string RegistryValueTypeToString(DWORD type);
HKEY StringToHKEY(string str); // since we can't just input/convert HKEY

int main(int argc, _TCHAR* argv[])
{
	HKEY hKey, inputHKey;
	string hKeyString, setKeyString;

	cout << "Enter root directory key, please: ";
	cin >> hKeyString;                               // input example: HKEY_LOCAL_MACHINE
    cout << "Enter key directory path, please: ";
	cin >> setKeyString;							 // input example: SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\

	inputHKey = StringToHKEY(hKeyString);
	LONG dwOpenKey = RegOpenKeyExA(inputHKey, setKeyString.c_str(), 0, KEY_READ, &hKey);
	
	// example of "in-code" input
	// LONG dwOpenKey = RegOpenKeyExW(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"), 0, KEY_READ, &hKey); 

	if (dwOpenKey == ERROR_SUCCESS) { // code 0 = ok
		cout << "Registry key opened successfully, error code " << GetLastError() << endl; 
		ProcessKey(hKey);
	}
	else {
		cout << "Registry key open failed, error code " << dwOpenKey << endl;
	}

	RegCloseKey(hKey);
	system("pause");
	return 0;
}

void ProcessKey(HKEY hKey)
{
	TCHAR    subkeyBuff[MAX_KEY_LENGTH];						
	TCHAR    classBuff[MAX_PATH] = TEXT("");
	FILETIME fileLastWriteTime;				
	DWORD    cchClassName = MAX_PATH, subkeysNum = 0, longestSubkeySize, longestClass, keyValuesNum, 
			 longestValueName, longestValueData, securityDescriptorSize, nameSize, statusCode, type;

	TCHAR valueName[MAX_VALUE_NAME];
	DWORD chValueName = MAX_VALUE_NAME;

	statusCode = RegQueryInfoKeyW(hKey, classBuff, &cchClassName, NULL, &subkeysNum, &longestSubkeySize, &longestClass, 
							  &keyValuesNum, &longestValueName, &longestValueData, &securityDescriptorSize, &fileLastWriteTime);     

	// Subkeys
	if (subkeysNum)
	{
		cout << "\nAmount of subkeys: " << subkeysNum << endl;
		for (int i = 0; i < subkeysNum; i++)
		{
			nameSize = MAX_KEY_LENGTH;
			statusCode = RegEnumKeyExW(hKey, i, subkeyBuff, &nameSize, NULL, NULL, NULL, &fileLastWriteTime);
			if (statusCode == ERROR_SUCCESS)
			{
				wcout << i + 1 << ") " << subkeyBuff << endl;
			}
		}
	}

	// Values
	BYTE* buffer = new BYTE[longestValueData];
	RtlZeroMemory(buffer, longestValueData); // simple a cool way to fill a block of memory with zeros

	if (keyValuesNum)
	{
		cout << "\nAmount of values: " << keyValuesNum << endl;

		for (int i = 0, statusCode = ERROR_SUCCESS; i < keyValuesNum; i++)
		{
			chValueName = MAX_VALUE_NAME;
			valueName[longestValueData] = '\0';
			statusCode = RegEnumValueW(hKey, i, valueName, &chValueName, NULL, NULL, NULL, NULL);

			if (statusCode == ERROR_SUCCESS)
			{

				DWORD lpData = longestValueData;
				buffer[0] = '\0'; // in case we got wrong data
				LONG dwRes = RegQueryValueExW(hKey, valueName, 0, &type, buffer, &lpData);
				wcout << i + 1 << ") " << valueName << "\r\t\t\t\t Type: "; 
				cout << RegistryValueTypeToString(type) << endl;
			}
		}
	}

	delete[] buffer; // free memory
}

string RegistryValueTypeToString(DWORD type) {
	switch (type) {
	case REG_NONE:
		return "REG_NONE";
	case REG_SZ:
		return "REG_SZ";
	case REG_EXPAND_SZ:
		return "REG_EXPAND_SZ";
	case REG_BINARY:
		return "REG_BINARY";
	case REG_DWORD:
		return "REG_DWORD";
	case REG_LINK:
		return "REG_LINK";
	case REG_MULTI_SZ:
		return "REG_MULTI_SZ";
	case REG_QWORD:
		return "REG_QWORD";
	}
}

HKEY StringToHKEY(string str) {
	if (str == "HKEY_CLASSES_ROOT")
		return HKEY_CLASSES_ROOT;
	if (str == "HKEY_CURRENT_USER")
		return HKEY_CURRENT_USER;
	if (str == "HKEY_LOCAL_MACHINE")
		return HKEY_LOCAL_MACHINE;
	if (str == "HKEY_USERS")
		return HKEY_USERS;
	if (str == "HKEY_PERFORMANCE_DATA")
		return HKEY_PERFORMANCE_DATA;
	if (str == "HKEY_CURRENT_CONFIG")
		return HKEY_CURRENT_CONFIG;
	if (str == "HKEY_DYN_DATA")
		return HKEY_DYN_DATA;
}