#include "GenericHandler.h"
#include "GetInteger.h"


int main()
{
	GenericHandler genHandler;
	int choice;

	while (1)
	{
		/* 메인 메뉴 출력 */
		genHandler.ShowGenMenu();
		cout << "메뉴를 선택하세요: ";
		choice = GetInt::GetInteger(1, 4);

		switch (choice)
		{
		case 1: // 고객 정보 관리 메뉴
			system("cls");
			genHandler.CltMenu();
			break;
		case 2: // 상품 정보 관리 메뉴
			system("cls");
			genHandler.ProdMenu();
			break;
		case 3: // 주문 내역 관리 메뉴
			system("cls");
			genHandler.OrderMenu();
			break;
		case 4:	//exit
			return 0;	
		}
	}

	return 0;
}