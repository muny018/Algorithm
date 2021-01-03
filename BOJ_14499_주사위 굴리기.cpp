//삼성 역량테스트 기출
//BOJ 14499 주사위 굴리기

//헤매던 점
// 나레기 시뮬레이션에 약함

//문제
//https://www.acmicpc.net/problem/14499

//해설
//https://penglog.tistory.com/74

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std; 

int N, M, x, y, K;
int nMap[21][21] = { 0 };
int nDice[6] = { 0 };
int nDiceMap[5][6] =
{
	{ 1, 2, 3, 4, 5, 6 }, // 0: 기본
	{ 4, 2, 1, 6, 5, 3 }, // 1: 동쪽
	{ 3, 2, 6, 1, 5, 4 }, // 2: 서쪽
	{ 5, 1, 3, 4, 6, 2 }, // 3: 북쪽
	{ 2, 6, 3, 4, 1, 5 }, // 4: 남쪽
};
vector <int> VecDir;
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void DiceMove(int nDir)
{
	int nDiceTemp[6] = {0 };
	for (int i = 0; i < 6; i++)
	{
		nDiceTemp[i] = nDice[i];
	}

	for (int i = 0; i < 6; i++)
	{
		nDice[i] = nDiceTemp[nDiceMap[nDir][i] - 1];
	}
	int stop = 0;
}

void Solve()
{
	int nCurRow = x;
	int nCurCol = y;
	int nNextRow, nNextCol;
	for (int Time = 0; Time < K; Time++)
	{
		int nDir = VecDir[Time];

		nNextRow = nCurRow + dy[nDir-1];
		nNextCol = nCurCol + dx[nDir-1];
		if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= M) continue;

		nCurRow = nNextRow;
		nCurCol = nNextCol;

		DiceMove(nDir);

		if (nMap[nNextRow][nNextCol] == 0)
		{
			nMap[nNextRow][nNextCol] = nDice[5];
		}
		else
		{
			nDice[5] = nMap[nNextRow][nNextCol]; 
			nMap[nNextRow][nNextCol] = 0;
		}


		cout << nDice[0] << endl;
		int a = 0;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	
	cin >> N >> M >> x >> y >> K;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> nMap[i][j];
		}
	}

	int dir = 0;
	for (int i = 0; i < K; i++)
	{
		cin >> dir; 
		VecDir.push_back(dir);
	}

	Solve();


	return 0;
}

