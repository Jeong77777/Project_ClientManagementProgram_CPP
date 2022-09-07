#ifndef __GET_INTEGER_H__
#define __GET_INTEGER_H__

/**
* @brief 숫자만을 입력 받기 위한 함수들
*/
class GetInt
{
public:
	static int GetInteger(int min, int max);
	static int GetInteger();
	static void GetOnlyZero();
};


#endif // __GET_INTEGER_H__
