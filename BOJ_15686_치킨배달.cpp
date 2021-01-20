//�Ｚ �����׽�Ʈ ����
//BOJ 15686 ġŲ ���

//��̴� ��
// ����?

//����
//https://www.acmicpc.net/problem/15686

//�ؼ�
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int nMap[50][50] = { 0 };
bool bVisited[14] = { 0 };
vector <pair < int, int > > vHome;
vector <pair < int, int > > vChicken;
int nAnswer = 99999999, nChickenNum = 0, nHomeNum = 0;

void Calc()
{
	vector <pair <int, int> > SelectedChick;
	SelectedChick.clear();
	int nChickenRow = 0, nChickenCol = 0;
	int nHomeRow = 0, nHomeCol = 0;
	int nDist = 0, nResult = 0, Temp = 0;

	for (int i = 0; i < nChickenNum; i++)
	{
		if (bVisited[i] == true)
		{
			nChickenRow = vChicken[i].first;
			nChickenCol = vChicken[i].second;

			SelectedChick.push_back(make_pair(nChickenRow, nChickenCol));
		}
	}

	//�� ���� ���ؼ� ġŲ�Ÿ� ���
	for (int i = 0; i < nHomeNum; i++)
	{
		nHomeRow = vHome[i].first;
		nHomeCol = vHome[i].second;
		Temp = 9999999;

		for (int j = 0; j < M; j++)
		{
			nChickenRow = SelectedChick[j].first;
			nChickenCol = SelectedChick[j].second;

			nDist = abs(nHomeRow - nChickenRow) + abs(nHomeCol - nChickenCol);

			if (nDist < Temp)
			{
				Temp = nDist;
			}
		}

		nResult += Temp;
	} 

	if (nResult < nAnswer)
	{
		nAnswer = nResult;
	}


}

void DepthFirstSearch(int nIndex, int nDepth)
{
	if (nDepth >= M && nIndex <= nChickenNum)
	{
		//ġŲ�Ÿ� ���
		Calc();
		return;
	}
	if (nIndex > nChickenNum)
	{
		return;
	}

	bVisited[nIndex] = true;
	DepthFirstSearch(nIndex + 1, nDepth + 1);
	bVisited[nIndex] = false;
	DepthFirstSearch(nIndex+1, nDepth);
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
			if (nMap[i][j] == 1)
			{
				vHome.push_back(make_pair(i, j));
			}
			else if (nMap[i][j] == 2)
			{
				vChicken.push_back(make_pair(i, j));
			}
		}
	}

	nHomeNum = vHome.size();
	nChickenNum = vChicken.size();
	DepthFirstSearch(0,0); 


	cout << nAnswer << endl;

	return 0;
}