//삼성 역량테스트 기출
//BOJ 17144 아기 상어

//헤매던 점

// 해결책 : 

//문제
//https://www.acmicpc.net/problem/17144

//해설
//얘는 BFS로 풀었네
//https://godz.tistory.com/21

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

int nMap[51][51] = { 0 };
int R, C, T;
int nRowPos, nColPos;
int nAnswer;

void Operate()
{
	int nMapCopy[51][51] = { 0 };

	for (int nRow = 0; nRow < R; nRow++)
	{
		for (int nCol = 0; nCol < C; nCol++)
		{
			nMapCopy[nRow][nCol] = nMap[nRow][nCol];
		}
	}


	//위쪽

	for (int nNextCol = nColPos + 2; nNextCol < C; nNextCol++)
	{

		nMapCopy[nRowPos][nNextCol] = nMap[nRowPos][nNextCol - 1];
	}

	for (int nNextRow = nRowPos - 1; nNextRow >= 0; nNextRow--)
	{
		nMapCopy[nNextRow][C - 1] = nMap[nNextRow + 1][C - 1];
	}

	for (int nNextCol = C - 2; nNextCol >= 0; nNextCol--)
	{

		nMapCopy[0][nNextCol] = nMap[0][nNextCol + 1];
	}

	for (int nNextRow = 1; nNextRow < nRowPos; nNextRow++)
	{
		nMapCopy[nNextRow][0] = nMap[nNextRow - 1][0];
	}

	nMapCopy[nRowPos][nColPos + 1] = 0;

	//밑쪽
	nRowPos++;
	for (int nNextCol = nColPos + 2; nNextCol < C; nNextCol++)
	{
		nMapCopy[nRowPos][nNextCol] = nMap[nRowPos][nNextCol - 1];
	}

	for (int nNextRow = nRowPos + 1; nNextRow < R; nNextRow++)
	{
		nMapCopy[nNextRow][C - 1] = nMap[nNextRow - 1][C - 1];
	}

	for (int nNextCol = C - 2; nNextCol >= 0; nNextCol--)
	{

		nMapCopy[R - 1][nNextCol] = nMap[R - 1][nNextCol + 1];
	}

	for (int nNextRow = R - 2; nNextRow > nRowPos; nNextRow--)
	{
		nMapCopy[nNextRow][0] = nMap[nNextRow + 1][0];
	}

	nMapCopy[nRowPos][nColPos + 1] = 0;



	memset(nMap, 0, sizeof(nMap));
	for (int nRow = 0; nRow < R; nRow++)
	{
		for (int nCol = 0; nCol < C; nCol++)
		{
			nMap[nRow][nCol] = nMapCopy[nRow][nCol];
		}
	}

	nRowPos--;

}

void Expand()
{
	int nMapCopy[51][51] = { 0 };
	int nCount = 0;
	int nValue = 0;

	for (int nRow = 0; nRow < R; nRow++)
	{
		for (int nCol = 0; nCol < C; nCol++)
		{
			nCount = 0;
			if (nMap[nRow][nCol] != 0)
			{
				nValue = nMap[nRow][nCol] / 5;
				for (int i = nRow - 1; i <= nRow + 1; i++)
				{
					if (i < 0 || i >= R) continue;
					if (nMap[i][nCol] == -1) continue;
					if (i == nRow) continue;
					nCount++;
					nMapCopy[i][nCol] += nValue;
				}

				for (int j = nCol - 1; j <= nCol + 1; j++)
				{
					if (j < 0 || j >= C) continue;
					if (nMap[nRow][j] == -1) continue;
					if (j == nCol) continue;
					nCount++;
					nMapCopy[nRow][j] += nValue;
				}

				nMapCopy[nRow][nCol] += nMap[nRow][nCol] - nValue*nCount;

			}
		}
	}

	memset(nMap, 0, sizeof(nMap));
	for (int nRow = 0; nRow < R; nRow++)
	{
		for (int nCol = 0; nCol < C; nCol++)
		{
			nMap[nRow][nCol] = nMapCopy[nRow][nCol];
		}
	}

}

void init()
{
	for (int i = 0; i < 51; i++)
	{
		for (int j = 0; j < 51; j++)
		{
			nMap[i][j] = 0;
		}
	}
	nRowPos = -1;
	nColPos = -1;
	nAnswer = 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> R >> C >> T;
	init();

	//입력
	for (int nRow = 0; nRow < R; nRow++)
	{
		for (int nCol = 0; nCol < C; nCol++)
		{
			cin >> nMap[nRow][nCol];
			if (nMap[nRow][nCol] == -1 && nRowPos == -1 && nColPos == -1)
			{
				nRowPos = nRow;
				nColPos = nCol;
			}
		}
	}

	for (int nTime = 1; nTime <= T; nTime++)
	{
		//연산
		Expand();
		Operate();
	}
	//결과

	for (int nRow = 0; nRow < R; nRow++)
	{
		for (int nCol = 0; nCol < C; nCol++)
		{
			if (nMap[nRow][nCol] == -1) continue;
			nAnswer += nMap[nRow][nCol];
		}
	}
	int stop_a = 0;
	cout << nAnswer << endl;


	return 0;
}