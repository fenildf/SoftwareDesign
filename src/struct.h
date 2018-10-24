#include<stdio.h>
#include<string.h>
typedef struct sql {
	char word[15];
	char tag[5];
	char trans_cn[100];
}sql;
void save(sql *L)
{
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "wordku.txt", "a");
	fprintf_s(fp, "%s %s %s\n", L->word, L->tag, L->trans_cn);
	fclose(fp);
}
void load(sql *L, int i)
{
	int j;
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "wordku.txt", "r+");
	for (j = 0; j < i; j++)
	{
		fscanf_s(fp, "%s", (L + j)->word, 15);
		fscanf_s(fp, "%s", (L + j)->tag, 5);
		fscanf_s(fp, "%s", (L + j)->trans_cn, 100);
	}
	fclose(fp);
}
void add(sql *L, int i)		//i为增加单词的数量
{
	int j;
	for (j = 0; j < i; j++, L++)
	{
		printf_s("Please input the word\n");
		gets_s(L->word, 15);
		printf_s("The tag:\n");
		gets_s(L->tag, 5);
		printf_s("The trans_cn:\n");
		gets_s(L->trans_cn, 100);
		save(L);
	}
}
void Edit(sql *L)
{
	int i;
	char Search[15];
	printf_s("Input the word you want to edit:\n");
	gets_s(Search, 15);
	for (i = 0; i < 1000; i++)
	{
		if (!strcmp(Search, L[i].word))		//查找符合的单词
			break;
	}
	printf_s("The word:\n");
	gets_s(L[i].word, 15);
	printf_s("The tag:\n");
	gets_s(L[i].tag, 5);
	printf_s("The trans_cn:\n");
	gets_s(L[i].trans_cn, 100);
}
void Delete(sql *L)
{
	int i, j;
	char Search[15];
	printf_s("Input the word you want to delete:\n");
	gets_s(Search, 15);
	for (i = 0; i < 1000; i++)
	{
		if (!strcmp(Search, L[i].word))
			break;
	}
	for (j = i + 1; j < 1000; j++)		//查找并删除
	{
		L[j - 1] = L[j];
	}
}