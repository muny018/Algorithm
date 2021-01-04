//삼성 SW 역량테스트 기출
//BOJ 14501 퇴사

//문제
//https://www.acmicpc.net/problem/14501

//해설
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std; 

int N;
int nMap[3][21] = { 0 };
int bVisited[21] = { 0 };
int nAnswer = 0;

int max(int a, int b)
{
	return a > b ? a : b;
}

void DepthFirstSearch(int nIndex, int nSum)
{
	if (nIndex >= N + 1)
	{
		nAnswer = max(nAnswer, nSum);
		return;
	}

	if (nIndex + nMap[0][nIndex] <= N + 1 && nIndex!=0)
	{
		DepthFirstSearch(nIndex + nMap[0][nIndex], nSum + nMap[1][nIndex]);
	}
	DepthFirstSearch(nIndex + 1, nSum);
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 1; i <= N; i++)
	{
		cin >> nMap[0][i] >> nMap[1][i];
	}

	DepthFirstSearch(1, 0);

	cout << nAnswer << endl;

	return 0;
}