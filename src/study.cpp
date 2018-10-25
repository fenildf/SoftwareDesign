#include<iostream>
#include"struct.h"
using namespace std;
int sectionPrint(sql L[],int times)
{
	int i,j,num;
	for (j=0;j<times/10;j++)
	{
		system("cls");
		printf("press i to choose the word you want to learn\npress x to exit\npress q to the previous page\npress any other keys to the next page\n");
		for (i = 10 * j; i < (j+1) * 10 ; i++)
		{
			printf("%d.%s\n", i + 1, L[i].word);
		}
		if (j == (times / 10-1) && times % 10 != 0)
		{
			for (i = 10 * (j+1); i < times; i++)
			{
				printf("%d.%s\n", i + 1, L[i].word);
			}
			printf("That's the end of the menu,press enter three times to exit\n");
		}
		char press = getchar();
		if (press == 'x')
		{
			return 0;
		}
		getchar();
		if (press == 'q')
		{
			j = j - 2;
			continue;
		}
		else
			if (press == 'i')
			{
				printf("choose the word you want to learn\n");
				scanf_s("%d", &num);
				system("cls");
				printf("\t\b\b%d.%s\n\t%s\n\t%s\n\tpress enter to return to menu\n\t",num, L[num-1].word, L[num-1].tag, L[num-1].trans_cn);
				getchar();
				getchar();
				j = j - 1;
			}
	}
}