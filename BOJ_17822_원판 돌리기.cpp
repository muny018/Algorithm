//�Ｚ���� CE/IM 2019�� �Ϲݱ� ���� ����
//BOJ 17822 ���� ������

//��Ŵ� ��
//

//�ذ�å : 
// 

//����
//https://www.acmicpc.net/problem/17822

//�ؼ�
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

struct RotateInfo
{
	int Num;
	int Dir;
	int Move;
};

int nMap[52][52] = { 0 };
int N, M, T;
bool bVisited[52][52] = { 0 };
vector <RotateInfo> Vec;
int dx[] = { 1,0,-1,0 }; //��������
int dy[] = { 0,1,0,-1 };
bool IsErase = false;
int nAnswer = 0;

void BFS(int nRow, int nCol, int nValue)
{
	int nCurRow, nCurCol, nNextRow, nNextCol;
	queue <pair<int,int>> BFSQue;
	BFSQue.push(make_pair(nRow, nCol));

	while (!BFSQue.empty())
	{
		nCurRow = BFSQue.front().first;
		nCurCol = BFSQue.front().second;
		BFSQue.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nCurRow + dy[i];
			nNextCol = nCurCol + dx[i];

			if (nNextCol > M) nNextCol = 1;
			if (nNextCol < 1) nNextCol = M; 
			if (nNextRow <1 || nNextRow > N) continue;

			if (bVisited[nNextRow][nNextCol] == 0 && nMap[nNextRow][nNextCol] == nValue)
			{
				BFSQue.push(make_pair(nNextRow, nNextCol));
				bVisited[nNextRow][nNextCol] = 1; 
				nMap[nNextRow][nNextCol] = 0;
				IsErase = true;
			}

		}

	}
	
}

void Rotate(int nRow, int Dir, int Move)
{
	int nMapCopy[52] = { 0 };
	queue <int> Que;

	for (int i = 1; i <= M; i++)
	{
		Que.push(nMap[nRow][i]);
	}

	int Front = 0;
	int nIndex = 1;

	if (Dir == 0) // �ð����
	{
		nIndex = 1 + Move;
	}
	else if (Dir == 1) //�ݽð����
	{
		nIndex = M - Move + 1;
	}

	while (!Que.empty())
	{
		Front = Que.front();
		Que.pop();
		nMapCopy[nIndex] = Front;
		nIndex++;
		if (nIndex > M) nIndex = 1;
	}

	for (int i = 1; i <= M; i++)
	{
		nMap[nRow][i] = nMapCopy[i];
	}

}

void Solve()
{
	int Multiply = 0;
	int nCurNum = 0;
	//������
	for (int Time = 0; Time < T; Time++)
	{
		int nNum = Vec[Time].Num;
		int nDir = Vec[Time].Dir;
		int nMove = Vec[Time].Move;

		if(nNum == 2 && nDir == 0 && nMove == 2)
		{
			int stop_a = 0;
		}

		Multiply = 1;
		while (true)
		{
			nCurNum = nNum * Multiply;
			if (nCurNum > N) break;

			Rotate(nCurNum, nDir, nMove);

			Multiply++;
		}

		memset(bVisited, 0, sizeof(bVisited));
		IsErase = false;
		//������ ����� BFS
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				if (bVisited[i][j] || nMap[i][j] ==0) continue;
				BFS(i, j,nMap[i][j]);
			}
		}

		
		//����� ������ ��մ��ϱ�
		int nCount = 0, nSum = 0;
		float fAverage = 0.00;
		if (IsErase == false)
		{
			for (int i = 1; i <= N; i++)
			{
				for (int j = 1; j <= M; j++)
				{
					if (nMap[i][j]==0) continue;
					nCount++;
					nSum += nMap[i][j];
				}
			}

			if (nCount == 0)
			{
				fAverage = 0;
			}
			else
			{
				fAverage = (float)nSum / (float)nCount;
			}

			for (int i = 1; i <= N; i++)
			{
				for (int j = 1; j <= M; j++)
				{
					if (fAverage == 0 || nMap[i][j] ==0) continue;
					
					if (nMap[i][j] > fAverage) nMap[i][j]--;
					else if (nMap[i][j] < fAverage) nMap[i][j]++;
				}
			}



		}


	} //Time ��


	//�����ִ� �� ���
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (nMap[i][j] == 0)continue;

			nAnswer += nMap[i][j];
		}
	}


}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> M >> T;

	RotateInfo Input;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> nMap[i][j];
		}
	}

	for (int i = 0; i < T; i++)
	{
		cin >> Input.Num >> Input.Dir >> Input.Move;
		Vec.push_back(Input);
	}

	Solve();

	cout << nAnswer << endl;

	return 0;
}
