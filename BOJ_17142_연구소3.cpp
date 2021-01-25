//삼성 역량테스트 기출 
//2019년 상반기 CE/IM 오전
//BOJ 17142 연구소3

//문제
//https://www.acmicpc.net/problem/17142

//해설
//https://yabmoons.tistory.com/254

//실패한 점
//활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다.
//Map을 다 돌았을 때, 비활성 -> 활성 된경우 Queue에 들어가는데 그 때 시간이 늘어남
// 이걸 해결못하겠음.
// -> Que 끝나고 Time++을 할게 아니라 Map에 적는다.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

vector <pair<int, int>> Vec;
int N, M, ZeroNum = 0, nVecSize = 0;
int nMap[51][51] = { 0 };
int nMapCopy[51][51] = { 0 };
int nAnswer = 999999;
bool bVisited[11] = { false };
int dx[] = { 1,0,-1,0 }; //동남서북
int dy[] = { 0,1,0,-1 };
bool bIsPossible = false;


void BFS()
{
	int nNowRow, nNowCol, nNextRow, nNextCol;
	int nVirusNum = 0, MaxNum = 0;
	int nQueSize = 0;

	memset(nMapCopy, -1, sizeof(nMapCopy));

	queue <pair<int, int>> Que;
	for (int i = 0; i < nVecSize; i++)
	{
		if (bVisited[i])
		{
			Que.push(make_pair(Vec[i].first, Vec[i].second));
			nMapCopy[Vec[i].first][Vec[i].second] = 0;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j] == 1) nMapCopy[i][j] = -9;
		}
	}


	while (!Que.empty())
	{
		nQueSize = Que.size();
		for (int j = 0; j < nQueSize; j++)
		{
			nNowRow = Que.front().first;
			nNowCol = Que.front().second;
			Que.pop();

			for (int i = 0; i < 4; i++)
			{
				nNextRow = nNowRow + dy[i];
				nNextCol = nNowCol + dx[i];

				if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= N) continue;
				if (nMap[nNextRow][nNextCol] != 1 && nMapCopy[nNextRow][nNextCol] == -1)
				{
					Que.push(make_pair(nNextRow, nNextCol));
					nMapCopy[nNextRow][nNextCol] = nMapCopy[nNowRow][nNowCol] + 1;

					if (nMap[nNextRow][nNextCol] == 0)
					{
						nVirusNum++;
						MaxNum = nMapCopy[nNextRow][nNextCol];
					}
				}
								
			}
		}
	}

	if (ZeroNum == nVirusNum && nAnswer> MaxNum  )
	{
		nAnswer = MaxNum;
	}

}

void DepthFirstSearch(int nIndex, int Num)
{
	if (Num >= M)
	{
		BFS();
		return;
	}

	if (nIndex > nVecSize) return;

	bVisited[nIndex] = true;
	DepthFirstSearch(nIndex + 1, Num + 1);
	bVisited[nIndex] = false;
	DepthFirstSearch(nIndex + 1, Num);

}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] == 2)
			{
				Vec.push_back(make_pair(i, j));
			}
			else if (nMap[i][j] == 0)
			{
				ZeroNum++;
			}
		}
	}
	nVecSize = Vec.size();

	int nCount = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j]) nCount++;
		}
	}

	if (nCount == N * N)
	{
		cout << "0" << endl;
		return 0;
	}

	DepthFirstSearch(0, 0);

	if (nAnswer == 999999)
	{
		cout << "-1" << endl;
	}
	else
	{
		cout << nAnswer << endl;
	}

	return 0;
}