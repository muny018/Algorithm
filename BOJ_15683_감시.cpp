//삼성 역량테스트 기출
//BOJ 15683 감시

//헤매던 점
// 잠 올때봐서 그런지 처음 어떻게 풀어야할지 구상을 못하고 전에 풀었던 데이터 컨닝한점 ..?

//문제
//https://www.acmicpc.net/problem/15683

//해설
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M, nVecSize =0; 
int nMap[9][9] = { 0 };
int bVisited[9][9] = { 0 };
vector <pair <int, int> > Vec;
vector <int> CCTV;
int dx[] = { 0, 1, 0, -1 }; //북동남서
int dy[] = { -1, 0, 1, 0 };
int nAnswer = 9999999;

void Calc()
{
	int nResult = 0; 

	for (int i = 0; i < nVecSize; i++)
	{
		bVisited[Vec[i].first][Vec[i].second] += 1;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (bVisited[i][j] == 0) nResult++;
		}
	}

	if (nResult < nAnswer)
	{
		nAnswer = nResult;
	}

}

void Visited(int nRow, int nCol, int nDir, bool IsVisit)
{
	if (IsVisit == true)
	{
		bVisited[nRow][nCol] = true;
		while (true)
		{
			int nNextRow = nRow + dy[nDir];
			int nNextCol = nCol + dx[nDir];

			if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= M) break;
			if (nMap[nNextRow][nNextCol] == 6) break;

			bVisited[nNextRow][nNextCol] += 1;
			nRow = nNextRow, nCol = nNextCol;
		}

	}
	else //해제
	{
		bVisited[nRow][nCol] = false;
		while (true)
		{
			int nNextRow = nRow + dy[nDir];
			int nNextCol = nCol + dx[nDir];

			if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= M) break;
			if (nMap[nNextRow][nNextCol] == 6) break;

			bVisited[nNextRow][nNextCol] -= 1;
			nRow = nNextRow, nCol = nNextCol;
		}
	}

}

void DepthFirstSearch(int nIndex)
{
	if (nIndex == nVecSize)
	{
		Calc();
		return;
	}

	int CCTVNum = CCTV[nIndex];
	int nRow = Vec[nIndex].first;
	int nCol = Vec[nIndex].second;


	if (CCTVNum == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			Visited(nRow, nCol, i, true);
			DepthFirstSearch(nIndex + 1);
			Visited(nRow, nCol, i, false);
		}
	}
	else if(CCTVNum == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			Visited(nRow, nCol, i, true);
			Visited(nRow, nCol, i+2, true);
			DepthFirstSearch(nIndex + 1);
			Visited(nRow, nCol, i, false);
			Visited(nRow, nCol, i + 2, false);
		}
	}
	else if (CCTVNum == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			Visited(nRow, nCol, i, true);
			Visited(nRow, nCol, (i + 1)%4, true);
			DepthFirstSearch(nIndex + 1);
			Visited(nRow, nCol, i, false);
			Visited(nRow, nCol, (i + 1) % 4, false);
		}
	}
	else if (CCTVNum == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			Visited(nRow, nCol, i, true);
			Visited(nRow, nCol, (i + 1) % 4, true);
			Visited(nRow, nCol, (i + 3) % 4, true);
			DepthFirstSearch(nIndex + 1);
			Visited(nRow, nCol, i, false);
			Visited(nRow, nCol, (i + 1) % 4, false);
			Visited(nRow, nCol, (i + 3) % 4, false);
		}
	}
	else if (CCTVNum == 5)
	{
		for (int i = 0; i < 4; i++)
		{
			Visited(nRow, nCol, i, true);
		}

			DepthFirstSearch(nIndex + 1);

		for (int i = 0; i < 4; i++)
		{
			Visited(nRow, nCol, i, false);
		}
		
	}
	else
	{
		return;
	}


}

int main()
{
	Vec.clear();
	freopen("input.txt", "r", stdin);
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] && nMap[i][j] != 6)
			{
				Vec.push_back(make_pair(i, j));
				CCTV.push_back(nMap[i][j]);
			}
			if (nMap[i][j] == 6)
			{
				bVisited[i][j] +=1;
			}
		}
	}
	nVecSize = Vec.size();
	

	DepthFirstSearch(0);

	cout << nAnswer << endl;


	return 0;
}