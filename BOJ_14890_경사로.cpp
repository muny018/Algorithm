//삼성 SW 역량테스트 기출
//BOJ 14890 경사로

//Review
// Index 위치에 따른 DFS 끝 지점을 잘 마무리할 것

//문제
// https://www.acmicpc.net/problem/14890

//해설
// 

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

int N, L;
int nMap[101][101] = { 0 };
bool bVisited[101] = { false };
int nProcessMap[101] = { 0 };
int nAnswer = 0; 

void DepthFirstSearch(int nIndex)
{
	if (nIndex >= N)
	{
		//조건 추가해야함
		nAnswer++;
		return;
	}

	int nStatus = nProcessMap[nIndex] - nProcessMap[nIndex - 1];
	bool bChk = true;

	//같은 높이
	if (nStatus == 0)
	{
		DepthFirstSearch(nIndex + 1);
	}
	//내려가는 경우
	else if (nStatus == -1 && nIndex + L-1 < N)
	{
		
		for (int i = nIndex; i < nIndex + L-1; i++)
		{
			if (nProcessMap[i] != nProcessMap[i + 1] || bVisited[i] == true)
			{
				bChk = false;
				break;
			}
		}

		if (bChk == true && bVisited[nIndex + L-1] == false)
		{
			for (int i = nIndex ; i < nIndex + L; i++)
			{
				bVisited[i] = true;
			}

			DepthFirstSearch(nIndex + L);
		}

	}
	//올라가는 경우
	else if (nStatus == 1 && nIndex - L >= 0)
	{
		for (int i = nIndex - L; i < nIndex-1; i++)
		{
			if (nProcessMap[i] != nProcessMap[i + 1] || bVisited[i] == true)
			{
				bChk = false;
				break;
			}
		}

		if (bChk == true && bVisited[nIndex - 1] == false)
		{
			for (int i = nIndex - L; i < nIndex; i++)
			{
				bVisited[i] = true;
			}

			DepthFirstSearch(nIndex + 1);
		}

	}
	else
	{
		return;
	}


}

void Solve()
{
	for (int i = 0; i < N; i++) // 세로행
	{
		memset(nProcessMap, 0, sizeof(nProcessMap));
		memset(bVisited, 0, sizeof(bVisited));

		for (int j = 0; j < N; j++)
		{
			nProcessMap[j] = nMap[j][i];
		}

		DepthFirstSearch(1);

	}

	for (int i = 0; i < N; i++) // 가로행
	{
		memset(nProcessMap, 0, sizeof(nProcessMap));
		memset(bVisited, 0, sizeof(bVisited));

		for (int j = 0; j < N; j++)
		{
			nProcessMap[j] = nMap[i][j];
		}

		DepthFirstSearch(1);

	}

}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
		}
	}

	Solve();

	cout << nAnswer << endl;
	return 0;
}