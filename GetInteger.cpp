#include "GetInteger.h"
#include <iostream>

using namespace std;

int GetInt::GetIntger(int min, int max)
{
	int sel;
	cin >> sel;
	while (sel < min || sel > max)
	{
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> sel;
	}
	return sel;
}

int GetInt::GetIntger()
{
	int id;
	cin >> id;
	while (id < 0 || id > INT_MAX)
	{
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << "�ùٸ� ���ڸ� �Է��ϼ���: ";
		cin >> id;
	}
	return id;
}

void GetInt::GetOnlyZero()
{
	int sel = 1;
	while (sel != 0)
	{
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}		
	}
}