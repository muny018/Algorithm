//삼성 역량테스트 기출 
//2019년 상반기 DS 오전

//BOJ 17143 낚시왕

//헤매던 점
// 벡터 구조체 정렬 새로 알게됨

//문제
//https://www.acmicpc.net/problem/17143

//해설
//
//벡터 구조체 정렬
//https://twinparadox.tistory.com/182

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std; 

struct FishInfo{
	int Num;
	int nRow;
	int nCol;
	int nSpeed; 
	int nDir;
	bool IsLive;
};

int nMap[101][101] = { 0 };
bool bVisited[101][101] = { 0 };
int nAnswer = 0, R, C, M, r, c, s, d, z;
int dx[] = { 0, 0, 0, 1, -1 }; //더미 위 아래 오른쪽 왼쪽
int dy[] = { 0, -1, 1, 0, 0 };
vector <FishInfo> Vec;
vector <FishInfo> NewVec;
vector <int> KillVec;

void BreadthFirstSearch()
{
	int nVecSize = 0;
	for (int JaksalCol = 1; JaksalCol <= C; JaksalCol++)
	{
		memset(bVisited, 0, sizeof(bVisited));
		nVecSize = Vec.size();
		bool IsFinish = false;
		//물고기 잡자
		for (int Row = 1; Row <= R; Row++)
		{
			if (nMap[Row][JaksalCol])
			{
				for (int i = 0; i < nVecSize; i++)
				{
					if (Vec[i].nRow == Row && Vec[i].nCol == JaksalCol)
					{
						KillVec.push_back(nMap[Vec[i].nRow][Vec[i].nCol]);
						nMap[Vec[i].nRow][Vec[i].nCol] = 0;
						Vec[i].IsLive = false;
						IsFinish = true;
						break;
					}
				}
			}

			if (IsFinish) break;
		}

		//물고기 움직이자
		memset(nMap, 0, sizeof(nMap));
		nVecSize = Vec.size();
		int Num;
		int nRow, nNextRow, nNextCol;
		int nCol;
		int nSpeed;
		int nDir;
		FishInfo InputFish;

		for (int i = nVecSize - 1; i >= 0; i--)
		{
			if (Vec[i].IsLive == false) continue;
			Num = Vec[i].Num;
			nRow = Vec[i].nRow;
			nCol = Vec[i].nCol;
			nSpeed = Vec[i].nSpeed;
			nDir = Vec[i].nDir;

			for (int Move = 0; Move < nSpeed; Move++)
			{
				nNextRow = nRow + dy[nDir];
				if (nNextRow <= 0)
				{
					nNextRow = 2;
					nDir = 2;
				}
				else if (nNextRow > R)
				{
					nNextRow = R-1;
					nDir = 1;
				}
				nRow = nNextRow;

				nNextCol = nCol + dx[nDir];
				if (nNextCol <= 0)
				{
					nNextCol = 2;
					nDir = 3;
				}
				else if (nNextCol > C)
				{
					nNextCol = C-1;
					nDir = 4;
				}
				nCol = nNextCol;
			}

			if (nSpeed == 0)
			{
				nNextRow = nRow;
				nNextCol = nCol;
			}

			if (bVisited[nNextRow][nNextCol]) continue;

			nMap[nNextRow][nNextCol] = Num;
			bVisited[nNextRow][nNextCol] = true;

			InputFish.Num = Num;
			InputFish.nRow = nNextRow;
			InputFish.nCol = nNextCol;
			InputFish.nSpeed = nSpeed;
			InputFish.nDir = nDir;
			InputFish.IsLive = true;

			NewVec.push_back(InputFish);
		}


		//Vec 새로 채워넣기
		Vec.clear();
		nVecSize = NewVec.size();

		for (int i = nVecSize-1; i >= 0; i--)
		{
			Vec.push_back(NewVec[i]);
		}

		NewVec.clear();
	}// 작살 Col위치

}

bool cmp(const FishInfo& x, const FishInfo& y)
{
	return x.Num < y.Num;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> R >> C >> M;
	FishInfo InputFish; 

	for (int i = 0; i < M; i++)
	{
		cin >> r >> c >> s >> d >> z;
		InputFish.Num = z;
		InputFish.nRow = r;
		InputFish.nCol = c;
		InputFish.nSpeed = s;
		InputFish.nDir = d;
		InputFish.IsLive = true;
		Vec.push_back(InputFish);
		nMap[r][c] = z;
	}

	sort(Vec.begin(), Vec.end(), cmp);

	BreadthFirstSearch();

	int nVecSize = KillVec.size();

	nAnswer = 0;
	for (int i = 0; i < nVecSize; i++)
	{
		nAnswer += KillVec[i];
	}

	cout << nAnswer << endl;

	return 0;
}