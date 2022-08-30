#include "GenericHandler.h"


void GenericHandler::ShowMenu() const
{
	cout << "-----상품 관리 프로그램------" << endl;
	cout << "1. 고객 정보 관리" << endl;
	cout << "2. 상품 정보 관리" << endl;
	cout << "3. 판매 내역 관리" << endl;
	cout << "4. 프로그램 종료" << endl;
}

void GenericHandler::CltMenu()
{
	while (1)
	{
		//system("cls");
		int sel;
		cltManager.ShowMenu();
		cout << "선택: ";	cin >> sel;

		if (sel == 1)
			cltManager.AddClient();
		else if (sel == 2)
			cltManager.SearchClient();
		else if (sel == 3)
		{
			int id;
			cout << "\n삭제할 고객ID를 입력하시오: " << endl;
			cin >> id;
			cltManager.DeleteClient(id);
		}
		else if(sel==4)
			break;			
		else
			cout << "잘못 입력하셨습니다." << endl;
	}
}