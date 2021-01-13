//삼성 SW 역량테스트 기출
//BOJ 14889 스타트와 링크
//....2017 하반기 역삼역.... 디스플레이.....ㅠㅠ..

//Review
// 팀 가르기까지는 잘했으나, 팀 스코어 메기는 과정에서 발적화를 함 


//문제
//https://www.acmicpc.net/problem/14889

//해설
// 

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std; 

int N;
int nMap[21][21] = { 0 };
bool bVisited[21] = { 0 };
int nAnswer = 9999999;


int Ability(vector <int> VecInput)
{
	int nResult = 0;
	int nSize = VecInput.size();

	for (int i = 0; i < nSize; i++)
	{
		for (int j = 0; j < nSize; j++)
		{
			nResult += nMap[VecInput[i]][VecInput[j]];
		}
	}


	return nResult;
}

void TeamScore()
{
	vector <int> Team_A; Team_A.clear();
	vector <int> Team_B; Team_B.clear();

	for (int i = 0; i < N; i++)
	{
		if (bVisited[i])
		{
			Team_A.push_back(i);
		}
		else
		{
			Team_B.push_back(i);
		}
	}

	int Team_A_Score = Ability(Team_A);
	int Team_B_Score = Ability(Team_B);
	int Differ = abs(Team_A_Score - Team_B_Score);

	if (Differ < nAnswer)
	{
		nAnswer = Differ;
	}
	
}

void DepthFirstSearch(int nIndex, int nSelectPeople)
{
	if (nSelectPeople >= N / 2)
	{
		TeamScore();
		return;
	}

	if (nIndex > N) return;

	bVisited[nIndex] = true;
	DepthFirstSearch(nIndex + 1, nSelectPeople + 1);
	bVisited[nIndex] = false;
	DepthFirstSearch(nIndex +1, nSelectPeople);

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
		}
	}

	DepthFirstSearch(0, 0 );

	cout << nAnswer << endl;

	return 0; 
}
