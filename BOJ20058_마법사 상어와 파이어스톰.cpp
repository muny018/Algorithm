//BOJ 20058 마법사 상어와 파이어스톰

//문제
//https://www.acmicpc.net/problem/20058

//해설
//

#define _CRT_SECURE_NO_WARNINGS
#define MaxRange 70

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int nMap[MaxRange][MaxRange] = { 0 };
int nCopyMap[MaxRange][MaxRange] = { 0 };
bool bVisited[MaxRange][MaxRange] = { false };
int dx[] = { -1,0,1,0 }; // 서북동남
int dy[] = { 0,-1,0,1 };
vector <int> vLInput; 
int N, Q, NValue;
int nIceNum = 0;
int nMaxArea = 0;

int BreadthFirstSearch(int nRow, int nCol)
{
	queue<pair<int, int>> Que;
	Que.push(make_pair(nRow, nCol));
	bVisited[nRow][nCol] = true;
	int nNextRow, nNextCol, nCurRow, nCurCol;
	int nCount = 1;

	while (!Que.empty())
	{
		nCurRow = Que.front().first;
		nCurCol = Que.front().second;
		Que.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nCurRow + dy[i];
			nNextCol = nCurCol + dx[i];
			if (nNextRow < 0 || nNextRow >= NValue || nNextCol < 0 || nNextCol >= NValue) continue;
			if (bVisited[nNextRow][nNextCol] || nMap[nNextRow][nNextCol] == 0) continue;

			bVisited[nNextRow][nNextCol] = true;
			Que.push(make_pair(nNextRow, nNextCol));
			nCount++;
		}
	}
	return nCount;
}

void Rotate(int nStartPosRow, int nStartPosCol, int nSize)
{
	int nRowIdx= 0 , nColIdx = 0;

	//상단
	nRowIdx = nStartPosRow + nSize-1;
	for (int nCol = nStartPosCol; nCol < nStartPosCol + nSize; nCol++)
	{
		nMap[nStartPosRow][nCol] = nCopyMap[nRowIdx][nStartPosCol];
		nRowIdx--;
	}

	//우측
	nColIdx = nStartPosCol;
	for (int nRow = nStartPosRow; nRow < nStartPosRow + nSize; nRow++)
	{
		nMap[nRow][nStartPosCol+nSize-1] = nCopyMap[nStartPosRow][nColIdx];
		nColIdx++;
	}


	//하단
	nRowIdx = nStartPosRow;
	for (int nCol = nStartPosCol + nSize-1; nCol >= nStartPosCol; nCol--)
	{
		nMap[nStartPosRow+nSize-1][nCol] = nCopyMap[nRowIdx][nStartPosCol+nSize-1];
		nRowIdx++;
	}

	//좌측
	nColIdx = nStartPosCol+nSize-1;
	for (int nRow = nStartPosRow+nSize-1; nRow >= nStartPosRow; nRow--)
	{
		nMap[nRow][nStartPosCol] = nCopyMap[nStartPosRow+nSize-1][nColIdx];
		nColIdx--;
	}

	//하단 레벨진입
	if (nSize-2 >= 2)
	{
		Rotate(nStartPosRow + 1, nStartPosCol + 1, nSize-2);
	}
	else
	{
		return;
	}
}

void RotateSequence(int idx)
{
	int nLInput = vLInput[idx];
	int LValue = 1;
	int nLTPosRow = 0, nLTPosCol = 0;

	for (int i = 0; i < nLInput; i++)
	{
		LValue *= 2;
	}

	//nMap 복사
	for (int nRow = 0; nRow < NValue; nRow++)
	{
		for (int nCol = 0; nCol < NValue; nCol++)
		{
			nCopyMap[nRow][nCol] = nMap[nRow][nCol];
		}
	}

	//Rotate
	for (int nRow = 0; nRow < NValue; nRow += LValue)
	{
		for (int nCol = 0; nCol < NValue; nCol += LValue)
		{
			Rotate(nRow, nCol, LValue);
		}
	}
}

void CheckIceState()
{
	int nCount = 0;
	int nNextRow = 0, nNextCol = 0;


	//nMap 복사
	for (int nRow = 0; nRow < NValue; nRow++)
	{
		for (int nCol = 0; nCol < NValue; nCol++)
		{
			nCopyMap[nRow][nCol] = nMap[nRow][nCol];
		}
	}

	for (int nRow = 0; nRow < NValue; nRow++)
	{
		for (int nCol = 0; nCol < NValue; nCol++)
		{
			if (nMap[nRow][nCol] == 0) continue;
			nCount = 0;

			for (int idx = 0; idx < 4; idx++)
			{
				nNextRow = nRow + dy[idx];
				nNextCol = nCol + dx[idx];
				if (nNextRow < 0 || nNextRow >= NValue || nNextCol < 0 || nNextCol >= NValue) continue;
				if (nCopyMap[nNextRow][nNextCol] > 0) nCount++;
			}

			if (nCount < 3) nMap[nRow][nCol]--;
		}
	}
}

void Solve()
{
	for (int nTime = 0; nTime < Q; nTime++)
	{
		RotateSequence(nTime);
		CheckIceState();
	}

	//얼음양 계산하기
	for (int nRow = 0; nRow < NValue; nRow++)
	{
		for (int nCol = 0; nCol < NValue; nCol++)
		{
			if (nMap[nRow][nCol] <= 0) continue;
			nIceNum += nMap[nRow][nCol];
		}
	}

	int Value = 0;
	//가장 큰 얼음덩어리 크기 계산
	for (int nRow = 0; nRow < NValue; nRow++)
	{
		for (int nCol = 0; nCol < NValue; nCol++)
		{
			if (bVisited[nRow][nCol] == true || nMap[nRow][nCol] == 0) continue;
			 Value = BreadthFirstSearch(nRow, nCol);
			 if (Value > nMaxArea) nMaxArea = Value;

		}
	}
	
	cout << nIceNum << "\n";
	cout << nMaxArea << "\n";

}

int main()
{
	NValue = 1;
	vLInput.clear();
	int nInput = 0;

	freopen("input.txt", "r", stdin);
	cin >> N >> Q; 

	for (int i = 0; i < N; i++)
	{
		NValue *= 2;
	}
	
	for (int nRow = 0; nRow < NValue; nRow++)
	{
		for (int nCol = 0; nCol < NValue; nCol++)
		{
			cin >> nMap[nRow][nCol];
		}
	}


	for (int i = 0; i < Q; i++)
	{
		cin >> nInput;
		vLInput.push_back(nInput);
	}

	Solve();

	return 0;
}
