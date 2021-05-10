//BOJ 11559 »Ñ¿ä»Ñ¿ä

//¹®Á¦
//https://www.acmicpc.net/problem/11559

//ÇØ¼³
//

#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <iostream>
#include <cstring>
using namespace std;

char cInput;
int nMap[13][7] = { 0 };
bool bVisited[13][7] = { 0 };
int nAnswer = 0;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
bool IsBreak = false;

void Down()
{
	int nMapCopy[13][7] = { 0 };

	int DownQueSize = 0;
	int temp = 0;
	for (int j = 0; j < 6; j++)
	{
		queue <int> DownQue;


		for (int i = 11; i >= 0; i--)
		{
			if (nMap[i][j] == 0) continue;
			DownQue.push(nMap[i][j]);
		}

		DownQueSize = DownQue.size();
		for (int i = 0; i < DownQueSize; i++)
		{
			temp = DownQue.front();
			DownQue.pop();
			nMapCopy[11 - i][j] = temp;
		}


	}


	for (int i = 11; i >= 0; i--)
	{
		for (int j = 0; j < 6; j++)
		{
			nMap[i][j] = nMapCopy[i][j];
		}
	}


}

void BreadthFirstSearch(int nRow, int nCol)
{
	int nCurRow, nCurCol, nNextRow, nNextCol;
	queue <pair<int,int>> Que;
	queue<pair<int, int>> QueSave;
	Que.push(make_pair(nRow, nCol));
	QueSave.push(make_pair(nRow, nCol));

	while (!Que.empty())
	{
		nCurRow = Que.front().first;
		nCurCol = Que.front().second;
		Que.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nCurRow + dy[i];
			nNextCol = nCurCol + dx[i];

			if (nNextRow < 0 || nNextCol < 0 || nNextRow >= 12 || nNextCol >= 6) continue;
			if (bVisited[nNextRow][nNextCol]) continue;
			if (nMap[nCurRow][nCurCol] == nMap[nNextRow][nNextCol])
			{
				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));
				QueSave.push(make_pair(nNextRow, nNextCol));
			}

		}

	}

	int QueSaveSize = QueSave.size();
	if (QueSaveSize >= 4)
	{
		IsBreak = true;
		while (!QueSave.empty())
		{
			nCurRow = QueSave.front().first;
			nCurCol = QueSave.front().second;
			QueSave.pop();
			nMap[nCurRow][nCurCol] = 0;
		}

	}

}

int main()
{
	freopen("input.txt", "r", stdin);

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cin >> cInput;
			if (cInput == '.')
			{
				nMap[i][j] = 0;
			}
			else if (cInput == 'R')
			{
				nMap[i][j] = 1;
			}
			else if (cInput == 'G')
			{
				nMap[i][j] = 2;
			}
			else if (cInput == 'B')
			{
				nMap[i][j] = 3;
			}
			else if (cInput == 'P')
			{
				nMap[i][j] = 4;
			}
			else if (cInput == 'Y')
			{
				nMap[i][j] = 5;
			}
		}
	}

	bool Go = true;
	while (Go)
	{
		IsBreak = false;
		memset(bVisited, 0, sizeof(bVisited));
		for (int i = 11; i >= 0; i--)
		{
			for (int j = 0; j < 6; j++)
			{
				if (bVisited[i][j] || nMap[i][j] == 0) continue;
				bVisited[i][j] = true;
				BreadthFirstSearch(i, j);
			}
		}

		if (IsBreak)
		{
			nAnswer++;
			Down();
		}
		else
		{
			Go = false;
			break;
		}
	}

	cout << nAnswer << endl;


	return 0;
}

