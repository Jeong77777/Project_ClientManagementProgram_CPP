#include "GetInteger.h"
#include <iostream>

using namespace std;


/**
* @brief �ּڰ�~�ִ밪 ������ ���ڸ��� �Է� ����
* @param int min �ּҰ�
* @param int max �ִ밪
* @return int �Է� ���� ����
*/
int GetInt::GetInteger(int min, int max)
{
	int sel;	
	while (1) {
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "�ٽ� �Է��ϼ���: ";
		}
		else if (sel < min || sel > max) {
			cout << "�ٽ� �Է��ϼ���: ";
		}
		else
			return sel;
	}
}


/**
* @brief ���ڸ� �Է� ����
* @return int �Է� ���� ����
*/
int GetInt::GetInteger()
{
	int sel;
	while (1) {
		cin >> sel;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "�ùٸ� ���ڸ� �Է��ϼ���: ";
		}
		else
			return sel;
	}
}


/**
* @brief ���� 0�� �Է� ����
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