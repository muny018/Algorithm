//BOJ 17406 배열 돌리기 4

//문제
//https://www.acmicpc.net/problem/17406

//해설
//https://regularmember.tistory.com/129

//헤매던 점

//시작 시간 2시 30분

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <tuple>
using namespace std;

struct Pos {
	int r;
	int c;
	int s;
}sPos;

int N, M, K;
int nMap[101][101] = { 0 };
int nMapCopy[101][101] = { 0 };
int nAnswer = 999999;
int Combi[10] = { 0 };
bool bVisited[10] = { 0 };
vector <Pos> Vec;
int nStartRow, nStartCol, nEndRow, nEndCol;
int StartRow, StartCol, EndRow, EndCol;

void BFS(int nDepth)
{
	nStartRow = nStartRow + nDepth;
	nStartCol = nStartCol + nDepth;
	nEndRow = nEndRow - nDepth;
	nEndCol = nEndCol - nDepth;

	queue <int> Que;

	//복사
	//가로1
	for (int i = nStartCol; i <= nEndCol; i++)
	{
		Que.push(nMap[nStartRow][i]);
	}

	//세로1
	for (int i = nStartRow + 1; i <= nEndRow; i++)
	{
		Que.push(nMap[i][nEndCol]);
	}

	//가로2
	for (int i = nEndCol - 1; i >= nStartCol; i--)
	{
		Que.push(nMap[nEndRow][i]);
	}

	//세로2
	for (int i = nEndRow - 1; i >= nStartRow + 1; i--)
	{
		Que.push(nMap[i][nStartCol]);
	}

	//붙여넣기
	int nTemp = 0;
	//가로1
	for (int i = nStartCol + 1; i <= nEndCol; i++)
	{
		nTemp = Que.front();
		Que.pop();
		nMap[nStartRow][i] = nTemp;
	}

	//세로1
	for (int i = nStartRow + 1; i <= nEndRow; i++)
	{
		nTemp = Que.front();
		Que.pop();
		nMap[i][nEndCol] = nTemp;
	}

	//가로2
	for (int i = nEndCol - 1; i >= nStartCol; i--)
	{
		nTemp = Que.front();
		Que.pop();
		nMap[nEndRow][i] = nTemp;
	}

	//세로2
	for (int i = nEndRow - 1; i >= nStartRow; i--)
	{
		nTemp = Que.front();
		Que.pop();
		nMap[i][nStartCol] = nTemp;
	}

	if (!Que.empty())
	{
		int stop_a = 0;
	}
}

void Solve()
{
	int Count = 0, Num;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			nMap[i][j] = nMapCopy[i][j];
		}
	}

	for (int i = 0; i < K; i++)
	{
		Num = Combi[i];
		StartRow = Vec[Num].r - Vec[Num].s;
		StartCol = Vec[Num].c - Vec[Num].s;

		EndRow = Vec[Num].r + Vec[Num].s;
		EndCol = Vec[Num].c + Vec[Num].s;

		Count = (EndRow - StartRow + 1) / 2;

		nStartRow = StartRow;
		nStartCol = StartCol;
		nEndRow = EndRow;
		nEndCol = EndCol;
		for (int j = 0; j < Count; j++)
		{
			BFS(j);
		}
	}

	int Sum = 0;
	for (int i = 1; i <= N; i++)
	{
		Sum = 0;
		for (int j = 1; j <= M; j++)
		{
			Sum += nMap[i][j];
		}
		if (nAnswer > Sum) nAnswer = Sum;
	}


}

void DepthFirstSearch(int nIndex)
{
	if (nIndex >= K)
	{
		Solve();
		return;
	}

	for (int i = 0; i < K; i++)
	{
		if (bVisited[i]) continue;

		bVisited[i] = true;
		Combi[nIndex] = i;
		DepthFirstSearch(nIndex + 1);
		Combi[nIndex] = 0;
		bVisited[i] = false;

	}


}

int main()
{
	freopen("input.txt", "r", stdin);

	//입력
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> nMap[i][j];
			nMapCopy[i][j] = nMap[i][j];
		}
	}

	for (int i = 0; i < K; i++)
	{
		cin >> sPos.r >> sPos.c >> sPos.s;
		Vec.push_back(sPos);
	}


	DepthFirstSearch(0);

	//출력
	cout << nAnswer << endl;

	return 0;
}