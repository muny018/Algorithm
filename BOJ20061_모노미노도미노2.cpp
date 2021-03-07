//BOJ20061_모노미노도미노2

//문제
//https://www.acmicpc.net/problem/20061

//해설
//

#define _CRT_SECURE_NO_WARNINGS
#define BlurLineStart 4
#define MaxLine 9

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std; 

vector <pair <int, pair <int, int>>> InputVec;
int nGreenMap[10][4];
int nBlueMap[4][10];
int N;
int nScore = 0;

void RedtoBlueShift(int t, int nCurRow, int nCurCol)
{
	int nMaxCol = MaxLine;
	int nNext = 0;

	if (t == 1) //1x1 블럭
	{
		nNext = 1;
		while (true)
		{
			if (nCurCol + nNext == 10)
			{
				nMaxCol = MaxLine;
				break;
			}

			if (nBlueMap[nCurRow][nCurCol + nNext] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxCol = nCurCol + nNext - 1;
				break;
			}
		}

		nBlueMap[nCurRow][nMaxCol] = 1;
	}
	else if (t == 2) //1x2 가로 블럭
	{
		nNext = 1;
		nCurCol++;
		while (true)
		{
			if (nCurCol + nNext == 10)
			{
				nMaxCol = MaxLine;
				break;
			}

			if (nBlueMap[nCurRow][nCurCol + nNext] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxCol = nCurCol + nNext - 1;
				break;
			}
		}

		nBlueMap[nCurRow][nMaxCol] = 1;
		nBlueMap[nCurRow][nMaxCol-1] = 1;
	}
	else if (t == 3) //2x1 세로 블럭
	{
		nNext = 1;
		int nMaxCol2 = MaxLine;
		int nResultCol = 0;

		//
		while (true)
		{
			if (nCurCol + nNext == 10)
			{
				nMaxCol = MaxLine;
				break;
			}

			if (nBlueMap[nCurRow][nCurCol + nNext] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxCol = nCurCol + nNext - 1;
				break;
			}
		}

		//두번째
		nCurRow++;
		nNext = 1;
		while (true)
		{
			if (nCurCol + nNext == 10)
			{
				nMaxCol2 = MaxLine;
				break;
			}

			if (nBlueMap[nCurRow][nCurCol + nNext] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxCol2 = nCurCol + nNext - 1;
				break;
			}
		}

		nResultCol = min(nMaxCol, nMaxCol2);

		nBlueMap[nCurRow][nResultCol] = 1;
		nBlueMap[nCurRow-1][nResultCol] = 1;
	}

}

void RedtoGreenShift(int t, int nCurRow, int nCurCol)
{
	int nMaxRow = MaxLine;
	int nNext = 0;

	if (t == 1) //1x1 블럭
	{
		nNext = 1;
		while (true)
		{
			if (nCurRow + nNext == 10) 
			{
				nMaxRow = MaxLine;
				break;
			}

			if (nGreenMap[nCurRow + nNext][nCurCol] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxRow = nCurRow + nNext - 1;
				break;
			}
		}

		nGreenMap[nMaxRow][nCurCol] = 1;
	}
	else if (t == 2) //1x2 가로 블럭
	{
		nNext = 1;
		int nMaxRow2 = MaxLine;
		int nResultRow = 0;
		//첫번쨰 Row
		while (true)
		{
			if (nCurRow + nNext == 10)
			{
				nMaxRow = MaxLine;
				break;
			}

			if (nGreenMap[nCurRow + nNext][nCurCol] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxRow = nCurRow + nNext - 1;
				break;
			}
		}

		//두번쨰 Row
		nCurCol++;
		nNext = 1;
		while (true)
		{
			if (nCurRow + nNext == 10)
			{
				nMaxRow2 = MaxLine;
				break;
			}

			if (nGreenMap[nCurRow + nNext][nCurCol] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxRow2 = nCurRow + nNext - 1;
				break;
			}
		}

		nResultRow = min(nMaxRow, nMaxRow2);


		nGreenMap[nResultRow][nCurCol] = 1;
		nGreenMap[nResultRow][nCurCol-1] = 1;
	}
	else if (t == 3) //2x1 세로 블럭
	{
		nNext = 1;
		nCurRow++;
		while (true)
		{
			if (nCurRow + nNext == 10)
			{
				nMaxRow = MaxLine;
				break;
			}

			if (nGreenMap[nCurRow + nNext][nCurCol] == 0)
			{
				nNext++;
			}
			else
			{
				nMaxRow = nCurRow + nNext - 1;
				break;
			}
		}

		nGreenMap[nMaxRow][nCurCol] = 1;
		nGreenMap[nMaxRow-1][nCurCol] = 1;
	}
}

