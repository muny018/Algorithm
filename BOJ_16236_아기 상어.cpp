//�Ｚ �����׽�Ʈ ����
//BOJ 16236 �Ʊ� ���

//��Ŵ� ��
// ���ѷ����� ���� �ð��ʰ��� �����, �׷��� 2�ð��� ���� �� �ذ���
// �ʱ⿡ § �ڵ�� ���� ����Ⱑ ���� �𼭸��� �ְ�, ���±��� ū����Ⱑ ���� ��� 
// ���ѷ����� ��������. �����̾��ٸ� ��� ���� ���ɸ� �� �� ���� ������ 1�ַ� �����ϰ� ���� ����������
// �ذ�å : ������ �� �����ϰ� �ݷʸ� �����ð��� �����ϰ� ���踦 ���ؾ���.

//����
//https://www.acmicpc.net/problem/16236

//�ؼ�
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int nMap[21][21] = { 0 };
int nAnswer = 0;
int Shark_Row = 0, Shark_Col = 0, nShark_Size = 2;
int dx[] = { 0, -1, 1, 0 }; //�ϼ�����
int dy[] = { -1, 0, 0, 1 };
int SharkUp[9] = { 0 };

void BreadthFirstSearch(int nRow, int nCol)
{
	queue <pair <int, int> > Que;
	vector <pair <int, int> > Vec;
	bool bVisited[21][21] = { 0 };
	Que.push(make_pair(nRow, nCol));
	bool IsStop = false;
	int nResult = 0, nDistanceMin = 99999999;

	while (!Que.empty())
	{
		int nQueSize = Que.size();
		bool IsStop = false;

		for (int Quesize = 0; Quesize < nQueSize; Quesize++)
		{
			int nCurRow = Que.front().first;
			int nCurCol = Que.front().second;
			bVisited[nCurRow][nCurCol] = true;
			Que.pop();

			if (nResult > nDistanceMin) continue;

			for (int i = 0; i < 4; i++)
			{
				int nNextRow = nCurRow + dy[i];
				int nNextCol = nCurCol + dx[i];
				if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= N) continue;
				if (bVisited[nNextRow][nNextCol]) continue;
				if (nShark_Size < nMap[nNextRow][nNextCol]) continue; //�ڽź��� ū ����� ��������

				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));

				if (nMap[nNextRow][nNextCol] && nShark_Size > nMap[nNextRow][nNextCol] && nResult <= nDistanceMin) //����� ����
				{
					nDistanceMin = nResult;
					Vec.push_back(make_pair(nNextRow, nNextCol));
					int stop = 0;
				}
			}
		}
		nResult++;
	}

	if (Vec.size()) //��Ƹ��� ����Ⱑ ����
	{
		sort(Vec.begin(), Vec.end());
		nAnswer += nDistanceMin + 1;
		Shark_Row = Vec[0].first; Shark_Col = Vec[0].second;
		nMap[Shark_Row][Shark_Col] = 0;


		if (nShark_Size <= 6 && SharkUp[nShark_Size])
		{
			SharkUp[nShark_Size]--;
			if (SharkUp[nShark_Size] <= 0) nShark_Size++;
		}
		Vec.clear();
		BreadthFirstSearch(Shark_Row, Shark_Col);
		return;
	}

	return;
}

bool SearchFish()
{
	bool IsGo = false;

	//���� �� �ִ� ����� �ּҰŸ� ã��
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j] && nShark_Size > nMap[i][j])
			{
				IsGo = true;
			}
		}
	}

	return IsGo;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] == 9)
			{
				Shark_Row = i;
				Shark_Col = j;
				nMap[i][j] = 0;
			}
		}
	}

	for (int i = 1; i <= 7; i++)
	{
		SharkUp[i] = i;
	}

	//Ǯ��

	BreadthFirstSearch(Shark_Row, Shark_Col);


	//���
	cout << nAnswer << endl;

	return 0;
}




