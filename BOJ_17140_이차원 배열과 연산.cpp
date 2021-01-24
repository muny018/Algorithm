//�Ｚ �����׽�Ʈ ����
//BOJ 17140 ������ �迭�� ����

//��Ŵ� ��
// ���� ���� �˾Ҵ�... ������ ������
// A[r][c]�� ����ִ� ���� k�� �Ǳ� ���� ������ �ּ� �ð��� ����Ѵ�. �� ���� 100�� �Ѿ�� ��쿡�� -1�� ����Ѵ�.
// �ð��� ������ �ٽ� Ǯ�����...
// �������� �켱���� ť�� ���������� ����.


//�ذ�å : 

//����
//https://www.acmicpc.net/problem/17140

//�ؼ�
//https://regularmember.tistory.com/97

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector <pair<int, int>> Vec;
int r, c, k;
int nMap[101][101] = { 0 };
int Cnt[101] = { 0 };
int nRowSize, nColSize;

void C_Calc()
{
	
	int nSize = 0, nCount = 0;
	int nTempSize = 0;

	for (int j = 0; j < nColSize; j++)
	{
		Vec.clear();
		nSize = 0;
		memset(Cnt, 0, sizeof(Cnt));

		for (int i = 0; i < nRowSize; i++)
		{
			Cnt[nMap[i][j]]++;
			nMap[i][j] = 0;
		}
		//�ֱ�
		for (int k = 1; k <= 100; k++)
		{
			if (Cnt[k] == 0) continue;
			Vec.push_back(make_pair(Cnt[k], k));
		}
		sort(Vec.begin(), Vec.end());

		nSize = Vec.size() * 2;
		if (nSize >= nTempSize) nTempSize = nSize;
		nCount = 0;
		for (int k = 0; k < nSize; k += 2)
		{
			nMap[k][j] = Vec[nCount].second;
			nMap[k+1][j] = Vec[nCount].first;
			nCount++;
		}
	}
	nRowSize = nTempSize;


}

void R_Calc()
{
	

	int nSize = 0, nCount = 0;
	int nTempSize = 0;

	for (int i = 0; i < nRowSize; i++)
	{
		Vec.clear();
		nSize = 0;
		memset(Cnt, 0, sizeof(Cnt));
		for (int j = 0; j < nColSize; j++)
		{
			Cnt[nMap[i][j]]++;
			nMap[i][j] = 0;
		}
		//�ֱ�
		for (int k = 1; k <= 100; k++)
		{
			if (Cnt[k] == 0) continue;
			Vec.push_back(make_pair(Cnt[k], k));
		}
		sort(Vec.begin(), Vec.end());
		
		nSize = Vec.size() * 2;
		if (nSize >= nTempSize) nTempSize = nSize;

		nCount = 0;
		for (int k = 0; k < nSize; k += 2)
		{
			nMap[i][k] = Vec[nCount].second;
			nMap[i][k+1] = Vec[nCount].first;
			nCount++;
		}
		
	}
	nColSize = nTempSize;

}

void Solve()
{
	int nTime = 0;
	while (true)
	{
		if (nMap[r - 1][c - 1] == k)
		{
			cout << nTime << endl;
			break;
		}

		nTime++;

		if (nTime > 100)
		{
			cout << "-1" << endl;
			break;
		}

		if (nRowSize >= nColSize)
		{
			R_Calc();
		}
		else
		{
			C_Calc();
		}
	}


}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> r >> c >> k;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> nMap[i][j];
		}
	}

	nRowSize = 3;
	nColSize = 3;

	Solve();

	return 0;
}