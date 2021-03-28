//BOJ 배열돌리기4 210328

//문제
//https://www.acmicpc.net/problem/17406

//해설
//

/*
1) 인풋 받고
2) 순열
3) 벡터 값에 따라 회전회전 시퀀스
4) 최소값 찾기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

struct RotateInfo
{
	int nStartRow;
	int nStartCol;
	int nEndRow;
	int nEndCol;
};

int N, M, K;
int nMap[51][51] = { 0 };
int nInputMap[51][51] = { 0 };
int bVisited[6] = { 0 };
int nSelect[6] = { 0 };
vector <RotateInfo> Vec;
int nAnswer = 9999999;

void Rotate(int nStartRow, int nStartCol, int nEndRow, int nEndCol, int nSize)
{
	int nCopyMap[51][51] = { 0 };

	for (int i = nStartRow; i <= nEndRow; i++)
	{
		for (int j = nStartCol; j <= nEndCol; j++)
		{
			nCopyMap[i][j] = nMap[i][j];
		}
	}

	//상단
	nMap[nStartRow][nStartCol] = nCopyMap[nStartRow+1][nStartCol];
	for (int j = nStartCol+1; j <= nEndCol; j++)
	{
		nMap[nStartRow][j] = nCopyMap[nStartRow][j - 1];
	}

	//우측
	for (int i = nStartRow+1; i <= nEndRow; i++)
	{
		nMap[i][nEndCol] = nCopyMap[i - 1][nEndCol];
	}

	//하단
	for (int j = nStartCol; j <= nEndCol-1; j++)
	{
		nMap[nEndRow][j] = nCopyMap[nEndRow][j + 1];
	}

	//좌측
	for (int i = nStartRow; i <= nEndRow-1; i++)
	{
		nMap[i][nStartCol] = nCopyMap[i + 1][nStartCol];
	}

	if (nSize - 2 > 2)
	{
		Rotate(nStartRow + 1, nStartCol + 1, nEndRow - 1, nEndCol - 1, nSize - 2);
	}

}

void RotateSeq()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			nMap[i][j] = nInputMap[i][j];
		}
	}


	for (int i = 0; i < K; i++)
	{
		int nStartRow = Vec[nSelect[i]].nStartRow;
		int nStartCol = Vec[nSelect[i]].nStartCol;
		int nEndRow = Vec[nSelect[i]].nEndRow;
		int nEndCol = Vec[nSelect[i]].nEndCol;

		int nSize = nEndRow - nStartRow+1;

		Rotate(nStartRow, nStartCol, nEndRow, nEndCol, nSize);
	}

	int nValue = 0;
	int nResultValue = 9999999;
	for (int i = 0; i < N; i++)
	{
		nValue = 0;
		for (int j = 0; j < M; j++)
		{
			nValue += nMap[i][j];
		}

		if (nResultValue > nValue)  nResultValue = nValue;
	}


	if (nAnswer > nResultValue)  nAnswer = nResultValue;
}

void DepthFirstSearch(int nIndex, int nNum)
{
	if (nIndex >= K)
	{
		//추가
		RotateSeq();
		return;
	}

	for (int i = 0; i < K; i++)
	{
		if (bVisited[i]) continue;
		bVisited[i] = true;
		nSelect[nIndex] = i;
		DepthFirstSearch(nIndex+1, i);
		bVisited[i] = false;
	}

}

int main()
{
	RotateInfo Input;
	int r, c, s;
	freopen("input.txt", "r", stdin);
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> nInputMap[i][j];
		}
	}

	for (int i = 0; i < K; i++)
	{
		cin >> r >> c >> s;
		r--; c--;
		Input.nStartRow = r-s;
		Input.nStartCol = c-s;
		Input.nEndRow = r+s;
		Input.nEndCol = c+s;
		Vec.push_back(Input);
	}

	for (int i = 0; i < K; i++)
	{
		bVisited[i] = true;
		nSelect[0] = i;
		DepthFirstSearch(1,i);
		bVisited[i] = false;
	}
	
	cout << nAnswer << "\n"; 

	return 0;
}