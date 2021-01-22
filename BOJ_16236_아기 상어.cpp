//삼성 역량테스트 기출
//BOJ 16236 아기 상어

//헤매던 점
// 무한루프에 빠져 시간초과에 헤맸음, 그러나 2시간쯤 지날 때 해결함
// 초기에 짠 코드는 작은 물고기가 구석 모서리에 있고, 가는길을 큰물고기가 막은 경우 
// 무한루프에 빠졌었음. 실전이었다면 모든 히든 테케를 알 수 없기 때문에 1솔로 착각하고 면접 못갓을꺼임
// 해결책 : 문제를 잘 이해하고 반례를 빠른시간에 생각하고 설계를 잘해야함.

//문제
//https://www.acmicpc.net/problem/16236

//해설
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int nMap[21][21] = { 0 };
int nAnswer = 0;
int Shark_Row = 0, Shark_Col = 0, nShark_Size = 2;
int dx[] = { 0, -1, 1, 0 }; //북서동남
int dy[] = { -1, 0, 0, 1 };
int SharkUp[9] = { 0 };

void BreadthFirstSearch(int nRow, int nCol)
{
	queue <pair <int, int> > Que;
	vector <pair <int, int> > Vec;
	bool bVisited[21][21] = { 0 };
	Que.push(make_pair(nRow, nCol));
	bool IsStop = false;
	int nResult = 0, nDistanceMin = 99999999;

	while (!Que.empty())
	{
		int nQueSize = Que.size();
		bool IsStop = false;

		for (int Quesize = 0; Quesize < nQueSize; Quesize++)
		{
			int nCurRow = Que.front().first;
			int nCurCol = Que.front().second;
			bVisited[nCurRow][nCurCol] = true;
			Que.pop();

			if (nResult > nDistanceMin) continue;

			for (int i = 0; i < 4; i++)
			{
				int nNextRow = nCurRow + dy[i];
				int nNextCol = nCurCol + dx[i];
				if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= N) continue;
				if (bVisited[nNextRow][nNextCol]) continue;
				if (nShark_Size < nMap[nNextRow][nNextCol]) continue; //자신보다 큰 물고기 못지나감

				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));

				if (nMap[nNextRow][nNextCol] && nShark_Size > nMap[nNextRow][nNextCol] && nResult <= nDistanceMin) //물고기 먹음
				{
					nDistanceMin = nResult;
					Vec.push_back(make_pair(nNextRow, nNextCol));
					int stop = 0;
				}
			}
		}
		nResult++;
	}

	if (Vec.size()) //잡아먹을 물고기가 존재
	{
		sort(Vec.begin(), Vec.end());
		nAnswer += nDistanceMin + 1;
		Shark_Row = Vec[0].first; Shark_Col = Vec[0].second;
		nMap[Shark_Row][Shark_Col] = 0;


		if (nShark_Size <= 6 && SharkUp[nShark_Size])
		{
			SharkUp[nShark_Size]--;
			if (SharkUp[nShark_Size] <= 0) nShark_Size++;
		}
		Vec.clear();
		BreadthFirstSearch(Shark_Row, Shark_Col);
		return;
	}

	return;
}

bool SearchFish()
{
	bool IsGo = false;

	//먹을 수 있는 물고기 최소거리 찾음
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j] && nShark_Size > nMap[i][j])
			{
				IsGo = true;
			}
		}
	}

	return IsGo;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] == 9)
			{
				Shark_Row = i;
				Shark_Col = j;
				nMap[i][j] = 0;
			}
		}
	}

	for (int i = 1; i <= 7; i++)
	{
		SharkUp[i] = i;
	}

	//풀이

	BreadthFirstSearch(Shark_Row, Shark_Col);


	//출력
	cout << nAnswer << endl;

	return 0;
}




/* @@@@@@@@@@@@@@@@@@@@@@@삽질했던 코드@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2
//삼성 역량테스트 기출
//BOJ 16236 아기 상어

//헤매던 점
//

//문제
//https://www.acmicpc.net/problem/16236

//해설
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int nMap[21][21] = { 0 };
int nAnswer = 0;
int Shark_Row = 0, Shark_Col = 0, nShark_Size = 2;
int dx[] = { 0, -1, 1, 0 }; //북서동남
int dy[] = { -1, 0, 0, 1 };
int SharkUp[9] = { 0 };

void BreadthFirstSearch(int nRow, int nCol)
{
	queue <pair <int, int> > Que;
	vector <pair <int, int> > Vec;
	bool bVisited[21][21] = { 0 };
	Que.push(make_pair(nRow, nCol));
	bool IsStop = false;
	int nResult = 0, nDistanceMin = 99999999;

	while (!Que.empty())
	{
		int nQueSize = Que.size();
		bool IsStop = false;

		for (int Quesize = 0; Quesize < nQueSize; Quesize++)
		{
			int nCurRow = Que.front().first;
			int nCurCol = Que.front().second;
			bVisited[nCurRow][nCurCol] = true;
			Que.pop();

			if (nResult > nDistanceMin) continue;

			for (int i = 0; i < 4; i++)
			{
				int nNextRow = nCurRow + dy[i];
				int nNextCol = nCurCol + dx[i];
				if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= N) continue;
				if (bVisited[nNextRow][nNextCol]) continue;
				if (nShark_Size < nMap[nNextRow][nNextCol]) continue; //자신보다 큰 물고기 못지나감

				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));

				if (nMap[nNextRow][nNextCol] && nShark_Size > nMap[nNextRow][nNextCol] && nResult <= nDistanceMin) //물고기 먹음
				{
					nDistanceMin = nResult;
					Vec.push_back(make_pair(nNextRow, nNextCol));
					int stop = 0;
				}
			}
		}
		nResult++;

		if (Vec.size()) //잡아먹을 물고기가 존재
		{
			sort(Vec.begin(), Vec.end());
			nAnswer += nDistanceMin + 1;
			Shark_Row = Vec[0].first; Shark_Col = Vec[0].second;
			nMap[Shark_Row][Shark_Col] = 0;


			if (nShark_Size <= 6 && SharkUp[nShark_Size])
			{
				SharkUp[nShark_Size]--;
				if (SharkUp[nShark_Size] <= 0) nShark_Size++;
			}
			Vec.clear();

			return;
		}
	}


	return;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@삽질했던 함수 부분@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool SearchFish()
{
	bool IsGo = false;

	//먹을 수 있는 물고기 최소거리 찾음
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j] && nShark_Size > nMap[i][j])
			{
				IsGo = true;
			}
		}
	}

	return IsGo;
}
//만약 작은 물고기가 맨 구석 코너에 있고 가는길을 큰물고기가 가로막으면 무한루프 돔
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main()
{
	//freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] == 9)
			{
				Shark_Row = i;
				Shark_Col = j;
				nMap[i][j] = 0;
			}
		}
	}

	for (int i = 1; i <= 7; i++)
	{
		SharkUp[i] = i;
	}

	//풀이
	while (true)
	{
		//잡아먹을 물고기 있냐?
		if (!SearchFish()) break;

		BreadthFirstSearch(Shark_Row, Shark_Col);
	}

	//출력
	cout << nAnswer << endl;

	return 0;
}
*/
