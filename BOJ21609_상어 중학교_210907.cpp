//BOJ21609_��� ���б�_210907

//����
//https://www.acmicpc.net/problem/21609

//�ؼ�
// 

/*
����Ž�� + BFS�� �� ū ��� ���Ϳ� �ֱ� (Row, Col)
	- BFS ���� ��, 0�̶� ���� �ڿ����� ã��
	- �ڿ��� �ִ��� üũ(�ּұ��� 2�̻�)
	- �� ū �������� üũ + ������ ��� ���� �� ������ + ���غ�� �� ū�� �� ū��

 - ��� ���� �� ���� ȹ��

- ���� �߷��ۿ� (-1�� �ȿ�����)

- 90�� �ݽð� ȸ��

- ���� �߷� �ۿ� (-1�� �ȿ�����)
*/

#define _CRT_SECURE_NO_WARNINGS

#define MAX 22

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct BlockInfo
{
	int nRefRow;
	int nRefCol;
	int nRainbowCount;
};

int nMap[MAX][MAX] = { 0 };
int nCopyMap[MAX][MAX] = { 0 };
int N, M;
vector <pair<int, int>> LongBlock;
BlockInfo LongBlockInfo;
bool SequnceDone = false;

long long nAnswer = 0;
int dx[] = {-1,0,1,0};
int dy[] = {0,-1,0,1};


void BFS(int nStartRow, int nStartCol)
{
	bool bVisited[MAX][MAX] = { false };

	int nNextRow, nNextCol, nRow, nCol;
	int nNum;
	nNum = nMap[nStartRow][nStartCol];

	queue <pair<int, int>> Que;
	vector <pair<int, int>> CandidateBlock;
	BlockInfo CandidateInfo;

	bVisited[nStartRow][nStartCol] = true;
	Que.push(make_pair(nStartRow, nStartCol));
	CandidateBlock.push_back(make_pair(nStartRow, nStartCol));


	while (!Que.empty())
	{
		nRow = Que.front().first;
		nCol = Que.front().second;
		Que.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nRow + dy[i];
			nNextCol = nCol + dx[i];
			if (nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N) continue;
			if (bVisited[nNextRow][nNextCol] == true) continue;
			if (nMap[nNextRow][nNextCol] == 0 || nMap[nNextRow][nNextCol] == nNum || nNum ==0)
			{
				//ó�� ������ 0 �� �� �ڿ��� ���� ����
				if (nMap[nNextRow][nNextCol] != 0)
				{
					nNum = nMap[nNextRow][nNextCol];
				}
				Que.push(make_pair(nNextRow, nNextCol));
				bVisited[nNextRow][nNextCol] = true;
				CandidateBlock.push_back(make_pair(nNextRow, nNextCol));
			}
		}
	}

	int nCandidateSize = CandidateBlock.size();

	//�ڰ�����_������ 2�̻�, �ڿ��� �ϳ� �̻�����
	if (nCandidateSize < 2) return;
	
	bool IsQualify = false;
	int nMinRow = MAX, nMinCol = MAX, nCount = 0;
	for (int i = 0; i < nCandidateSize; i++)
	{
		nRow = CandidateBlock[i].first;
		nCol = CandidateBlock[i].second;
		if (nMap[nRow][nCol] > 0) IsQualify = true;
		else if (nMap[nRow][nCol] == 0) nCount++;

		if (nMap[nRow][nCol] > 0)
		{
			if (nMinRow > nRow) nMinRow = nRow;
			if (nMinCol > nCol) nMinCol = nCol;
		}

	}

	if (IsQualify == false) return;

	CandidateInfo.nRainbowCount = nCount;
	CandidateInfo.nRefRow = nMinRow;
	CandidateInfo.nRefCol = nMinCol;


	int nOrgSize = LongBlock.size();

	if (nOrgSize <= nCandidateSize)
	{
		if (nOrgSize < nCandidateSize)
		{
			LongBlock.swap(CandidateBlock);
			LongBlockInfo = CandidateInfo;
		}
		else if (LongBlockInfo.nRainbowCount <= CandidateInfo.nRainbowCount)
		{
			if (LongBlockInfo.nRainbowCount < CandidateInfo.nRainbowCount)
			{
				LongBlock.swap(CandidateBlock);
				LongBlockInfo = CandidateInfo;
			}
			else if (LongBlockInfo.nRefRow <= CandidateInfo.nRefRow)
			{
				if (LongBlockInfo.nRefRow < CandidateInfo.nRefRow)
				{
					LongBlock.swap(CandidateBlock);
					LongBlockInfo = CandidateInfo;
				}
				else if (LongBlockInfo.nRefCol < CandidateInfo.nRefCol)
				{
					LongBlock.swap(CandidateBlock);
					LongBlockInfo = CandidateInfo;
				}
			}
		}
	}
}

void CheckLongBlock()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ( nMap[i][j] >= 0)
			{
				BFS(i, j);
			}
		}
	}

	//�������
	int nOrgSize = LongBlock.size();
	if (nOrgSize == 0)
	{
		SequnceDone = true;
		return;
	}

	nAnswer += nOrgSize * nOrgSize;

	int nRow, nCol;

	for (int i = 0; i < nOrgSize; i++)
	{
		nRow = LongBlock[i].first;
		nCol = LongBlock[i].second;
		nMap[nRow][nCol] = -9;
	}

}

void GravityProc(int nCol, int nStartRow)
{
	if (nStartRow < 0) return;

	vector <int> Vec;
	int nVecSize;

	for (int i = nStartRow; i >= 0; i--)
	{
		if (nMap[i][nCol] == -9) continue;

		if (nMap[i][nCol] == -1)
		{
			nCopyMap[i][nCol] = -1;
			nVecSize = Vec.size();

			int nIdx = nStartRow;
			for (int j = 0; j < nVecSize; j++)
			{
				nCopyMap[nIdx][nCol] = Vec[j];
				nIdx--;
			}
			Vec.clear();

			GravityProc(nCol, i - 1);

			return;
		}
		else
		{
			Vec.push_back(nMap[i][nCol]);
		}
	}

	int nIdx = nStartRow;
	nVecSize = Vec.size();

	for (int j = 0; j < nVecSize; j++)
	{
		nCopyMap[nIdx][nCol] = Vec[j];
		nIdx--;
	}

}

void Gravity()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j] == -1)
			{
				nCopyMap[i][j] = nMap[i][j];
			}
			else
			{
				nCopyMap[i][j] = -9;
			}
			
		}
	}


	for (int j = 0; j < N; j++)
	{
		GravityProc(j, N - 1);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			nMap[i][j] = nCopyMap[i][j];
		}
	}
}

void Rotate()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			nCopyMap[i][j] = nMap[i][j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			nMap[i][j] = nCopyMap[j][N-1-i];
		}
	}

}

void Solve()
{
	while (true)
	{
		LongBlock.clear();
		LongBlockInfo.nRainbowCount = -1;
		LongBlockInfo.nRefRow = -1;
		LongBlockInfo.nRefCol = -1;


		CheckLongBlock();
		
		//Ż�� ������ ��������.
		if (SequnceDone == true) return;
		
		Gravity();
		Rotate();
		Gravity();

	}

}

int main()
{
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	#endif

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
		}
	}

	Solve();

	cout << nAnswer << "\n";

	return 0;
}