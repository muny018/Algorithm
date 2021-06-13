//SWE_2115_벌꿀채취

//문제
//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu

//해설
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int N, M, C, nAnswer, SelectSum, nMax, FirstSum, SecondSum;
int nMap[10][10], Select[5];
bool bVisited[10][10];
bool isContinue;

void dfs(int nNowCol, int a, int sum, int Price)
{
	if (sum > C) return;
	if (a == M) return;
	//nSum = nSum + Select[nNowCol] * Select[nNowCol];

	if (Price > nMax)
	{
		nMax = Price;
	}

	for (int i = nNowCol+1; i < M; i++)
	{
		dfs(i, a + 1, sum + Select[i], Price + (Select[i] * Select[i]));
		dfs(i, a + 1, sum , Price);
	}

}

int SearchBest(bool isFirst)
{

	nMax = 0;

	for (int i = 0; i < M; i++)
	{
		dfs(i, 1, Select[i], Select[i] * Select[i]);
	}

	return nMax;
}


int solve()
{
	int Tmpsum = 0;

	if (SelectSum > C)
	{
		Tmpsum = SearchBest(true);

	}
	else
	{
		for (int i = 0; i < M; i++)
		{
			Tmpsum = Tmpsum + (Select[i] * Select[i]);
		}
	}
	return Tmpsum;
}

void CheckVisited(int nRow, int nCol, int nLimited)
{
	for (int i = nCol; i < nCol + nLimited; i++)
	{
		bVisited[nRow][i] = true;
	}
}

void UnCheckVisited(int nRow, int nCol, int nLimited)
{
	for (int i = nCol; i < nCol + nLimited; i++)
	{
		bVisited[nRow][i] = false;
	}
}

void select()
{
	for (int FirstRow = 0; FirstRow < N; FirstRow++)
	{
		for (int FirstCol = 0; FirstCol < N; FirstCol++)
		{
			if (FirstCol + (M - 1) >= N) continue;
			CheckVisited(FirstRow, FirstCol, M);
			memset(Select, 0, sizeof(Select));
			SelectSum = 0;

			for (int i = 0; i < M; i++)
			{
				Select[i] = nMap[FirstRow][FirstCol + i];
				SelectSum = SelectSum + Select[i];
			}

			FirstSum = solve(); // 첫번째 선택 최적합 out

			for (int SecondRow = FirstRow; SecondRow < N; SecondRow++)
			{
				for (int SecondCol = 0; SecondCol < N; SecondCol++)
				{
					if (SecondCol + (M - 1) >= N) continue;
					//if (bVisited[SecondRow][SecondCol] == true) continue;
					isContinue = false;
					//CheckVisited(SecondRow, SecondCol, M);
					memset(Select, 0, sizeof(Select));
					SelectSum = 0;

					for (int i = 0; i < M; i++)
					{
						if (bVisited[SecondRow][SecondCol+i] == true)
						{
							isContinue = true;
							continue;
						}
						Select[i] = nMap[SecondRow][SecondCol + i];
						SelectSum = SelectSum + Select[i];
					}

					if (isContinue == true) continue;
					SecondSum = solve(); // 첫번째 선택 최적합 out

					//UnCheckVisited(SecondRow, SecondCol, M);

					if (FirstSum + SecondSum > nAnswer)
					{
						nAnswer = FirstSum + SecondSum;
					}
				}
			}

			UnCheckVisited(FirstRow, FirstCol, M);
		}

	}


}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int nTestCase = 1; nTestCase <= T; nTestCase++)
	{
		//초기화
		memset(nMap, 0, sizeof(nMap));
		memset(bVisited, 0, sizeof(bVisited));
		nAnswer = 0;

		//입력
		cin >> N >> M >> C;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> nMap[i][j];
			}

		}

		//풀이
		select();


		//출력
		cout << "#" << nTestCase << " " << nAnswer << endl;

	}//테케 끝

	return 0;
}