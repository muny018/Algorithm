//BOJ20057 ������ ���� ����̵�

//����
//https://www.acmicpc.net/problem/20057

//�ؼ�
// 

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

int nMap[510][510] = { 0 };
int N;
int dx[] = {-1,0,1,0}; //��������
int dy[] = {0,1,0,-1};
int nPaddingSize = 2;
float fTable0[5][5] = { 0.00f };
float fTable1[5][5] = { 0.00f };
float fTable2[5][5] = { 0.00f };
float fTable3[5][5] = { 0.00f };

void SandCheck()
{
	int nTotalSum = 0;
	int nNSum = 0;
	int nResult = 0;


	for (int nRow = 0; nRow < N + nPaddingSize * 2; nRow++)
	{
		for (int nCol = 0; nCol < N + nPaddingSize * 2; nCol++)
		{
			nTotalSum += nMap[nRow][nCol];
		}
	}

	for (int nRow = nPaddingSize; nRow < N + nPaddingSize; nRow++)
	{
		for (int nCol = nPaddingSize; nCol < N + nPaddingSize; nCol++)
		{
			nNSum += nMap[nRow][nCol];
		}
	}

	nResult = nTotalSum - nNSum;

	cout << nResult << '\n';


}

void MoveSand(int nCurRow, int nCurCol, int nDir)
{
	int nRowCount = 0;
	int nColCount = 0;
	int nSand = nMap[nCurRow][nCurCol];
	nMap[nCurRow][nCurCol] = 0;
	int nSpreadSum = 0;

	for (int nRow = nCurRow - nPaddingSize; nRow <= nCurRow + nPaddingSize; nRow++)
	{
		for (int nCol = nCurCol - nPaddingSize; nCol <= nCurCol + nPaddingSize; nCol++)
		{
			if (nDir == 0) //���ʹ����̵�
			{
				nMap[nRow][nCol] += (int)(nSand*fTable0[nRowCount][nColCount]);
				nSpreadSum += (int)(nSand*fTable0[nRowCount][nColCount]);
			}
			else if (nDir == 1) //���ʹ����̵�
			{
				nMap[nRow][nCol] += (int)(nSand * fTable1[nRowCount][nColCount]);
				nSpreadSum += (int)(nSand*fTable1[nRowCount][nColCount]);
			}
			else if (nDir == 2) //���ʹ����̵�
			{
				nMap[nRow][nCol] += (int)(nSand * fTable2[nRowCount][nColCount]);
				nSpreadSum += (int)(nSand*fTable2[nRowCount][nColCount]);
			}
			else if (nDir == 3) //���ʹ����̵�
			{
				nMap[nRow][nCol] += (int)(nSand * fTable3[nRowCount][nColCount]);
				nSpreadSum += (int)(nSand*fTable3[nRowCount][nColCount]);
			}

			nColCount++;
		}
		nColCount = 0;
		nRowCount++;
	} 

	//a ���

	if (nDir == 0) //���ʹ����̵�
	{
		nMap[nCurRow][nCurCol - 1] += nSand - nSpreadSum;
	}
	else if (nDir == 1) //���ʹ����̵�
	{
		nMap[nCurRow+1][nCurCol] += nSand - nSpreadSum;
	}
	else if (nDir == 2) //���ʹ����̵�
	{
		nMap[nCurRow][nCurCol +1] += nSand - nSpreadSum;
	}
	else if (nDir == 3) //���ʹ����̵�
	{
		nMap[nCurRow-1][nCurCol] += nSand - nSpreadSum;
	}
	
}

void DepthFirstSearch(int nCurRow, int nCurCol, int nCurDir, int nMoveLimit, int nMoveCount)
{
	if (nCurRow == 2 && nCurCol == 2)
	{
		//��輱 �ۿ� �ִ� �𷡾� ī��Ʈ
		SandCheck();
		return;
	}

	nMoveCount++;
	int nNextRow = nCurRow + dy[nCurDir];
	int nNextCol = nCurCol + dx[nCurDir];
	int nNextCur = nCurDir;

	MoveSand(nNextRow, nNextCol, nCurDir);

	//���� �� �̵�Ƚ�� ����
	if (nCurDir == 1 && (nMoveLimit == nMoveCount))
	{
		nMoveLimit++;
		nMoveCount = 0;
		nNextCur = (nCurDir + 1) % 4;
	}
	else if (nCurDir == 3 && (nMoveLimit == nMoveCount))
	{
		nMoveLimit++;
		nMoveCount = 0;
		nNextCur = (nCurDir + 1) % 4;
	}
	else if (nMoveLimit == nMoveCount)
	{
		nMoveCount = 0;
		nNextCur = (nCurDir + 1) % 4;
	}

	DepthFirstSearch(nNextRow, nNextCol, nNextCur, nMoveLimit, nMoveCount);
}

void TableReady()
{


	//���ʹ����̵�
	fTable0[0][2] = 0.02f;
	fTable0[4][2] = 0.02f;
	fTable0[1][1] = 0.1f;
	fTable0[1][2] = 0.07f;
	fTable0[1][3] = 0.01f;
	fTable0[3][1] = 0.1f;
	fTable0[3][2] = 0.07f;
	fTable0[3][3] = 0.01f;
	fTable0[2][0] = 0.05f;
	fTable0[2][1] = 0.00f;

	//���ʹ����̵�
	fTable1[2][0] = 0.02f;
	fTable1[2][4] = 0.02f;
	fTable1[1][1] = 0.01f;
	fTable1[2][1] = 0.07f;
	fTable1[3][1] = 0.1f;
	fTable1[1][3] = 0.01f;
	fTable1[2][3] = 0.07f;
	fTable1[3][3] = 0.1f;
	fTable1[3][2] = 0.00f;
	fTable1[4][2] = 0.05f;

	//���ʹ����̵�
	fTable2[0][2] = 0.02f;
	fTable2[4][2] = 0.02f;
	fTable2[1][1] = 0.01f;
	fTable2[1][2] = 0.07f;
	fTable2[1][3] = 0.1f;
	fTable2[3][1] = 0.01f;
	fTable2[3][2] = 0.07f;
	fTable2[3][3] = 0.1f;
	fTable2[2][4] = 0.05f;
	fTable2[2][3] = 0.00f;

	//���ʹ����̵�
	fTable3[2][0] = 0.02f;
	fTable3[2][4] = 0.02f;
	fTable3[1][1] = 0.1f;
	fTable3[2][1] = 0.07f;
	fTable3[3][1] = 0.01f;
	fTable3[1][3] = 0.1f;
	fTable3[2][3] = 0.07f;
	fTable3[3][3] = 0.01f;
	fTable3[0][2] = 0.05f;
	fTable3[1][2] = 0.00f;

}

void solve()
{
	int nStartRow = (N / 2) + nPaddingSize;
	int nStartCol = (N / 2) + nPaddingSize;
	TableReady();
	DepthFirstSearch(nStartRow, nStartRow, 0, 1,0);

}

int main()
{
	freopen("input.txt", "r", stdin);
	
	cin >> N; 
	for (int i = nPaddingSize; i < N + nPaddingSize; i++)
	{
		for (int j = nPaddingSize; j < N + nPaddingSize; j++)
		{
			cin >> nMap[i][j];
		}
	}

	solve();

	return 0;
}