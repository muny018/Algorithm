//SWEA 등산로 조성

//문제
//https://swexpertacademy.com/main/code/problem/problemDetail.do

//해설 
//http://shalgorithmstd.tistory.com/88
//http://알고리즘.com/swexpert/73

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std; 

int T, N,K;
int nMap[8][8] = { 0 };
bool bVisited[8][8] = { false };
int nMax;
int nAnswer = 1;
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

void Init()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			nMap[i][j] = 0;
			bVisited[i][j] = 0;
		}
	}
	nMax = 0;
	nAnswer = 1;

}

void Input()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] > nMax) nMax = nMap[i][j];
		}
	}
}

void DepthFirstSearch(int Length, int h, int nCurRow, int nCurCol, bool Used)
{
	if (nAnswer < Length) nAnswer = Length;

	for (int nIdx = 0; nIdx < 4; nIdx++)
	{
		int nNextRow = nCurRow + dy[nIdx];
		int nNextCol = nCurCol + dx[nIdx];

		if (nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N) continue;
		if (bVisited[nNextRow][nNextCol]) continue;

		if (h > nMap[nNextRow][nNextCol])
		{
			bVisited[nNextRow][nNextCol] = true;
			DepthFirstSearch(Length + 1, nMap[nNextRow][nNextCol], nNextRow, nNextCol, Used);
			bVisited[nNextRow][nNextCol] = false;
		}
		else if (Used == false && h> nMap[nNextRow][nNextCol] - K)
		{
			bVisited[nNextRow][nNextCol] = true;
			DepthFirstSearch(Length + 1, h-1, nNextRow, nNextCol, true);
			bVisited[nNextRow][nNextCol] = false;
		}
	}

}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T; 

	for (int nTestCase = 1; nTestCase <= T; nTestCase++)
	{
		cin >> N >> K;

		Init();

		Input();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (nMap[i][j] != nMax) continue;
				bVisited[i][j] = true;
				DepthFirstSearch(1, nMap[i][j], i, j, false);
				bVisited[i][j] = false;
			}
		}

		cout << "#" << nTestCase << " " << nAnswer << "\n";
	}


	return 0;
}