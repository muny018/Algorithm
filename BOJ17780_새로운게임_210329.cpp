//BOJ17780 새로운 게임

//문제
//https://www.acmicpc.net/problem/17780

//해설
//

/*
VecHorse 크기만큼 순서대로 움직임 (한턴한턴 움직이고 나서, 4개쌓여있는지 체크)
젤 바닥이냐?
	바닥이라면 움직인다.

	파랑색-> 이동방향 반대로 하고 전진,
		근데 전진한게 테두리 밖이거나, 또 파랑색이면 제자리 있기

	흰색 -> 통쨰로 가져가서 차례대로 쌓는다.
	VecHorse 정보 업데이트 해준다.
	기존에 있었던거 Vec.clear(); 해줌

	빨간색->통쨰로 가져가서 쌓을려는걸 반대로 쌓는다.


*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std; 

struct HorseInfo
{
	int nNum;
	int nRow;
	int nCol;
	int nDir;
	bool IsBottom;
};

vector <HorseInfo> nVecMap[16][16];
vector <HorseInfo> VecHorse;

int N, K;
int nMap[13][13] = { 0 };
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,-1,1 };
int nAnswer = -1;

void VecHorseUpdate(int nRow, int nCol)
{
	int nVecSize = nVecMap[nRow][nCol].size();
	int nNum;

	for (int i = 0; i < nVecSize; i++)
	{
		nNum = nVecMap[nRow][nCol].at(i).nNum;
		
		VecHorse[nNum].nRow = nVecMap[nRow][nCol].at(i).nRow;
		VecHorse[nNum].nCol = nVecMap[nRow][nCol].at(i).nCol;
		VecHorse[nNum].nDir = nVecMap[nRow][nCol].at(i).nDir;
		VecHorse[nNum].IsBottom = nVecMap[nRow][nCol].at(i).IsBottom;
	}

}

void Move(int nCurRow, int nCurCol, int nDir)
{
	int nCurVecSize = 0;
	int nNextRow = nCurRow + dy[nDir];
	int nNextCol = nCurCol + dx[nDir];
	int nNextDir;
	HorseInfo MoveInfo;


	if (nMap[nNextRow][nNextCol] == 2 || nNextRow <0 || nNextRow >=N || nNextCol <0 || nNextCol >=N) // 파랑색
	{
		//방향전환
		if (nDir == 0) nNextDir = 1;
		else if (nDir == 1)nNextDir = 0;
		else if (nDir == 2)nNextDir = 3;
		else if (nDir == 3)nNextDir = 2;

		nNextRow = nCurRow + dy[nNextDir];
		nNextCol = nCurCol + dx[nNextDir];

		if (nMap[nNextRow][nNextCol] == 2 || nNextRow < 0 || nNextRow >= N || nNextCol < 0 || nNextCol >= N)
		{
			nVecMap[nCurRow][nCurCol].at(0).nDir = nNextDir;
			VecHorse[nVecMap[nCurRow][nCurCol].at(0).nNum].nDir = nNextDir;
		}
		else
		{
			if (nMap[nNextRow][nNextCol] == 0) //흰색
			{
				nCurVecSize = nVecMap[nCurRow][nCurCol].size();
				for (int i = 0; i < nCurVecSize; i++)
				{
					MoveInfo.nNum = nVecMap[nCurRow][nCurCol].at(i).nNum;
					MoveInfo.nRow = nNextRow;
					MoveInfo.nCol = nNextCol;
					if (i == 0) MoveInfo.nDir = nNextDir;
					else MoveInfo.nDir = nVecMap[nCurRow][nCurCol].at(i).nDir;
					
					if (nVecMap[nNextRow][nNextCol].size() == 0) MoveInfo.IsBottom = true;
					else MoveInfo.IsBottom = false;

					nVecMap[nNextRow][nNextCol].push_back(MoveInfo);
				}
				nVecMap[nCurRow][nCurCol].clear();

				//VecHorse 안에 내용 업데이트
				VecHorseUpdate(nNextRow, nNextCol);

			}
			else if (nMap[nNextRow][nNextCol] == 1) //빨간색
			{
				nCurVecSize = nVecMap[nCurRow][nCurCol].size();
				for (int i = nCurVecSize - 1; i >= 0; i--)
				{
					MoveInfo.nNum = nVecMap[nCurRow][nCurCol].at(i).nNum;
					MoveInfo.nRow = nNextRow;
					MoveInfo.nCol = nNextCol;

					if (i == 0) MoveInfo.nDir = nNextDir;
					else MoveInfo.nDir = nVecMap[nCurRow][nCurCol].at(i).nDir;

					if (nVecMap[nNextRow][nNextCol].size() == 0) MoveInfo.IsBottom = true;
					else MoveInfo.IsBottom = false;

					nVecMap[nNextRow][nNextCol].push_back(MoveInfo);
				}
				nVecMap[nCurRow][nCurCol].clear();

				//VecHorse 안에 내용 업데이트
				VecHorseUpdate(nNextRow, nNextCol);
			}
		}
	}
	else if (nMap[nNextRow][nNextCol] == 0) //흰색
	{
		nCurVecSize = nVecMap[nCurRow][nCurCol].size();
		for (int i = 0; i < nCurVecSize; i++)
		{
			MoveInfo.nNum = nVecMap[nCurRow][nCurCol].at(i).nNum;
			MoveInfo.nRow = nNextRow;
			MoveInfo.nCol = nNextCol;
			MoveInfo.nDir = nVecMap[nCurRow][nCurCol].at(i).nDir;
			if (nVecMap[nNextRow][nNextCol].size() == 0) MoveInfo.IsBottom = true;
			else MoveInfo.IsBottom = false;

			nVecMap[nNextRow][nNextCol].push_back(MoveInfo);
		}
		nVecMap[nCurRow][nCurCol].clear();

		//VecHorse 안에 내용 업데이트
		VecHorseUpdate(nNextRow, nNextCol);

	}
	else if (nMap[nNextRow][nNextCol] == 1) //빨간색
	{
		nCurVecSize = nVecMap[nCurRow][nCurCol].size();
		for (int i = nCurVecSize - 1; i >= 0; i--)
		{
			MoveInfo.nNum = nVecMap[nCurRow][nCurCol].at(i).nNum;
			MoveInfo.nRow = nNextRow;
			MoveInfo.nCol = nNextCol;
			MoveInfo.nDir = nVecMap[nCurRow][nCurCol].at(i).nDir;
			if (nVecMap[nNextRow][nNextCol].size() == 0) MoveInfo.IsBottom = true;
			else MoveInfo.IsBottom = false;

			nVecMap[nNextRow][nNextCol].push_back(MoveInfo);
		}
		nVecMap[nCurRow][nCurCol].clear();

		//VecHorse 안에 내용 업데이트
		VecHorseUpdate(nNextRow, nNextCol);
	}

}

bool Check()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (nVecMap[i][j].size() >= 4) return true;
		}
	}

	return false;
}

void Solve()
{
	int nVecSize = VecHorse.size();
	bool flag = true;
	int nNum, nRow, nCol, nDir;
	int nTurn = 0;

	while (flag)
	{
		nTurn++;
		if (nTurn > 1000)
		{
			nAnswer = -1;
			return;
		}

		for (int i = 0; i < nVecSize; i++)
		{
			if (VecHorse[i].IsBottom == false) continue;

			nRow = VecHorse[i].nRow;
			nCol = VecHorse[i].nCol;
			nDir = VecHorse[i].nDir;

			Move(nRow, nCol, nDir);

			if (Check() == true)
			{
				nAnswer = nTurn;
				return;
			}
		}

	}

}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> nMap[i][j];
		}
	}

	HorseInfo Input;
	for (int i = 0; i < K; i++)
	{
		cin >> Input.nRow >> Input.nCol >> Input.nDir;
		Input.nRow--;
		Input.nCol--;
		Input.nDir--;
		Input.nNum = i;
		Input.IsBottom = true;
		VecHorse.push_back(Input);
		nVecMap[Input.nRow][Input.nCol].push_back(Input);
	}

	Solve();

	cout << nAnswer << "\n";


	return 0;
}