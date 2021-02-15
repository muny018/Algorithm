//BOJ 17472 �ٸ� �����

//����
//https://www.acmicpc.net/problem/17472

//�ؼ�
//https://yabmoons.tistory.com/292

//��Ŵ� ��
// A�� �����ε�.. ������� �յ� ����

#define _CRT_SECURE_NO_WARNINGS
#define INF 1000

#include <queue>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M, Area_Num;
int nAnswer = INF;
int nMap[10][10] = { 0 };
int Label[10][10] = { 0 };
int Dist[7][7] = { 0 }; // �� ���� �ִܰŸ��� �����ϱ� ���� �迭
						// Dist[a][b] =c   -> a�� b�� �ִܰŸ��� c��.

bool bVisited[10][10] = { 0 }; // �� �󺧸� �� �� �湮üũ��
bool Connect[7][7] = { false };
bool ConnectIsland[7] = { false };
bool Select[7 * 7] = { false };

vector <pair<int, int> > InputVec;
vector <pair<int, int>> Area_Pos[7];
vector <pair<pair<int, int>, int>> BridgeList;

int dx[] = { 1,0,-1,0 }; //��������
int dy[] = { 0, 1, 0, -1 };

void DFS(int nCurRow, int nCurCol, int Dir, int B_Size, int nStart, int nEnd)
{
	int nxRow = nCurRow + dy[Dir];
	int nxCol = nCurCol + dx[Dir];

	if (nxRow < 0 || nxRow >= N || nxCol < 0 || nxCol >= M) return;

	if (nMap[nxRow][nxCol] == 0)
	{
		DFS(nxRow, nxCol, Dir, B_Size + 1, nStart, nEnd);
	}
	else if (nMap[nxRow][nxCol] == 1)
	{
		if (Label[nxRow][nxCol] == nEnd)
		{
			if (B_Size > 1)
			{
				if (Dist[nStart][nEnd] > B_Size)
				{
					Dist[nStart][nEnd] = B_Size;
					Dist[nEnd][nStart] = B_Size;
				}
				return;
			}
		}
		else
		{
			return;
		}
	}

}

void MakeBridge(int nStart, int nEnd)
{
	int nVecSize = Area_Pos[nStart].size();
	for (int i = 0; i < nVecSize; i++)
	{
		int nCurRow = Area_Pos[nStart][i].first;
		int nCurCol = Area_Pos[nStart][i].second;

		for (int j = 0; j < 4; j++)
		{
			int nNextRow = nCurRow + dy[j];
			int nNextCol = nCurCol + dx[j];

			if (nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= M) continue;
			if (nMap[nNextRow][nNextCol] == 0)
			{
				DFS(nCurRow, nCurCol, j, 0, nStart,nEnd);
			}
		}
	}

}

void FindDistance()
{
	for (int i = 1; i < Area_Num; i++)
	{
		for (int j = i + 1; j < Area_Num; j++)
		{
			MakeBridge(i, j);
			if (Dist[i][j] == INF) continue;
			BridgeList.push_back(make_pair(make_pair(i,j), Dist[i][j]));
		}
	}
	
}

void BFS(int nRow, int nCol, int Num)
{
	int nCurRow = 0, nCurCol = 0;
	int nNextRow = 0, nNextCol = 0;
	queue <pair<int, int>> Que;

	Que.push(make_pair(nRow, nCol));
	bVisited[nRow][nCol] = true;
	Area_Pos[Num].push_back(make_pair(nRow, nCol));
	Label[nRow][nCol] = Num;

	while (!Que.empty())
	{
		nCurRow = Que.front().first;
		nCurCol = Que.front().second;
		Que.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nCurRow + dy[i];
			nNextCol = nCurCol + dx[i];
			if (nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= M) continue;
			if (nMap[nNextRow][nNextCol] == 1 && bVisited[nNextRow][nNextCol] == 0)
			{
				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));
				Label[nNextRow][nNextCol] = Num;
				Area_Pos[Num].push_back(make_pair(nNextRow, nNextCol));
			}

		}
	}
}

void Make_Label()
{

	int LabelNum = 1;
	int nInputVecSize = InputVec.size();
	for (int i = 0; i < nInputVecSize; i++)
	{
		int Row = InputVec[i].first;
		int Col = InputVec[i].second;

		if (bVisited[Row][Col] == 0)
		{
			BFS(Row, Col, LabelNum++);
			
		}
	}
	Area_Num = LabelNum;
}

bool CheckConnect()
{
	memset(Connect, 0, sizeof(Connect));
	memset(ConnectIsland, 0, sizeof(ConnectIsland));
	int Row, Col;
	int nSize = BridgeList.size();
	for (int i = 0; i < nSize; i++)
	{
		if (Select[i] == true)
		{
			Row = BridgeList[i].first.first;
			Col = BridgeList[i].first.second;
			Connect[Row][Col] = true;
			Connect[Col][Row] = true;
		}
	}

	queue <int> CheckQue;
	CheckQue.push(1);
	ConnectIsland[1] = true;
	int IslandCnt = 1;
	bool IsConnect = false;
	
	while (!CheckQue.empty())
	{
		int Cur = CheckQue.front();
		CheckQue.pop();
		if (IslandCnt == Area_Num - 1)
		{
			IsConnect = true;
			break;
		}

		for (int i = 1; i < Area_Num; i++)
		{
			if (Cur == i) continue;
			if (Connect[Cur][i] == true && ConnectIsland[i] == false)
			{
				ConnectIsland[i] = true;
				CheckQue.push(i);
				IslandCnt++;
			}
		}
	}

	return IsConnect;
}

void DistDFS(int nIndex, int nCount, int sum)
{
	if (nCount >= 1)
	{
		if (CheckConnect() == true)
		{
			if (nAnswer > sum) nAnswer = sum;
		}
	}
	
	for (int i = nIndex; i < BridgeList.size(); i++)
	{
		if (Select[i] == true) continue;
		Select[i] = true;
		DistDFS(i, nCount + 1, sum + BridgeList[i].second);
		Select[i] = false;
	}

}


void Solve()
{
	Make_Label(); // BFS ���� ���ںο�
	FindDistance(); //�� ���� �ִܰŸ� ���ϱ�
	DistDFS(0, 0, 0); //���� �����ϱ�

	if (nAnswer == INF) cout << "-1" << endl;
	else cout << nAnswer << endl;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> M;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Dist[i][j] = INF;
		}
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j]==1) InputVec.push_back(make_pair(i, j));
		}
	}

	Solve();

	return 0;
}