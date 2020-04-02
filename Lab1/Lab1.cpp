#include <iostream>
#include <iomanip>
#include "Lab1.h"

int main()
{
	std::cout << "First task:\n";
	firstTask();
	std::cout << std::endl << std::endl << "\nSecond task:\n";
	secondTask();
	std::cout << std::endl << std::endl << "\nThird task:\n";
	thirdTask();
	std::cout << std::endl << std::endl << "\nFourth task:\n";
	fourthTask();

	return 0;
}

void firstTask()
{
	unsigned int decimalNum;

	std::cout << "Enter your number to convert into binary: ";
	std::cin >> decimalNum;
	std::cout << std::setw(12) << decimalNum << " = ";
	showBinary(decimalNum);
}

void secondTask()
{
	unsigned int decimalNum;
	unsigned int shift;

	std::cout << "Enter your number to convert into binary: ";
	std::cin >> decimalNum;
	std::cout << "Enter your number to shift: ";
	std::cin >> shift;

	unsigned int shiftedNum = (decimalNum << shift) | (decimalNum >> (sizeof(decimalNum) * CHAR_BIT - shift));

	showBinary(shiftedNum);
}

void thirdTask()
{
	unsigned int day = 0, month = 0, year = 0;

	std::cout << "Enter day: ";
	std::cin >> day;

	std::cout << "Enter month: ";
	std::cin >> month;

	std::cout << "Enter year: ";
	std::cin >> year;

	std::cout << "\n\nPacked date: ";
	unpackDate(packDate(day, month, year));
}

void fourthTask()
{
	unsigned int decimalNum;

	std::cout << "Enter any number: ";
	std::cin >> decimalNum;

	std::cout << "Binary: ";
	showBinary(decimalNum);

	std::cout << "\n\n1st method - Amount of 1s: " << fourthTaskFirst(decimalNum);
	fourthTaskSecond(decimalNum);
}

unsigned int fourthTaskFirst(unsigned int decimalNum)
{
	unsigned int oneChecker = 1, onesCounter = 0, bit = 0;

	if (decimalNum < 256)
		bit = 8;
	else
		bit = 32;

	for (unsigned int i = 1; i <= bit; i++)
	{
		if (oneChecker & decimalNum)
		{
			onesCounter++;
		}
		oneChecker <<= 1;
	}

	return onesCounter;
}

void fourthTaskSecond(unsigned int decimalNum)
{
	char arr[256] = {};
	unsigned int decNum = 0, onesCounter = 0;

	for (unsigned int i = 0; i < 256; i++) {
		decNum = fourthTaskFirst(i);
		arr[i] = (char)decNum;
	}

	//unsigned int byte1 = decimalNum & 0x00'00'00'FF;
	//unsigned int byte2 = (decimalNum & 0x00'00'FF'00) >> 8;
	//unsigned int byte3 = (decimalNum & 0x00'FF'00'00) >> 16;
	//unsigned int byte4 = (decimalNum & 0xFF'00'00'00) >> 24;
	//onesCounter = arr[byte1] + arr[byte2] + arr[byte3] + arr[byte4];

	unsigned char bytes[4];

	for (int i = 3; i >= 0; i--) {
		bytes[3 - i] = (decimalNum >> (i * CHAR_BIT)) & 0xFF;
		onesCounter += arr[bytes[3 - i]];
	}

	std::cout << "\n2nd method - Amount of 1s: " << onesCounter << "\n\n\n\n";
}

void showBinary(unsigned int decimalNum)
{
	unsigned int displayMask = 1 << 31;

	for (unsigned int shownBit = 1; shownBit <= 32; shownBit++)
	{
		std::cout << (decimalNum & displayMask ? '1' : '0');
		displayMask >>= 1;
		if (shownBit % CHAR_BIT == 0)
		{
			std::cout << ' ';
		}
	}
}

// 00000000 00000000 00000000 00000000 - unsigned int
// |  day  | month  |      year      |

int packDate(unsigned int day, unsigned int month, unsigned int year)
{
	unsigned int packedDate;

	packedDate = day << 24 | month << 16 | year;
	showBinary(packedDate);

	return packedDate;
}

int unpackDate(int packedDate)
{
	int day = packedDate >> 24;
	int month = (packedDate << 8) >> 24;
	int year = (packedDate << 16) >> 16;

	std::cout << "\nUnpacked date: " << day << "/" << month << "/" << year;

	return 0;
}