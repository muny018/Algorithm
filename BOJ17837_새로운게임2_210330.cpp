//BOJ17837 ���ο� ����2

//����
//https://www.acmicpc.net/problem/17837

//�ؼ�
// 

/*
HorseInfo Struct �����
	�Է� vector�� �ְ�
	while �ȿ� vector Size��ŭ ������� �����µ�

- ������� �̵�
	����ĭ�� �Ķ����̸� �̵�����ݴ�, ��ĭ ����
		�ٵ��� ��輱 or �Ķ����̸� ���⸸ �ݴ�.
	����ĭ�� ����̸� ����ĭ ���� ������� �װ�
		HorseInfo ���� ����, ���� �־����� ����
	����ĭ�� �������̸� �ݴ�� �װ�
		HorseInfo ���� ����, ���� �־����� ����
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

struct HorseInfo
{
	int nNum;
	int nRow;
	int nCol;
	int nDir;
};

vector <HorseInfo> nVecMap[13][13];
vector <HorseInfo> HorseVec;

int N, K;
int nMap[13][13] = { 0 };
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,-1,1 };
int nAnswer = -1; 

bool CheckGameEnd()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nVecMap[i][j].size() >= 4) return true;
		}
	}

	return false;
}

void Solve()
{
	int nVecSize = HorseVec.size();
	int nCurVecSize;
	int nTime = 0;
	int nRow, nCol, nDir, nNum;
	int nNextRow, nNextCol, nNextDir, FindIndex, nCount;
	HorseInfo MoveInfo;

	while (true)
	{
		nTime++;
		if (nTime > 1000)
		{
			nAnswer = -1;
			return;
		}

		for (int nIndex = 0; nIndex < nVecSize; nIndex++)
		{
			nNum = HorseVec[nIndex].nNum;
			nRow = HorseVec[nIndex].nRow;
			nCol = HorseVec[nIndex].nCol;
			nDir = HorseVec[nIndex].nDir;

			nNextRow = nRow + dy[nDir];
			nNextCol = nCol + dx[nDir];
			
			//�Ķ����̰ų� ������� ���
			if (nMap[nNextRow][nNextCol] == 2 || nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N)
			{
				if (nDir == 0) nNextDir = 1;
				else if( nDir ==1)nNextDir = 0;
				else if (nDir == 2)nNextDir = 3;
				else if (nDir == 3)nNextDir = 2;

				nNextRow = nRow + dy[nNextDir];
				nNextCol = nCol + dx[nNextDir];
				nDir = nNextDir;

				//Index Ž��
				nCurVecSize = nVecMap[nRow][nCol].size();
				for (int i = 0; i < nCurVecSize; i++)
				{
					if (nVecMap[nRow][nCol].at(i).nNum == nNum)
					{
						FindIndex = i;
						break;
					}
				}

				//���� �ٲ㵵 ����ĭ�� �Ķ����̰ų� ������� ���
				if (nMap[nNextRow][nNextCol] == 2 || nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N)
				{
					HorseVec[nIndex].nDir = nNextDir;
					nVecMap[nRow][nCol].at(FindIndex).nDir = nNextDir;
					continue;
				}

				HorseVec[nIndex].nDir = nNextDir;
				nVecMap[nRow][nCol].at(FindIndex).nDir = nNextDir;
			}

			//����ĭ�� ���
			if (nMap[nNextRow][nNextCol] == 0)
			{
				nCount = 0;

				//Index Ž��
				nCurVecSize = nVecMap[nRow][nCol].size();
				for (int i = 0; i < nCurVecSize; i++)
				{
					if (nVecMap[nRow][nCol].at(i).nNum == nNum)
					{
						FindIndex = i;
						break;
					}
				}

				//�ű��, HorseVec ���� ����
				for (int i = FindIndex; i < nCurVecSize; i++)
				{
					MoveInfo.nNum = nVecMap[nRow][nCol].at(i).nNum;
					MoveInfo.nRow = nNextRow;
					MoveInfo.nCol = nNextCol;
					MoveInfo.nDir = nVecMap[nRow][nCol].at(i).nDir;

					nVecMap[nNextRow][nNextCol].push_back(MoveInfo);
					nCount++;

					HorseVec[MoveInfo.nNum].nRow = nNextRow;
					HorseVec[MoveInfo.nNum].nCol = nNextCol;
					HorseVec[MoveInfo.nNum].nDir = nVecMap[nRow][nCol].at(i).nDir;
				}

				//����
				for (int i = 0; i < nCount; i++)
				{
					nVecMap[nRow][nCol].pop_back();
				}

				if (CheckGameEnd() == true)
				{
					nAnswer = nTime;
					return;
				}
			}
			else if (nMap[nNextRow][nNextCol] == 1) //����ĭ�� ������
			{
				nCount = 0;
				//Index Ž��
				nCurVecSize = nVecMap[nRow][nCol].size();
				for (int i = 0; i < nCurVecSize; i++)
				{
					if (nVecMap[nRow][nCol].at(i).nNum == nNum)
					{
						FindIndex = i;
						break;
					}
				}

				//�ű��, HorseVec ���� ����
				for (int i = nCurVecSize-1; i >= FindIndex; i--)
				{
					MoveInfo.nNum = nVecMap[nRow][nCol].at(i).nNum;
					MoveInfo.nRow = nNextRow;
					MoveInfo.nCol = nNextCol;
					MoveInfo.nDir = nVecMap[nRow][nCol].at(i).nDir;

					nVecMap[nNextRow][nNextCol].push_back(MoveInfo);
					nCount++;

					HorseVec[MoveInfo.nNum].nRow = nNextRow;
					HorseVec[MoveInfo.nNum].nCol = nNextCol;
					HorseVec[MoveInfo.nNum].nDir = nVecMap[nRow][nCol].at(i).nDir;
				}

				//����
				for (int i = 0; i < nCount; i++)
				{
					nVecMap[nRow][nCol].pop_back();
				}

				if (CheckGameEnd() == true)
				{
					nAnswer = nTime;
					return;
				}
			}
		}

	}
	

}

int main()
{
	HorseInfo Input;
	freopen("input.txt", "r", stdin);
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
		}
	}
	
	for (int i = 0; i < K; i++)
	{
		cin >> Input.nRow >> Input.nCol >> Input.nDir;
		Input.nRow--, Input.nCol--, Input.nDir--;
		Input.nNum = i;
		HorseVec.push_back(Input);
		nVecMap[Input.nRow][Input.nCol].push_back(Input);
	}
	 
	Solve();

	cout << nAnswer << "\n";

	return 0;
}