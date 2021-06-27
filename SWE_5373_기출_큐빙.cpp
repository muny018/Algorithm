// SWE 기출 큐빙

//문제
//https://www.acmicpc.net/problem/5373

//풀이
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <vector>
using namespace std; 

int T, Count;
char Input[2];

char White[3][3], TempWhite[3][3];
char Red[3][3], TempRed[3][3];
char Yellow[3][3], TempYellow[3][3];
char Green[3][3], TempGreen[3][3];
char Blue[3][3], TempBlue[3][3];
char Orange[3][3], TempOrange[3][3];


vector<pair<char, bool>> vec;

void calc()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << White[i][j];
		}
		cout << endl;
	}

}

void solve()
{
	for (int num = 0; num < Count; num++)
	{
		char Rotate = vec.at(num).first;
		bool Dir = vec.at(num).second;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{

				TempWhite[i][j] = White[i][j];
				TempRed[i][j] = Red[i][j];
				TempYellow[i][j] = Yellow[i][j];
				TempGreen[i][j] = Green[i][j];
				TempBlue[i][j] = Blue[i][j];
				TempOrange[i][j] = Orange[i][j];
			}
		}



		if (Rotate == 'U')
		{
			if (Dir == false) // Up 시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						White[i][2] = TempWhite[0][i];
						White[i][1] = TempWhite[1][i];
						White[i][0] = TempWhite[2][i];
					}
				}

				for (int i = 0; i < 3; i++)
				{
					Green[0][i] = TempRed[0][i];
					Red[0][i] = TempBlue[0][i];
					Blue[0][i] = TempOrange[0][i];
					Orange[0][i] = TempGreen[0][i];
				}

			}
			else  // Up 반시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						White[0][i] = TempWhite[i][2];
						White[1][i] = TempWhite[i][1];
						White[2][i] = TempWhite[i][0];
					}
				}

				for (int i = 0; i < 3; i++)
				{
					Red[0][i] = TempGreen[0][i];
					Green[0][i] = TempOrange[0][i];
					Orange[0][i] = TempBlue[0][i];
					Blue[0][i] = TempRed[0][i];	
				}


			}
		}
		else if (Rotate == 'D')
		{
			if (Dir == false) // Down 시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Yellow[i][2] = TempYellow[0][i];
						Yellow[i][1] = TempYellow[1][i];
						Yellow[i][0] = TempYellow[2][i];
					}
				}

				for (int i = 0; i < 3; i++)
				{
					Red[2][i] = TempGreen[2][i];
					Green[2][i] = TempOrange[2][i];
					Orange[2][i] = TempBlue[2][i];
					Blue[2][i] = TempRed[2][i];
				}
			}
			else  // Down 반시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Yellow[0][i] = TempYellow[i][2];
						Yellow[1][i] = TempYellow[i][1];
						Yellow[2][i] = TempYellow[i][0];
					}
				}

				for (int i = 0; i < 3; i++)
				{
					Green[2][i] = TempRed[2][i];
					Red[2][i] = TempBlue[2][i];
					Blue[2][i] = TempOrange[2][i];
					Orange[2][i] = TempGreen[2][i];
				}

			}
		}
		else if (Rotate == 'F')
		{
			if (Dir == false) // Front 시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Red[i][2] = TempRed[0][i];
						Red[i][1] = TempRed[1][i];
						Red[i][0] = TempRed[2][i];
					}
				}

				White[2][0] = TempGreen[2][2];
				White[2][1] = TempGreen[1][2];
				White[2][2] = TempGreen[0][2];

				Green[2][2] = TempYellow[0][2];
				Green[1][2] = TempYellow[0][1];
				Green[0][2] = TempYellow[0][0];

				Yellow[0][2] = TempBlue[0][0];
				Yellow[0][1] = TempBlue[1][0];
				Yellow[0][0] = TempBlue[2][0];
				
				Blue[0][0] = TempWhite[2][0];
				Blue[1][0] = TempWhite[2][1];
				Blue[2][0] = TempWhite[2][2];
			}
			else  // Front 반시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Red[0][i] = TempRed[i][2];
						Red[1][i] = TempRed[i][1];
						Red[2][i] = TempRed[i][0];
					}
				}


				White[2][0] = TempBlue[0][0];
				White[2][1] = TempBlue[1][0];
				White[2][2] = TempBlue[2][0];

				Blue[0][0] = TempYellow[0][2];
				Blue[1][0] = TempYellow[0][1];
				Blue[2][0] = TempYellow[0][0];

				Yellow[0][2] = TempGreen[2][2];
				Yellow[0][1] = TempGreen[1][2];
				Yellow[0][0] = TempGreen[0][2];

				Green[2][2] = TempWhite[2][0];
				Green[1][2] = TempWhite[2][1];
				Green[0][2] = TempWhite[2][2];

			}
		}
		else if (Rotate == 'B')
		{
			if (Dir == false) // Back 시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Orange[i][2] = TempOrange[0][i];
						Orange[i][1] = TempOrange[1][i];
						Orange[i][0] = TempOrange[2][i];
					}
				}

				White[0][0] = TempBlue[0][2];
				White[0][1] = TempBlue[1][2];
				White[0][2] = TempBlue[2][2];

				Blue[2][2] = TempYellow[2][0];
				Blue[1][2] = TempYellow[2][1];
				Blue[0][2] = TempYellow[2][2];

				Yellow[2][2] = TempGreen[2][0];
				Yellow[2][1] = TempGreen[1][0];
				Yellow[2][0] = TempGreen[0][0];

				Green[0][0] = TempWhite[0][2];
				Green[1][0] = TempWhite[0][1];
				Green[2][0] = TempWhite[0][0];

			}
			else  // Back 반시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Orange[0][i] = TempOrange[i][2];
						Orange[1][i] = TempOrange[i][1];
						Orange[2][i] = TempOrange[i][0];
					}
				}

				Blue[0][2] = TempWhite[0][0];
				Blue[1][2] = TempWhite[0][1];
				Blue[2][2] = TempWhite[0][2];

				White[0][0] = TempGreen[2][0];
				White[0][1] = TempGreen[1][0];
				White[0][2] = TempGreen[0][0];

				Green[0][0] = TempYellow[2][0];
				Green[1][0] = TempYellow[2][1];
				Green[2][0] = TempYellow[2][2];

				Yellow[2][2] = TempBlue[0][2];
				Yellow[2][1] = TempBlue[1][2];
				Yellow[2][0] = TempBlue[2][2];

			}
		}
		else if (Rotate == 'L')
		{
			if (Dir == false) // Left 시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Green[i][2] = TempGreen[0][i];
						Green[i][1] = TempGreen[1][i];
						Green[i][0] = TempGreen[2][i];
					}
				}

				White[0][0] = TempOrange[2][2];
				White[1][0] = TempOrange[1][2];
				White[2][0] = TempOrange[0][2];

				for (int i = 0; i < 3; i++)
				{
					Red[i][0] = TempWhite[i][0];
					Yellow[i][0] = TempRed[i][0];
				}

				Orange[0][2] = TempYellow[2][0];
				Orange[1][2] = TempYellow[1][0];
				Orange[2][2] = TempYellow[0][0];


			}
			else  //Left 반시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Green[0][i] = TempGreen[i][2];
						Green[1][i] = TempGreen[i][1];
						Green[2][i] = TempGreen[i][0];
					}
				}

				Orange[0][2] = TempWhite[2][0];
				Orange[1][2] = TempWhite[1][0];
				Orange[2][2] = TempWhite[0][0];

				for (int i = 0; i < 3; i++)
				{
					White[i][0] = TempRed[i][0];
					Red[i][0] = TempYellow[i][0];
				}

				Yellow[0][0] = TempOrange[2][2];
				Yellow[1][0] = TempOrange[1][2];
				Yellow[2][0] = TempOrange[0][2];


			}
		}
		else if (Rotate == 'R')
		{
			if (Dir == false) // Right 시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Blue[i][2] = TempBlue[0][i];
						Blue[i][1] = TempBlue[1][i];
						Blue[i][0] = TempBlue[2][i];
					}
				}

				Orange[2][0] = TempWhite[0][2];
				Orange[1][0] = TempWhite[1][2];
				Orange[0][0] = TempWhite[2][2];

				for (int i = 0; i < 3; i++)
				{
					White[i][2] = TempRed[i][2];
					Red[i][2] = TempYellow[i][2];
				}

				Yellow[0][2] = TempOrange[2][0];
				Yellow[1][2] = TempOrange[1][0];
				Yellow[2][2] = TempOrange[0][0];

			}
			else  // Right 반시계방향
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						Blue[0][i] = TempBlue[i][2];
						Blue[1][i] = TempBlue[i][1];
						Blue[2][i] = TempBlue[i][0];
					}
				}

				White[0][2] = TempOrange[2][0];
				White[1][2] = TempOrange[1][0];
				White[2][2] = TempOrange[0][0];

				for (int i = 0; i < 3; i++)
				{
					Red[i][2] = TempWhite[i][2];
					Yellow[i][2] = TempRed[i][2];
				}

				Orange[0][0] = TempYellow[2][2];
				Orange[1][0] = TempYellow[1][2];
				Orange[2][0] = TempYellow[0][2];

			}
		}



	}

}

void init()
{
	vec.clear();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			White[i][j] = 'w';
			Red[i][j] = 'r';
			Yellow[i][j] = 'y';
			Green[i][j] = 'g';
			Blue[i][j] = 'b';
			Orange[i][j] = 'o';
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T; 
	
	for (int nTestCase = 1; nTestCase <= T; nTestCase++)
	{
		//초기화
		bool Dir;
		init();

		//입력
		cin >> Count;
		for (int num = 0; num < Count; num++)
		{
			cin >> Input[0] >> Input[1];

			if (Input[1] == '+')
			{
				Dir = 0;
			}
			else
			{
				Dir = 1;
			}

			vec.push_back(make_pair(Input[0], Dir));
			
		}

		//풀이
		solve();
		
		//출력
		calc();
			
	}//테케 끝
	return 0;
}