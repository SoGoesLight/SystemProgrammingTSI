#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

string getDriveTypeStr(int driveTypeNum);

int main()
{
    //1
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);
    
    //2
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);
    char strLocalTime[256];
    sprintf_s(strLocalTime,
        "%d-%02d-%02d %02d:%02d:%02d.%03d", // d -> Signed decimal integer specifier
        localTime.wYear,
        localTime.wMonth,
        localTime.wDay,
        localTime.wHour,
        localTime.wMinute,
        localTime.wSecond,
        localTime.wMilliseconds);

    TIME_ZONE_INFORMATION timeZone;
    GetTimeZoneInformation(&timeZone);
    char direction = timeZone.Bias <= 0 ? '+' : '-'; // timeZone.Bias == -120
    int hours = abs(timeZone.Bias / 60); 
    int minutes = abs(timeZone.Bias % 60) ;

    //3
    int defUserLanguage = GetUserDefaultLangID();
    char* code = new char[100];
    VerLanguageNameW(defUserLanguage, (LPTSTR)code, 100); // VerLanguageNameA shows "??????? ??????"

    TCHAR username[256];
    DWORD maxUsernameLength = 256;
    GetUserNameA((LPSTR)username, &maxUsernameLength);

    //4
    wchar_t currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(sizeof(currentDirectory), (LPSTR)currentDirectory);

    wchar_t winDir[MAX_PATH];
    GetWindowsDirectoryA((LPSTR)winDir, sizeof(winDir));

    wchar_t sysDir[MAX_PATH];
    GetSystemDirectoryA((LPSTR)sysDir, sizeof(sysDir));

    //5
    int logicalDrives = GetLogicalDrives();

    int n;
    char c[4];
    string drives, drivesTypesAndFreeSpace;

    for (int i = 0; i < 26; i++) // 26 - latin alphabet
    {
        n = ((logicalDrives >> i) & 0x00000001); // bit shift
        if (n == 1) // check if the last bit equals to 1
        {
            c[0] = char(65 + i); // get the correct letter from ASCII table
            c[1] = ':'; // formatting 
            c[2] = '\\'; // formatting
            c[3] = '\0'; // null-terminator

            drives += c; // appending everything from above for output
            drives += ", ";

            char temp[256];
            string type = getDriveTypeStr(GetDriveTypeA((LPCSTR)c));
            sprintf_s(temp, "\n     %s - ", c);
            drivesTypesAndFreeSpace += temp; // appending everything from above for output
            drivesTypesAndFreeSpace += type;

            unsigned long int sectors_per_cluster = 0,
                bytes_per_sector = 0,
                number_of_free_clusters = 0,
                total_number_of_clusters = 0;
            
            GetDiskFreeSpaceA(c, &sectors_per_cluster, // 8
                                 &bytes_per_sector, // 512
                                 &number_of_free_clusters, // 32767739
                                 &total_number_of_clusters); // 243910212

            unsigned long int freeSpace = sectors_per_cluster * bytes_per_sector * number_of_free_clusters; // in Bytes
            freeSpace /= 1048576; // in GBs
            sprintf_s(temp, " - %u GBs", freeSpace);
            drivesTypesAndFreeSpace += temp;
            
            //free_bytes_available = free_bytes_available / 1000000;
            //total_number_of_bytes = total_number_of_bytes / 1048576;
            //total_number_of_free_bytes = total_number_of_free_bytes / 1048576;
        }
    }

    // Output
    cout << "1) Computer name: " << computerName << endl;
    cout << "2.1) Local time: " << strLocalTime << endl;
    cout << "2.2) Time zone: GMT" << direction << hours;
    minutes == 0 ? cout << endl : cout << minutes << endl;
    cout << "3.1) Default user language ID: " << defUserLanguage << endl;
    cout << "3.2) Default user language: " << code << endl; // random Unicode symbols because of Russian def userlang
    printf_s("3.3) Username: %s\n", username); // without printf_s formatting shows kind of address
    printf_s("4.1) Current directory: %s\n", currentDirectory);
    printf_s("4.2) Windows directory: %s\n", winDir);
    printf_s("4.3) System directory: %s\n", sysDir);
    cout << "5.1) Logical drives in bits: " << logicalDrives << endl;
    cout << "5.2) Logical drives by letters: " << drives << endl;
    cout << "5.3) Logical drives their types and free space: " << drivesTypesAndFreeSpace << endl;

    return 0;
}

string getDriveTypeStr(int driveTypeNum) {
    switch (driveTypeNum)
    {
    case 0:
        return "DRIVE_UNKNOWN";
        break;
    case 1:
        return "DRIVE_NO_ROOT_DIR";
        break;
    case 2:
        return "DRIVE_REMOVABLE";
        break;
    case 3:
        return "DRIVE_FIXED";
        break;
    case 4:
        return "DRIVE_REMOTE";
        break;
    case 5:
        return "DRIVE_CDROM";
        break;
    case 6:
        return "DRIVE_RAMDISK";
        break;
    default: "Error";
    }
}