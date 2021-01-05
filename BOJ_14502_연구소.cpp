//삼성 SW 역량테스트 기출
//BOJ 14502 연구소 BFS버젼

//헤매던 점
//Debug 에서 3초이상 걸렸었음, 근데 릴리즈(서버)에서는 통과됨

//문제
//https://www.acmicpc.net/problem/14502

//해설
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
using namespace std; 

int N, M;
int nMap[9][9] = { 0 };
int nAnswer = 0, nWallNum = 0; 
vector <pair<int, int>> Vec;
int dx[] = { 1, 0, -1, 0 }; 
int dy[] = { 0, 1, 0, -1 }; //동 남 서 북

int max(int a, int b)
{
	return a > b ? a : b;
}

void BreadthFirstSearch()
{
	int nSize = Vec.size(); 
	queue <pair<int, int>> Que;
	int nInputRow, nInputCol, nNextRow, nNextCol;
	bool bVisited[9][9] = { 0 };
	int nVirusNum = 0;

	for (int i = 0; i < nSize; i++)
	{
		nInputRow = Vec[i].first;
		nInputCol = Vec[i].second;

		bVisited[nInputRow][nInputCol] = true;
		Que.push(make_pair(nInputRow, nInputCol));
		nVirusNum++;
	}

	while (!Que.empty())
	{
		nInputRow = Que.front().first;
		nInputCol = Que.front().second;
		Que.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nInputRow + dy[i];
			nNextCol = nInputCol + dx[i];

			if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= M) continue; 
			if (bVisited[nNextRow][nNextCol]) continue; 
			if (nMap[nNextRow][nNextCol]) continue;

			bVisited[nNextRow][nNextCol] = true;
			nVirusNum++;
			Que.push(make_pair(nNextRow, nNextCol));
		}
	}

	int nResult = N*M - nWallNum - nVirusNum;
	nAnswer = max(nAnswer, nResult);

}


int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] == 2)
			{
				Vec.push_back(make_pair(i, j));
			}
			else if (nMap[i][j] == 1)
			{
				nWallNum++;
			}
		}
	}

	nWallNum = nWallNum + 3;

	//벽세우기
	for (int FirstRow = 0; FirstRow < N; FirstRow++)
	{
		for (int FirstCol = 0; FirstCol < M; FirstCol++)
		{
			if (nMap[FirstRow][FirstCol]) continue;
			for (int SecondRow = 0; SecondRow < N; SecondRow++)
			{
				for (int SecondCol = 0; SecondCol < M; SecondCol++)
				{
					if (nMap[SecondRow][SecondCol]) continue;
					for (int ThirdRow = 0; ThirdRow < N; ThirdRow++)
					{
						for (int ThirdCol = 0; ThirdCol < M; ThirdCol++)
						{
							if (nMap[ThirdRow][ThirdCol]) continue;
							if (FirstRow == SecondRow && FirstCol == SecondCol) continue;
							if (FirstRow == ThirdRow && FirstCol == ThirdCol) continue;
							if (ThirdRow == SecondRow && ThirdCol == SecondCol) continue;

							if (!nMap[FirstRow][FirstCol] && !nMap[SecondRow][SecondCol] &&
								!nMap[ThirdRow][ThirdCol])
							{
								nMap[FirstRow][FirstCol] = 1;
								nMap[SecondRow][SecondCol] = 1;
								nMap[ThirdRow][ThirdCol] = 1;

								BreadthFirstSearch();

								nMap[FirstRow][FirstCol] = 0;
								nMap[SecondRow][SecondCol] = 0;
								nMap[ThirdRow][ThirdCol] = 0;
							}
							

						}
					}
				}
			}
		}
	}

	cout << nAnswer << endl;

	return 0;
}