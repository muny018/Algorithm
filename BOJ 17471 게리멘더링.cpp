//삼성 상시테스트 A형 기출
//BOJ 17471 게리멘더링

//헤매던 점
//1. 스타트와 링크처럼 인원을 똑같이 하여 2팀 나누는 방법을 알고 있었으나
//   인원을 비균등하게 나눠서 완전탐색 하는 법을 할 줄 몰랐음 ...
// 2. 팀을 나눈다음 각 팀이 이어져있는지 체크하는 법 헷갈림

//해결책 : 
// 1. for 문을 통한 DFS로 해결
// 2. nCheck[11] 1차원 배열과 nMap[11][11]을 이용하여 BFS 연결되어 있는지 확인함.

//문제
//https://www.acmicpc.net/problem/17471

//해설
//얘는 BFS로 풀었네
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

	//혼자일 때
	if (nVecSize == 1) return true;

	Que.push(Vec[0]);
	while (!Que.empty())
	{
		nLocate = Que.front();
		Que.pop();
		for (int i = 1; i <= N; i++)
		{
			if (nMap[nLocate][i] == 1 && bCheck[i] == 1) //연결되어 있는 경우
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

	//팀 선택
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


	//이어져있는지 확인후 최소값 구하기
	if (CheckConnect(FirstTeam) && CheckConnect(SecondTeam))
	{
		//최소값 구하는 과정
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
	
	//출력
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