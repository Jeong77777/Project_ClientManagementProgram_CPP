#include "GetInteger.h"
#include <iostream>

using namespace std;

int GetInt::GetInteger(int min, int max)
{
	int sel;	
	while (1) {
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "다시 입력하세요: ";
		}
		else if (sel < min || sel > max) {
			cout << "다시 입력하세요: ";
		}
		else
			return sel;
	}
}

int GetInt::GetInteger()
{
	int sel;
	while (1) {
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "올바른 숫자를 입력하세요: ";
		}
		else
			return sel;
	}
}

void GetInt::GetOnlyZero()
{
	int sel;
	while (1) {
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		if (sel == 0)
			break;
	}
}