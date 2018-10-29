#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

int amount = 100;
char name[20];
int number;

typedef struct {                       //定义单词库结构体wordku
	char word[15];                     //单词
	char tag[5];                       //词性
	char trans_cn[20];				   //释义
	int wrongnumber;						   //错误次数
}wordku;

void kong();                           //初始化界面
void enroll();                         //用户注册登录
void menu();                           //菜单界面
void colour();                         //设置界面颜色
void changecode();                     //修改密码
int  sectionPrint(wordku L[], int times);  //单词预览
void wordstudy();                      //新词学习
void ETC(wordku L[], int j);             //英译中
void CTE(wordku L[], int j);				//中译英
void wordspell();                      //单词拼写
int  sort(wordku L[], wordku M[], int i);     //错题集整理
void addku();                          //词库增加
void correctku();                      //词库修改
void deleteku();                       //单词删除
void addword();                        //词库补充
void suffle(wordku L[], int i);   	       //单词背诵：数组（伪）无规则排序

/*typedef struct {                        //定义文件结构体，储存该应用的账号密码
	char name[20];                     //账号
	char code[20];                     //密码
}FILE;*/

typedef struct {                       //定义用户结构体users
	char account[20];                  //账号
	char code[20];                     //密码
}user;
user p;
user man[100];



void enroll()                           //定义函数：注册和登录
{
	wordku temp[1000];
	FILE *fp,*fp1,*fp2;
	fp = fopen("name.txt", "a+");
	int count = 0;                        //定义打卡次数    
	int  m,i;
	char n[20], c[20];
	printf("\t\t\t\t\t 1.注册\n");
	printf("\t\t\t\t\t 2:登录\n");
	printf("\t\t\t\t\t 请选择注册或登录:");
	scanf_s("%d", &m);
	if (m == 1)
	{
		printf("\t\t\t\t\t 请设置账号名[不能超过20个字符]:\n\t\t\t\t\t ");
		getchar();
		gets_s(n);
		for (m = 0; m < 100; m++)
		{
			fscanf(fp, "%s", man[m].account);
			fscanf(fp, "%s", man[m].code);
		}
		for (m = 0; m < 100; m++)
		{
			if (!strcmp(n, man[m].account))
			{
				printf("\t\t\t\t\t 此用户名已经存在\n");
				printf("\t\t\t\t\t 请重新输入用户名:");
				gets_s(n);
			}
			else
			{
				continue;
			}
		}
		strcpy(name,n);
		strcpy(p.account, n);
		printf("\t\t\t\t\t 请设置密码[不能超过20个字符]:");
		gets_s(c);
		strcpy(p.code, c);
		fprintf(fp, "%s %s\n", p.account, p.code);
		fclose(fp);
		printf("\t\t\t\t\t 您已注册成功! 您的账号为:%s\n", p.account);
		char *filename = strcat(name, ".txt");
		fp1 = fopen(filename, "a+");
		fp2 = fopen("wordku.txt", "a+");
		for (i = 0; i < 100; i++)
		{
			fscanf(fp2, "%s", temp[i].word);
			fscanf(fp2, "%s", temp[i].tag);
			fscanf(fp2, "%s", temp[i].trans_cn);
			fprintf(fp1, "%s %s %s\n", temp[i].word, temp[i].tag, temp[i].trans_cn);
		}
		printf("\t\t\t\t\t 请重新登录");
		getchar();
		system("cls");
		enroll();
	}
	else                                   //登录
	{
		printf("\t\t\t\t\t 请输入账号:");
		getchar();
		gets_s(n);
		for (m = 0; m < 100; m++)
		{
			fscanf(fp, "%s", man[m].account);
			fscanf(fp, "%s", man[m].code);
		}
		fclose(fp);
		for (m = 0; m < 100; m++)
		{
			if (!strcmp(n, man[m].account))
			{
				printf("\t\t\t\t\t 请输入密码:");
				gets_s(c);
				if (!strcmp(c, man[m].code))
				{
					printf("\t\t\t\t\t 登陆成功\n");
					number = m;
					strcpy(name, man[m].account);
					break;
				}
			}
			else 
			{
				continue;
			}
			printf("\t\t\t\t\t 登录失败\n");
			printf("\t\t\t\t\t 请重新输入\n");
			system("cls");
			enroll();
		}
	}
}
/*void menu()            //定义函数：菜单
{
	int i, j, k;
	printf("\t\t\t\t          0:颜色设置           \t\t\t\t");   //定义菜单选项，从0-4自主选择
	printf("\t\t\t\t          1:修改密码		 \t\t\t\t");
	printf("\t\t\t\t          2:单词学习		  \t\t\t\t");
	printf("\t\t\t\t          3:词库编辑         \t\t\t\t");
	printf("\t\t\t\t          4:退出             \t\t\t\t");
	printf("\t\t\t请自由选择数字[0-3]：\n");
	scanf("%d", &i);
		switch (i)
		{
		case 0: colour(); break;
		case 1: changecode(); break;
		case 2:
			printf("\t\t\t\t   1:单词预览       \t\t\t\t");
			printf("\t\t\t\t   2:单词背诵	    \t\t\t\t");
			printf("\t\t\t\t   3:英译中         \t\t\t\t");
			printf("\t\t\t\t   4:错题集整理     \t\t\t\t");
			printf("\t\t\t请自由选择数字[1-4]:  \t\t\t\t");
				scanf("%d", &j);
			if (j == 1)
				sectionPrint();               //未完成
			else if (j == 2)

			else if (j == 3)
				review(wordku L[], int j);        //参数未设置
			else if (j == 4)
				sort(wordku L[], wordku M[], int i)；
			else
				menu();
			break;
		case 3:
			printf("\t\t\t\t   1:词库增加        \t\t\t\t");
			printf("\t\t\t\t   2:词库修改        \t\t\t\t");
			printf("\t\t\t\t   3:单词删除        \t\t\t\t");
			printf("\t\t\t\t   4:词库补充        \t\t\t\t");
			printf("\t\t\t请自由选择数字[1-4]:   \t\t\t\t");
			scanf("%d", &k);
			switch (k)
			{
			case 1:addku(); break;
			case 2:correctku(); break;
			case 3:deleteku(); break;
			case 4:addword(); break;
			}
			break;
		case 4:
			enroll();
			break;
		}
}*/
void changecode()                         //定义函数：修改密码
{
	FILE *fp;
	int m;
	printf("\t\t\t\t\t 请输入新密码:");
	gets_s(p.code);                      //输入新的密码
	fp = fopen("name.txt", "a+");            //以读写模式打开
	for (m=0;m<100;m++)
	{
		fscanf(fp, "%s", man[m].account);
		fscanf(fp, "%s", man[m].code);
	}
	strcpy(man[number].code,p.code);
	fclose(fp);
	fp = fopen("name.txt", "r+");
	for (m = 0; m < 100; m++)
	{
		fprintf(fp, "%s %s\n", man[m].account,man[m].code);
	}
	fclose(fp);
	printf("\t\t\t\t\t 修改成功!\n");
	//menu();
}

/*int main()
{
	FILE *fp;
	enroll();
	changecode();
	getchar();
	getchar();
}*/