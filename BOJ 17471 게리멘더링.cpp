//�Ｚ ����׽�Ʈ A�� ����
//BOJ 17471 �Ը������

//��Ŵ� ��
//1. ��ŸƮ�� ��ũó�� �ο��� �Ȱ��� �Ͽ� 2�� ������ ����� �˰� �־�����
//   �ο��� ��յ��ϰ� ������ ����Ž�� �ϴ� ���� �� �� ������ ...
// 2. ���� �������� �� ���� �̾����ִ��� üũ�ϴ� �� �򰥸�

//�ذ�å : 
// 1. for ���� ���� DFS�� �ذ�
// 2. nCheck[11] 1���� �迭�� nMap[11][11]�� �̿��Ͽ� BFS ����Ǿ� �ִ��� Ȯ����.

//����
//https://www.acmicpc.net/problem/17471

//�ؼ�
//��� BFS�� Ǯ����
//https://tdm1223.tistory.com/118

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

vector <int> FirstTeam;
vector <int> SecondTeam;
int N;
int nMap[12][12] = { 0 };
int nHuman[12] = { 0 };
int bVisited[12] = { 0 };
int nAnswer = 99999999;

bool CheckConnect(vector <int> &Vec)
{
	int nVecSize = Vec.size();
	bool bCheck[12] = { 0 };
	int nLocate = 0;
	bool bIsConnect = true;
	queue <int> Que;
	for (int i =0; i < nVecSize; i++)
	{
		bCheck[Vec[i]] = true;
	}

	//ȥ���� ��
	if (nVecSize == 1) return true;

	Que.push(Vec[0]);
	while (!Que.empty())
	{
		nLocate = Que.front();
		Que.pop();
		for (int i = 1; i <= N; i++)
		{
			if (nMap[nLocate][i] == 1 && bCheck[i] == 1) //����Ǿ� �ִ� ���
			{
				Que.push(i);
				bCheck[i] = false;
			}
		}
	}
	
	for (int i = 1; i <= N; i++)
	{
		if (bCheck[i]) bIsConnect = false;
	}

	return bIsConnect;
}

void Solve()
{
	FirstTeam.clear();
	SecondTeam.clear();
	int nFirstSize = 0, nSecondSize = 0, FirstSum = 0, SecondSum=0, Diff =0;

	//�� ����
	for (int i = 1; i <= N; i++)
	{
		if (bVisited[i])
		{
			FirstTeam.push_back(i);
		}
		else
		{
			SecondTeam.push_back(i);
		}
	}
	nFirstSize = FirstTeam.size();
	nSecondSize = SecondTeam.size();


	//�̾����ִ��� Ȯ���� �ּҰ� ���ϱ�
	if (CheckConnect(FirstTeam) && CheckConnect(SecondTeam))
	{
		//�ּҰ� ���ϴ� ����
		for (int i = 0; i < nFirstSize; i++)
		{
			FirstSum += nHuman[FirstTeam[i]];
		}

		for (int i = 0; i < nSecondSize; i++)
		{
			SecondSum += nHuman[SecondTeam[i]];
		}
		Diff = abs(FirstSum - SecondSum);

		if (nAnswer > Diff)
		{
			nAnswer = Diff;
		}
		
	}
	
	
}

void TeamSelect(int nIndex, int nCount, int nMax)
{
	if (nCount == nMax)
	{
		Solve();
		return;
	}
	
	if (nIndex >= N) return;

	for (int i = nIndex; i <= N; i++)
	{
		if (bVisited[i]) continue;

		bVisited[i] = true;
		TeamSelect(nIndex + 1, nCount + 1, nMax);
		bVisited[i] = false;
	}

}

int main()
{

	freopen("input.txt", "r", stdin);
	cin >> N; 
	int x=0,nConnectNum = 0;
	

	for (int i = 1; i <= N; i++)
	{
		cin >> nHuman[i];
	}

	for (int i = 1; i <= N; i++)
	{
		cin >> nConnectNum;
		for (int j = 1; j <= nConnectNum; j++)
		{
			cin >> x;
			nMap[i][x] = 1;
			nMap[x][i] = 1;
		}
	}

	for (int i = 1; i <= N / 2; i++)
	{
		memset(bVisited, 0, sizeof(bVisited));
		TeamSelect(1, 0, i);
	}
	
	//���
	if (nAnswer == 99999999)
	{
		cout << "-1" << endl;
	}
	else
	{
		cout << nAnswer << endl;
	}

	return 0;
}