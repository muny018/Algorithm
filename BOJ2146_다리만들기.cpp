//BOJ 2146 다리만들기

//문제
//https://www.acmicpc.net/problem/2146

//해설
//

#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <queue>
#include <iostream>
using namespace std; 

int dx[] = { -1,0,1,0 }; //서북동남
int dy[] = { 0,-1,0,1 };
int nMap[101][101] = { 0 };
int N;
vector <pair <int, int> > Vec;
int nLabelCount = 1;
bool bLabelVisited[101][101] = { 0 };
bool bflag = false;
int nMinDistance = 100000;

void BreadthFirstSearch(int nRow, int nCol)
{
	int nCurRow, nCurCol, nNextRow, nNextCol;
	queue <pair <int, int> > Que;
	bool bVisited[101][101] = { 0 };
	bVisited[nRow][nCol] = true;

	Que.push(make_pair(nRow, nCol));

	int nCount = 0;

	while (!Que.empty())
	{
		int QueSize = Que.size(); 

		for (int nDistance = 0; nDistance < QueSize; nDistance++)
		{
			nCurRow = Que.front().first;
			nCurCol = Que.front().second;
			Que.pop();

			for (int idx = 0; idx < 4; idx++)
			{
				nNextRow = nCurRow + dy[idx];
				nNextCol = nCurCol + dx[idx];
				if (nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N) continue;
				if (bVisited[nNextRow][nNextCol]) continue;
				if (nMap[nCurRow][nCurCol] >= 1 && (nMap[nNextRow][nNextCol] == nMap[nCurRow][nCurCol])) continue; // 같은 섬 제거

				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));

				if (nMap[nCurRow][nCurCol] == 0 && nMap[nNextRow][nNextCol] != 0 && (nMap[nNextRow][nNextCol] != nMap[nRow][nCol])) //섬발견
				{
					if (nMinDistance > nCount)
					{
						nMinDistance = nCount;
					}
				}
			}
		}

		nCount++;

	}

}

void DepthFirstSearch(int nCurRow, int nCurCol)
{
	for (int idx = 0; idx < 4; idx++)
	{
		int nNextRow = nCurRow + dy[idx];
		int nNextCol = nCurCol + dx[idx];
		if (nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N) continue;
		if (bLabelVisited[nNextRow][nNextCol]) continue;
		if (nMap[nNextRow][nNextCol] == 1)
		{
			nMap[nNextRow][nNextCol] = nLabelCount;
			bflag = true;
			bLabelVisited[nNextRow][nNextCol] = true;
			DepthFirstSearch(nNextRow, nNextCol);
		}
	}
}

void Solve()
{
	//섬 라벨링
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (bLabelVisited[i][j] || nMap[i][j] == 0) continue;
			bLabelVisited[i][j] = true;
			nMap[i][j] = nLabelCount;
			bflag = true;
			DepthFirstSearch(i, j);
			
			if (bflag == true) nLabelCount++;
		}
	}

	//가장 짧은 다리 탐색
	int nVecSize = Vec.size();
	for (int i = 0; i < nVecSize; i++)
	{
		int nRow = Vec[i].first;
		int nCol = Vec[i].second;

		BreadthFirstSearch(nRow, nCol);
	}

	cout << nMinDistance << "\n";
}

int main()
{
	int nInput;
	freopen("input.txt", "r", stdin);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nInput;

			if (nInput)
			{
				nMap[i][j] = 1;
				Vec.push_back(make_pair(i, j));
			}
		}
	}

	Solve();


	return 0;
}