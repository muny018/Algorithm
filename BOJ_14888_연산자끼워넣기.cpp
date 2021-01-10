//삼성 SW 역량테스트 기출
//BOJ 14888 연산자 끼워넣기

//Review
// 특이사항 없음

//문제
//https://www.acmicpc.net/problem/14888

//해설
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std; 
int N;
int nResult = 0;
int nMap[12] = { 0 };
int nCalcMap[5] = { 0 };
int nAnswer_Max = -999999999;
int nAnswer_Min = 999999999;

void DepthFirstSearch(int nIndex, int nSum, int Add, int Subtract, int Multiply, int Divide)
{
	if (nIndex >= N -1)
	{
		//종료 최대 최소 남기는 시퀀스
		if (nSum > nAnswer_Max)
		{
			nAnswer_Max = nSum;
		}
		if (nSum < nAnswer_Min)
		{
			nAnswer_Min = nSum;
		}
		return;
	}

	if (Add > 0)
	{
		nResult = nSum + nMap[nIndex + 1];
		DepthFirstSearch(nIndex + 1, nResult, Add - 1, Subtract, Multiply, Divide);
	}
	if (Subtract > 0)
	{
		nResult = nSum - nMap[nIndex + 1];
		DepthFirstSearch(nIndex + 1, nResult, Add, Subtract - 1, Multiply, Divide);
	}
	if (Multiply > 0)
	{
		nResult = nSum * nMap[nIndex + 1];
		DepthFirstSearch(nIndex + 1, nResult, Add, Subtract, Multiply - 1, Divide);
	}
	if (Divide > 0)
	{
		nResult = nSum / nMap[nIndex + 1];
		DepthFirstSearch(nIndex + 1, nResult, Add, Subtract, Multiply, Divide - 1);
	}


}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> nMap[i];
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> nCalcMap[i];
	}

	DepthFirstSearch(0, nMap[0], nCalcMap[0], nCalcMap[1], nCalcMap[2], nCalcMap[3]);

	cout << nAnswer_Max << endl; 
	cout << nAnswer_Min << endl;

	return 0;
}