/* @@@@@@@@@@@@@@@@@@@@@@@�����ߴ� �ڵ�@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2
//�Ｚ �����׽�Ʈ ����
//BOJ 16236 �Ʊ� ���

//��Ŵ� ��
//

//����
//https://www.acmicpc.net/problem/16236

//�ؼ�
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int nMap[21][21] = { 0 };
int nAnswer = 0;
int Shark_Row = 0, Shark_Col = 0, nShark_Size = 2;
int dx[] = { 0, -1, 1, 0 }; //�ϼ�����
int dy[] = { -1, 0, 0, 1 };
int SharkUp[9] = { 0 };

void BreadthFirstSearch(int nRow, int nCol)
{
	queue <pair <int, int> > Que;
	vector <pair <int, int> > Vec;
	bool bVisited[21][21] = { 0 };
	Que.push(make_pair(nRow, nCol));
	bool IsStop = false;
	int nResult = 0, nDistanceMin = 99999999;

	while (!Que.empty())
	{
		int nQueSize = Que.size();
		bool IsStop = false;

		for (int Quesize = 0; Quesize < nQueSize; Quesize++)
		{
			int nCurRow = Que.front().first;
			int nCurCol = Que.front().second;
			bVisited[nCurRow][nCurCol] = true;
			Que.pop();

			if (nResult > nDistanceMin) continue;

			for (int i = 0; i < 4; i++)
			{
				int nNextRow = nCurRow + dy[i];
				int nNextCol = nCurCol + dx[i];
				if (nNextRow < 0 || nNextCol < 0 || nNextRow >= N || nNextCol >= N) continue;
				if (bVisited[nNextRow][nNextCol]) continue;
				if (nShark_Size < nMap[nNextRow][nNextCol]) continue; //�ڽź��� ū ����� ��������

				bVisited[nNextRow][nNextCol] = true;
				Que.push(make_pair(nNextRow, nNextCol));

				if (nMap[nNextRow][nNextCol] && nShark_Size > nMap[nNextRow][nNextCol] && nResult <= nDistanceMin) //����� ����
				{
					nDistanceMin = nResult;
					Vec.push_back(make_pair(nNextRow, nNextCol));
					int stop = 0;
				}
			}
		}
		nResult++;

		if (Vec.size()) //��Ƹ��� ����Ⱑ ����
		{
			sort(Vec.begin(), Vec.end());
			nAnswer += nDistanceMin + 1;
			Shark_Row = Vec[0].first; Shark_Col = Vec[0].second;
			nMap[Shark_Row][Shark_Col] = 0;


			if (nShark_Size <= 6 && SharkUp[nShark_Size])
			{
				SharkUp[nShark_Size]--;
				if (SharkUp[nShark_Size] <= 0) nShark_Size++;
			}
			Vec.clear();

			return;
		}
	}


	return;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@�����ߴ� �Լ� �κ�@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool SearchFish()
{
	bool IsGo = false;

	//���� �� �ִ� ����� �ּҰŸ� ã��
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j] && nShark_Size > nMap[i][j])
			{
				IsGo = true;
			}
		}
	}

	return IsGo;
}
//���� ���� ����Ⱑ �� ���� �ڳʿ� �ְ� ���±��� ū����Ⱑ ���θ����� ���ѷ��� ��
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main()
{
	//freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
			if (nMap[i][j] == 9)
			{
				Shark_Row = i;
				Shark_Col = j;
				nMap[i][j] = 0;
			}
		}
	}

	for (int i = 1; i <= 7; i++)
	{
		SharkUp[i] = i;
	}

	//Ǯ��
	while (true)
	{
		//��Ƹ��� ����� �ֳ�?
		if (!SearchFish()) break;

		BreadthFirstSearch(Shark_Row, Shark_Col);
	}

	//���
	cout << nAnswer << endl;

	return 0;
}
*/