void MoveGreenLine(int nEndRow)
{
	int nCopyGreenMap[10][4] = { 0 };

	//copy
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			nCopyGreenMap[i][j] = nGreenMap[i][j];
		}
	}

	for (int i = 4; i <= nEndRow; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			nGreenMap[i][j] = nCopyGreenMap[i-1][j];
		}
	}
}

void MoveBlueLine(int nEndCol)
{
	int nCopyBlueMap[4][10] = { 0 };

	//copy
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			nCopyBlueMap[i][j] = nBlueMap[i][j];
		}
	}

	for (int i = 0; i <= 3; i++)
	{
		for (int j = 4; j <= nEndCol; j++)
		{
			nBlueMap[i][j] = nCopyBlueMap[i][j-1];
		}
	}
}

void CheckScore()
{
	int nMaxLine = MaxLine;
	bool bScoreUp = true;

	//Green
	for (int nRow = nMaxLine; nRow >= 4; nRow--)
	{
		bScoreUp = true;
		for (int nCol = 0; nCol <= 3; nCol++)
		{
			if (nGreenMap[nRow][nCol] == 0)
			{
				bScoreUp = false;
				break;
			}
		}

		if (bScoreUp == true)
		{
			nScore++;
			MoveGreenLine(nRow);
			CheckScore();
		}
	}

	//Blue
	for (int nCol = nMaxLine; nCol >= 4; nCol--)
	{
		bScoreUp = true;
		for (int nRow = 0; nRow <= 3; nRow++)
		{
			if (nBlueMap[nRow][nCol] == 0)
			{
				bScoreUp = false;
				break;
			}
		}

		if (bScoreUp == true)
		{
			nScore++;
			MoveBlueLine(nCol);
			CheckScore();
		}
	}

}

void BlurLineCheck()
{
	int nBlurLineStart = BlurLineStart;
	int nCount;
	//Green
	nCount = 0;
	for (int nRow = nBlurLineStart; nRow <= nBlurLineStart + 1; nRow++)
	{
		for (int nCol = 0; nCol <= 3; nCol++)
		{
			if (nGreenMap[nRow][nCol])
			{
				nCount++;
				break;
			}
		}
	}
	
	for (int i = 0; i < nCount; i++)
	{
		MoveGreenLine(9);
	}


	//Blue
	nCount = 0;
	for (int nCol = nBlurLineStart; nCol <= nBlurLineStart + 1; nCol++)
	{
		for (int nRow = 0; nRow <= 3; nRow++)
		{
			if (nBlueMap[nRow][nCol])
			{
				nCount++;
				break;
			}
		}
	}

	for (int i = 0; i < nCount; i++)
	{
		MoveBlueLine(9);
	}

}
void solve()
{
	int t, nRow, nCol;
	for (int nTime = 0; nTime < N; nTime++)
	{
		t = InputVec[nTime].first;
		nRow = InputVec[nTime].second.first;
		nCol = InputVec[nTime].second.second;

		//옮기기
		RedtoGreenShift(t, nRow, nCol);
		RedtoBlueShift(t, nRow, nCol);

		//점수확인
		CheckScore();

		//연한라인확인
		BlurLineCheck();
	}

	//파란색보드 초록색보드 타일에 있는 칸의 갯수
	int nSum = 0;
	int nBlurLineStart = BlurLineStart;
	int nMaxLine = MaxLine;

	//초록
	for (int nRow = nBlurLineStart; nRow <= nMaxLine; nRow++)
	{
		for (int nCol = 0; nCol <= 3; nCol++)
		{
			if (nGreenMap[nRow][nCol]) nSum++;
		}
	}

	//파랑
	for (int nCol = nBlurLineStart; nCol <= nMaxLine; nCol++)
	{
		for (int nRow = 0; nRow <= 3; nRow++)
		{
			if (nBlueMap[nRow][nCol]) nSum++;
		}
	}

	cout << nScore << "\n";
	cout << nSum << "\n";
}

int main()
{
	int t, nRow, nCol;
	freopen("input.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> t >> nRow >> nCol;
		InputVec.push_back(make_pair(t, make_pair(nRow, nCol)));
	}

	solve();

	return 0;
}