//BOJ21608 상어초등학교

//문제
// https://www.acmicpc.net/problem/21608

//해설
//https://bloodstrawberry.tistory.com/265

//
//nLove 부분을 Vector로 만들어서 풀어도 맞았음.

#define _CRT_SECURE_NO_WARNINGS
#define MAX 21

#include <iostream>
#include <vector>
using namespace std;

int dy[] = { -1,0,0,1 };
int dx[] = { 0,-1,1,0 };

struct PeopleInfo
{
	int nNum;
	int nLove[MAX*MAX];
};

struct Pos
{
	int nRow;
	int nCol;
};

int nMap[MAX][MAX];
PeopleInfo People[MAX*MAX];
int N;
int nAnswer = 0;

void Simulate()
{
	vector<Pos> Priority_One;
	vector<Pos> Priority_Two;

	int max = -1;
	int nCount = 0;
	int nNextRow, nNextCol;
	Pos Pos;

	for (int nIdx = 0; nIdx < N*N; nIdx++)
	{
		Priority_One.clear();
		Priority_Two.clear();
		max = -1;
		nCount = 0;

		//첫번째_ 좋아하는 사람 수 카운트
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (nMap[i][j] != 0) continue;
				nCount = 0;
				

				for (int nDir = 0; nDir < 4; nDir++)
				{
					nNextRow = i - dy[nDir];
					nNextCol = j - dx[nDir];
					if (nMap[nNextRow][nNextCol] <= 0) continue;


					if (People[nIdx].nLove[nMap[nNextRow][nNextCol]] == 1)
					{
						nCount++;
					}
				}

				Pos.nRow = i;
				Pos.nCol = j;
				if (max <= nCount)
				{
					if (max < nCount) //새로 갱신
					{
						Priority_One.clear();
						Priority_One.push_back(Pos);
						max = nCount;
					}
					else
					{
						Priority_One.push_back(Pos);
					}
				}
			}
		}

		int nOneSize = Priority_One.size();

		if (nOneSize == 1)
		{
			nMap[Priority_One[0].nRow][Priority_One[0].nCol] = People[nIdx].nNum;
		}
		else
		{
			max = -1;
			//두번째 주변에 빈곳이 있나?
			for (int i = 0; i < nOneSize; i++)
			{
				int x = Priority_One[i].nCol;
				int y = Priority_One[i].nRow;
				nCount = 0;

				for (int nDir = 0; nDir < 4; nDir++)
				{
					nNextRow = y - dy[nDir];
					nNextCol = x - dx[nDir];
					if (nMap[nNextRow][nNextCol] != 0) continue;

					nCount++;
				}

				Pos.nRow = y;
				Pos.nCol = x;
				if (max <= nCount)
				{
					if (max < nCount) //새로 갱신
					{
						Priority_Two.clear();
						Priority_Two.push_back(Pos);
						max = nCount;
					}
					else
					{
						Priority_Two.push_back(Pos);
					}
				}

			}

			nMap[Priority_Two[0].nRow][Priority_Two[0].nCol] = People[nIdx].nNum;

			int Stop_a = 0;
		}
	}

}

void Satisfy()
{
	int nCount = 0;
	int nIdx = 0;
	int nNextRow, nNextCol;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int nNum = nMap[i][j];
			nCount = 0;

			//인덱스 찾기

			for (int nPeople = 0; nPeople < N*N; nPeople++)
			{
				if (People[nPeople].nNum == nNum)
				{
					nIdx = nPeople;
					break;
				}
			}

			for (int nDir = 0; nDir < 4; nDir++)
			{
				nNextRow = i + dy[nDir];
				nNextCol = j + dx[nDir];
				if (nMap[nNextRow][nNextCol] == -1) continue;
				
				if (People[nIdx].nLove[nMap[nNextRow][nNextCol]] == 1)
				{
					nCount++;
				}

			}

			if (nCount == 1) nAnswer = nAnswer + 1;
			else if (nCount==2) nAnswer = nAnswer + 10;
			else if (nCount == 3) nAnswer = nAnswer + 100;
			else if (nCount == 4) nAnswer = nAnswer + 1000;


		}
	}



}


void Solve()
{
	Simulate();
	Satisfy();
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N;

	int nNum, One, Two, Three, Four;
	for (int i = 0; i < N*N; i++)
	{
		cin >> nNum >> One >> Two >> Three >> Four;
		People[i].nNum = nNum;
		People[i].nLove[One] = 1; 
		People[i].nLove[Two] = 1;
		People[i].nLove[Three] = 1;
		People[i].nLove[Four] = 1;

	}

	//경계선 처리
	for (int i = 0; i <= N + 1; i++)
	{
		for (int j = 0; j <= N + 1; j++)
		{
			nMap[i][j] = -1;
		}
	}

	//초기화
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			nMap[i][j] = 0;
		}
	}

	Solve();

	cout << nAnswer << endl;

	return 0;
}