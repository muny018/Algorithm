// 2019 �Ｚ �Ϲݱ� DS �ι�
// BOJ 17779 �Ը��Ǵ��� 2 

//����
//https://www.acmicpc.net/problem/17779

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;


// ��Ģ
/*
1) ������
ù���� ������ : (row, col)
���� ������ : (row + d1, Col - d1)
�Ʒ� ������ : (row + d1 + d2, Col - d1 + d2)
���� ������ : (row + d2, Col + d2)

2) d1, d2 Limit
 d1 Limit : ~ Col
 d2 Limit : N - Col -1 ����

 3) 5 X 1 �迭 ���� ���

 4) Sequence
   1. �� �����
   2. ����Ž������ x,y �ǳװ��鼭 �ش� ��ġ���� d1, d2 �� �Ǵ°� �־�鼭 ���
   3. 1,2,3,4,5 ������ ũ�� count �ؼ� Min Max ���̰� �ּҰ� ����

*/

struct Pos {
	int Row; 
	int Col;

};

int nMap[21][21] = { 0 };
int N;
int nAnswer = 999999999;

bool CheckLimit(int Pos_Row, int Pos_Col, int D1, int D2)
{

    // �� 4���� ���������� N ��� ���� ����°� �ִ��� üũ
    if (Pos_Row < 0 || Pos_Row >N || Pos_Col < 0 || Pos_Col > N) return false;
    if (Pos_Row + D1 > N || Pos_Col - D1 < 0) return false;
    if (Pos_Row + D1 + D2 > N || Pos_Col - D1 + D2 > N) return false;
    if (Pos_Row + D2 > N || Pos_Col + D2 > N) return false;

    return true;
}

void MakeSection(int Pos_Row, int Pos_Col, int D1, int D2)
{
    if (CheckLimit(Pos_Row, Pos_Col, D1, D2) == false) return;

	int nSum[7] = { 0 };
	Pos Pos[7];
	
	int nLabeling[21][21] = { 0 };

	//��� ������ 5�� �ʱ�ȭ
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			nLabeling[i][j] = 5;
		}
	}
	

	//ù���� ������ : (row, col)
	Pos[1].Row = Pos_Row;
	Pos[1].Col = Pos_Col;

	//���� ������ : (row + d1, Col - d1)
	Pos[2].Row = Pos_Row + D1;
	Pos[2].Col = Pos_Col - D1;

	//���� ������ : (row + d2, Col + d2)
	Pos[3].Row = Pos_Row + D2 ;
	Pos[3].Col = Pos_Col + D2 ;

	//�Ʒ� ������ : (row + d1 + d2, Col - d1 + d2)
	Pos[4].Row = Pos_Row + D1 + D2;
	Pos[4].Col = Pos_Col-D1+D2;

	int SubArea = 0, PlusArea = 0;
	//1�� ������
	for (int nRow = 0; nRow < Pos[2].Row; nRow++)
	{
		if (nRow >= Pos[1].Row) SubArea++;
		for (int nCol = 0; nCol <= Pos[1].Col - SubArea; nCol++)
		{
			nLabeling[nRow][nCol] = 1;
		}
	}

	//2�� ������+		[0]	0x00efefd8 {1, 1, 5, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}	int[21]

	SubArea = 0, PlusArea = 0;
	for (int nRow = 0; nRow <= Pos[3].Row; nRow++)
	{
		if (nRow >Pos[1].Row) PlusArea++;
		for (int nCol = Pos[1].Col + 1 + PlusArea; nCol < N; nCol++)
		{
			nLabeling[nRow][nCol] = 2;
		}
	}

	//3�� ������
	SubArea = 0, PlusArea = 0;
	for (int nRow = N-1 ; nRow >= Pos[2].Row; nRow--)
	{
		if (nRow < Pos[4].Row) SubArea++;
		for (int nCol = 0; nCol < Pos[4].Col- SubArea; nCol++)
		{
			nLabeling[nRow][nCol] = 3;
		}
	}

	//4�� ������
	SubArea = 0, PlusArea = 0;
	for (int nRow = N-1; nRow > Pos[3].Row; nRow--)
	{
		if (nRow <= Pos[4].Row) PlusArea++;
		for (int nCol = Pos[4].Col + PlusArea; nCol < N; nCol++)
		{
			nLabeling[nRow][nCol] = 4;
		}
	}


	//���
	for (int nRow = 0; nRow < N; nRow++)
	{
		for (int nCol = 0; nCol < N; nCol++)
		{
			if (nLabeling[nRow][nCol] == 1) nSum[1] += nMap[nRow][nCol];
			else if (nLabeling[nRow][nCol] == 2) nSum[2] += nMap[nRow][nCol];
			else if (nLabeling[nRow][nCol] == 3) nSum[3] += nMap[nRow][nCol];
			else if (nLabeling[nRow][nCol] == 4) nSum[4] += nMap[nRow][nCol];
			else if (nLabeling[nRow][nCol] == 5) nSum[5] += nMap[nRow][nCol];
		}
	}


	
    int nMax = 0, nMin = 99999999, nResult = 0;

    for (int i = 1; i <= 5; i++)
    {
        if (nSum[i] > nMax)  nMax = nSum[i];
        if (nSum[i] < nMin)  nMin = nSum[i];
    }

    nResult = nMax - nMin; 

    if (nResult < nAnswer) nAnswer = nResult;


}

void Solve()
{
    //��ü Row, Col �� ���� ����Ž��
    for (int Pos_Row = 0; Pos_Row < N; Pos_Row++)
    {
        for (int Pos_Col = 0; Pos_Col < N; Pos_Col++)
        {
            if (Pos_Row == 2 && Pos_Col == 2)
            {
                int stop_a = 0;
            }
            //D1, D2�� ���� ����Ž��
            for (int D1 = 1; D1 < Pos_Col; D1++)
            {
                for (int D2 = 1; D2 < N - Pos_Col; D2++)
                {
                    
                    MakeSection(Pos_Row, Pos_Col, D1, D2);

                }
            }


        }
    }


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
    
    Solve();

    cout << nAnswer << endl;

	return 0;
}