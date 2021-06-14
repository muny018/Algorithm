// SWE 2117 홈 방범 서비스

//문제
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu

//해설
// 

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std; 

int nAnswer, N, M;
bool nMap[20][20];
int Price[22];

bool ChkRange(int nRow, int nCol)
{
	if (nRow < 0 || nCol < 0 || nRow >= N || nCol >= N)
	{
		return false;
	}

	return true;
}

int solve(int nRow, int nCol, int k)
{
	int cnt = 0;

	//상 하단
	int UpStartRow, DownStartRow, StartCol, Length;

	for (int i = 1; i <= k - 1; i++)
	{
		UpStartRow = nRow - (k - i);
		DownStartRow = nRow + k - i;

		Length = i*2 -1;
		StartCol = nCol - i+1;

		for (int j = StartCol; j < StartCol + Length; j++)
		{
			if (ChkRange(UpStartRow, j) == true && nMap[UpStartRow][j] == true) cnt++;
			if (ChkRange(DownStartRow, j) == true && nMap[DownStartRow][j] == true) cnt++;
		}

	}

	// 중단
	Length = k * 2 - 1;
	StartCol = nCol - (k - 1);

	for (int i = StartCol; i < StartCol + Length; i++)
	{
		if (ChkRange(nRow, i) == true && nMap[nRow][i] == true) cnt++;
	}
	
	if (cnt * M - Price[k] < 0)
	{
		cnt = 0;
	}

	return cnt;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T, nCount;
	cin >> T;

	memset(Price, 0, sizeof(Price));

	for (int i = 1; i <= 22; i++)
	{
		if (Price[i] != 0) continue;
		Price[i] = i*i + (i - 1)*(i - 1);
	}


	for (int nTestCase = 1; nTestCase <= T; nTestCase++)
	{
		//초기화
		nAnswer = 0;
		memset(nMap, 0, sizeof(nMap));

		//입력
		cin >> N >> M;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> nMap[i][j];
			}
		}

		//풀이 
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int k = 1; k <= N + 1; k++)
				{
					if (i == 3 && j == 3 && k == 4)
					{
						int hold = 0;
					}
					nCount = solve(i, j, k);

					if (nCount > nAnswer)
					{
						nAnswer = nCount;
					}
				}
			}
		}
		
		//출력
		cout << "#" << nTestCase << " " << nAnswer << endl;
				
	}// 테케 끝

	return 0;
}
