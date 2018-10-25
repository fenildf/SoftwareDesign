#include<iostream>
#include"struct.h"
#include<stdlib.h>
#include<time.h>
using namespace std;

void suffle(sql L[],int i)	//数组（伪）无规则排序
{
	srand(time(0));
	int j;
	sql temp;
	for (i; i>1; i--)
	{
		srand(time(0));
		int n = rand() % (i + 1);
		if (n == i )
		{
			continue;
		}
		temp = L[n];
		for (j = 0; j < i - n-1 ; j++)
		{
			L[n + j] = L[n + j + 1];
		}
		L[i - 1] = temp;
	}
}

void review(sql L[],int j)	//答题
{
	int i;
	char corr[100];
	for (i = 0; i < j; i++)
	{
		system("cls");
		printf("%s,%d\n",  L[i].word,L[i].wrong);
		printf("请输入中文释义：\n");
		scanf_s("%s",corr,100);
		if (strcmp(corr,L[i].trans_cn)==0)
		{
			printf("You are correct\npress enter to the next word\n");
			getchar();
			getchar();
		}
		else
		{
			printf("you are wrong\nplease try again\n");
			L[i].wrong++;
			getchar();
			getchar();
			i = i - 1;
		}
	}
}

int sort(sql L[],sql M[], int i)	//错题整理
{
	int j;
	int n = 0;
	for (j = 0; j < i; j++)
	{
		if (L[j].wrong != 0)
		{
			M[n] = L[j];
			n++;
		}
	}
	return n;
}