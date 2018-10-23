#include<stdio.h>
#include<string.h>
typedef struct {
	char word[15];
	char tag[5];
	char trans_cn[100];
}sql;
void save(sql *L)
{
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "word.txt", "a");
	fprintf_s(fp, "%s,%s,%s\n", L->word, L->tag, L->trans_cn);
	fclose(fp);
}
/*void load()
{
	char a[10], b[10], c[10];
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "word.txt", "r+");
	fscanf_s(fp,"%s,%s,%s",a ,b, c);
	printf_s("%s,%s,%s", a, b, c);
	fclose(fp);
}*/
void add(sql *L, int i)		
{
	int j;
	for (j = 0; j < i; j++,L++)
	{
		printf_s("Please input the word\n");
		gets(L->word);
		printf_s("The tag:\n");
		gets(L->tag);
		printf_s("The trans_cn:\n");
		gets(L->trans_cn);
		save(L);
	}
}
void Edit(sql *L)
{
	int i;
	char Search[15];
	printf_s("Input the word you want to edit:\n");
	gets(Search);
	for (i = 0; i < 1000; i++)
	{
		if (!strcmp(Search, L[i].word))	
			break;
	}
	printf_s("The word:\n");
	gets(L[i].word);
	printf_s("The tag:\n");
	gets(L[i].tag);
	printf_s("The trans_cn:\n");
	gets(L[i].trans_cn);
}
void Delete(sql *L)
{
	int i,j;
	char Search[15];
	printf_s("Input the word you want to delete:\n");
	gets(Search);
	for (i = 0; i < 1000; i++)
	{
		if (!strcmp(Search, L[i].word))
			break;
	}
	for (j = i + 1; j < 1000; j++)
	{
		L[j-1]= L[j];
	}
}
int main()
{
	int i;
	sql test[1000];
	add(test, 3);
	//load(test);
	for (i = 0; i < 3; i++)
	{
		printf_s("The word is:\n");
		puts(test[i].word);
		puts(test[i].tag);
		puts(test[i].trans_cn);
	}
	Edit(test);
	Delete(test);
}