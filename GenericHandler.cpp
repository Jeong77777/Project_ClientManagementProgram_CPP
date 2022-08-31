#include "GenericHandler.h"
#include "Line.h"


void GenericHandler::ShowMenu() const
{
	cout << LINE80 << endl;
	cout << "\t\t\t고객 관리 및 상품 관리 프로그램" << endl;
	cout << LINE80 << endl;
	cout << "\t\t\t\t1.  고객 정보 관리" << endl;
	cout << "\t\t\t\t2.  상품 정보 관리" << endl;
	cout << "\t\t\t\t3.  판매 내역 관리" << endl;
	cout << "\t\t\t\t4.  프로그램 종료" << endl;
	cout << LINE80 << endl;
}

void GenericHandler::CltMenu()
{
	while (1)
	{		
		int sel;
		cltManager.ShowMenu();
		cout << "메뉴를 선택하세요: ";	cin >> sel;

		if (sel == 1)	// 신규고객등록
		{
			system("cls");
			cltManager.AddClientMenu();
		}			
		else if (sel == 2)	// 정보조회삭제변경
		{
			system("cls");
			cltManager.SearchClientMenu();
		}			
		else if (sel == 3)	// 처음으로
		{
			system("cls");
			break;
		}
		else
			cout << "잘못 입력하셨습니다." << endl;
	}
}