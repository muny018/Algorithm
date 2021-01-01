//BOJ 19237 어른 상어

//문제
// https://www.acmicpc.net/problem/19237

//해설
//https://yabmoons.tistory.com/496

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dy[] = { 0, -1,1,0,0 };
int dx[] = { 0, 0,0,-1,1 };

struct SHARK
{
	int nRow;
	int nCol;
	int nDir;
	bool Live;
	vector <int> Priority[5];
};

struct MapInfo
{
	vector <int> V;
	int Smell_Num;
	int Smell_Time;
	
};

MapInfo nMap[21][21];
SHARK Shark[401];
int N, M, k;

bool Check()
{
	for (int i = 2; i <= M; i++)
	{
		if (Shark[i].Live == true) return false;
	}

	return true;
}

void MoveShark(int nTime)
{
	for (int i = 1; i <= M; i++)
	{	
		if (Shark[i].Live == false) continue;
		
		int nRow = Shark[i].nRow;
		int nCol = Shark[i].nCol;
		int nDir = Shark[i].nDir;
		bool flag = false;

		nMap[nRow][nCol].V.clear();

		for (int j = 1; j <= 4; j++)
		{
			int nPriortyDir = Shark[i].Priority[nDir].at(j - 1);
			int nNextRow = nRow + dy[nPriortyDir];
			int nNextCol = nCol + dx[nPriortyDir];

			if (nNextRow >= 0 && nNextCol >= 0 && nNextRow < N && nNextCol < N)
			{
				if (nMap[nNextRow][nNextCol].Smell_Time <= nTime)
				{
					flag = true;
					Shark[i].nRow = nNextRow;
					Shark[i].nCol = nNextCol;
					Shark[i].nDir = nPriortyDir;
					nMap[nNextRow][nNextCol].V.push_back(i);
					break;
				}
			}
		}

		if (flag == false)
		{
			for (int j = 1; j <= 4; j++)
			{
				int nPriortyDir = Shark[i].Priority[nDir].at(j - 1);
				int nNextRow = nRow + dy[nPriortyDir];
				int nNextCol = nCol + dx[nPriortyDir];

				if (nNextRow >= 0 && nNextCol >= 0 && nNextRow < N && nNextCol < N)
				{
					if (nMap[nNextRow][nNextCol].Smell_Num ==i)
					{
						Shark[i].nRow = nNextRow;
						Shark[i].nCol = nNextCol;
						Shark[i].nDir = nPriortyDir;
						nMap[nNextRow][nNextCol].V.push_back(i);
						break;
					}
				}
			}
		}


	}
}

void SmellShark(int nTime)
{
	for (int i = 1; i <= M; i++)
	{
		if (Shark[i].Live == false) continue;

		int nRow = Shark[i].nRow;
 		int nCol = Shark[i].nCol;
		nMap[nRow][nCol].Smell_Time = nTime + k;
		nMap[nRow][nCol].Smell_Num = i;
	}

}

void EatShark()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nMap[i][j].V.size() <= 1) continue;

			sort(nMap[i][j].V.begin(), nMap[i][j].V.end());

			for (int x = 1; x < nMap[i][j].V.size(); x++)
			{
				int SharkNum = nMap[i][j].V.at(x);
				Shark[SharkNum].Live = false;
			}
		}
	}

}

void Solve()
{
	for (int Time = 0; Time <= 1001; Time++)
	{
		if (Time >= 1001)
		{
			cout << "-1" << endl;
			return;
		}
		else if (Check() == true)
		{
			cout << Time << endl;
			return;
		}

		//냄새뿌린다
		SmellShark(Time);

		//움직인다
		MoveShark(Time);

		//겹치는거 먹는다.
		EatShark();
	}
	


}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> M >> k;
	int Num;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Num;
			if (Num != 0)
			{
				nMap[i][j].V.push_back(Num);
				Shark[Num].nRow = i;
				Shark[Num].nCol = j;
			}
			nMap[i][j].Smell_Num = 0;
			nMap[i][j].Smell_Time = 0;
		}
	}

	for (int i = 1; i <= M; i++)
	{
		int dir;
		cin >> dir;
		Shark[i].nDir = dir;
		Shark[i].Live = true;
	}

	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int x = 1; x <= 4; x++)
			{
				cin >> Num;
				Shark[i].Priority[j].push_back(Num);
			}

		}
	}

	Solve();


	return 0;
}