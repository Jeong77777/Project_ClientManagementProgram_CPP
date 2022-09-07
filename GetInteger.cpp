#include "GetInteger.h"
#include <iostream>

using namespace std;


/**
* @brief 최솟값~최대값 사이의 숫자만을 입력 받음
* @param int min 최소값
* @param int max 최대값
* @return int 입력 받은 숫자
*/
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


/**
* @brief 숫자만 입력 받음
* @return int 입력 받은 숫자
*/
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


/**
* @brief 숫자 0만 입력 받음
*/
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