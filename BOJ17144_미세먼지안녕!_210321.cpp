//BOJ17144 미세먼지 안녕!

//문제
//https://www.acmicpc.net/problem/17144

//해설
// 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std; 

vector <pair<pair<int, int>, int >> Vec;
int R, C, T;
int nMap[51][51] = { 0 };
int nCopyMap[51][51] = { 0 };
int nPurifyRow = 0;
int nAnswer = 0;
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };


void MoveWind()
{
	int nPurifyRowPos = 0;

	//
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			nCopyMap[i][j] = nMap[i][j];
		}
	}

	//윗쪽 (반시계방향)
	nPurifyRowPos = nPurifyRow;
	nMap[nPurifyRowPos][0] = -1;

		//하단
	nMap[nPurifyRowPos][1] = 0;
	for (int nCol = 2; nCol < C; nCol++)
	{
		nMap[nPurifyRowPos][nCol] = nCopyMap[nPurifyRowPos][nCol - 1];
	}
		//우측
	for (int nRow = nPurifyRowPos - 1; nRow >= 0; nRow--)
	{
		nMap[nRow][C - 1] = nCopyMap[nRow+1][C - 1];
	}
		//상단
	for (int nCol = 0; nCol <= C - 2; nCol++)
	{
		nMap[0][nCol] = nCopyMap[0][nCol + 1];
	}
		//좌측
	for (int nRow = 1; nRow < nPurifyRowPos; nRow++)
	{
		nMap[nRow][0] = nCopyMap[nRow - 1][0];
	}


	//아랫쪽 (시계방향)
	nPurifyRowPos = nPurifyRow + 1;
	nMap[nPurifyRowPos][0] = -1;

		//상단
	nMap[nPurifyRowPos][1] = 0;
	for (int nCol = 2; nCol < C; nCol++)
	{
		nMap[nPurifyRowPos][nCol] = nCopyMap[nPurifyRowPos][nCol - 1];
	}
		//우측
	for (int nRow = nPurifyRowPos+1 ; nRow < R; nRow++)
	{
		nMap[nRow][C-1] = nCopyMap[nRow - 1][C-1];
	}

		//하단
	for (int nCol = 0; nCol <= C - 2; nCol++)
	{
		nMap[R-1][nCol] = nCopyMap[R - 1][nCol + 1];
	}

		//좌측
	for (int nRow = nPurifyRowPos + 1; nRow <= R - 2; nRow++)
	{
		nMap[nRow][0]=  nCopyMap[nRow+1][0];
	}

}

void CheckEmul()
{
	Vec.clear();
	
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (nMap[i][j] > 0)
			{
				Vec.push_back(make_pair(make_pair(i, j), nMap[i][j]));
			}
		}
	}
}

void MoveEmul()
{
	CheckEmul();

	int nVecSize = Vec.size();
	int nRow, nCol, nValue, nNextRow, nNextCol, nMoveValue, nSelfValue;
	int nCount = 0;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			nCopyMap[i][j] = 0;
		}
	}

	for (int nIdx = 0; nIdx < nVecSize; nIdx++)
	{
		nRow = Vec[nIdx].first.first;
		nCol = Vec[nIdx].first.second;
		nValue = Vec[nIdx].second;
		nCount = 0;

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nRow + dy[i];
			nNextCol = nCol + dx[i];

			if (nNextRow < 0 || nNextRow >= R || nNextCol < 0 || nNextCol >= C) continue;
			if (nMap[nNextRow][nNextCol] == -1) continue;
			nCount++;
		}

		nMoveValue = nValue / 5;
		nSelfValue = nValue - (nValue / 5) * nCount;

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nRow + dy[i];
			nNextCol = nCol + dx[i];

			if (nNextRow < 0 || nNextRow >= R || nNextCol < 0 || nNextCol >= C) continue;
			if (nMap[nNextRow][nNextCol] == -1) continue;
			nCopyMap[nNextRow][nNextCol] += nMoveValue;
		}
		nCopyMap[nRow][nCol] += nSelfValue;
	}


	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			nMap[i][j]=nCopyMap[i][j];
		}
	}
	
}

void Solve()
{
	for (int nTime = 0; nTime < T; nTime++)
	{
		MoveEmul();
		MoveWind();
	}

	//미세먼지 양 구하기
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (nMap[i][j] >= 0)
			{
				nAnswer += nMap[i][j];
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> R >> C >> T;

	int nInput;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> nInput;
			nMap[i][j] = nInput;

			if (nInput == -1)
			{
				nPurifyRow = i;
			}
		}
	}

	nPurifyRow--;

	Solve();

	cout << nAnswer << "\n";

	return 0;
}