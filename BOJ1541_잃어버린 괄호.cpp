// BOJ 1541 잃어버린 괄호

//문제 
//https://www.acmicpc.net/problem/1541 

//해설
//http://dhpark.kr/entry/BOJ-1541-%EC%9E%83%EC%96%B4%EB%B2%84%EB%A6%B0-%EA%B4%84%ED%98%B8

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

char cMap[50] = { 0 };

int x;

int main()
{
	bool minus = false;
	int Answer = 0;
	while (scanf("%d", &x) != EOF)
	{
		if (x < 0) minus = true;
		if (minus)
		{
			Answer -= abs(x);
		}
		else
		{
			Answer += abs(x);
		}

	}

	printf("%d", Answer);
	return 0;
}