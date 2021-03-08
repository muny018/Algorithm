//BOJ 1744 SWTest A 비슷문제 '수 묶기'

//문제
//https://www.acmicpc.net/problem/1744

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std; 

int N;
int nMap[10000] = { 0 };
bool bVisited[10000] = { false };
int Result = 0;

void Solve()
{
	bool IsNegativeOdd = false;
	bool IsPositiveOdd = false;

	//음수 일 때
	for (int i = 0; i < N - 1; i= i+2)
	{
		if (nMap[i + 1] >= 1) break;

		Result += nMap[i]*nMap[i + 1];
		bVisited[i] = true;
		bVisited[i + 1] = true;
	}

	//양수 일 때
	for (int i = N-1; i > 0; i = i -2)
	{
		if (nMap[i-1] <= 1)break;
		Result += nMap[i] * nMap[i - 1];
		bVisited[i] = true;
		bVisited[i - 1] = true;
	}

	for (int i = 0; i < N; i++)
	{
		if (bVisited[i] == true) continue; 

		Result += nMap[i];

	}


}

void BubbleSort()
{
	int Temp;

	for (int j = 0; j < N - 1; j++)
	{
		for (int i = 0; i < N - 1; i++)
		{
			if (nMap[i] > nMap[i + 1])
			{
				Temp = nMap[i];
				nMap[i] = nMap[i + 1];
				nMap[i + 1] = Temp;
			}
		}
	}

}

int main()
{
	
	cin >> N; 

	for (int i = 0; i < N; i++)
	{
		cin >> nMap[i];
	}

	BubbleSort();
	Solve();

	cout << Result << endl;

	return 0;
}