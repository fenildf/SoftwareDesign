#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include <time.h>
#define  SIZE  300 

int amount = 100;
char name[20];
int number;
char *filename;
int number_wrong = 0;                  //错词数


typedef struct {                       //定义单词库结构体wordku
	char word[15];                     //单词
	char tag[5];                       //词性
	char trans_cn[20];				   //释义
	int wrongnumber;						   //错误次数
}wordku;
wordku L[1000];
wordku M[1000];

typedef struct {                       //定义错词库结构体wrongku
	char word[15];                     //单词
	char tag[5];                       //词性
	char trans_cn[20];                 //词义
	int  priority;                     //优先级
}wrongku[SIZE];

typedef struct {                       //定义用户结构体users
	char account[20];                  //账号
	char code[20];                     //密码
}user;
user p;
user man[100];


void kong();                           //初始化界面
void enroll();                         //用户注册登录
void menu();                           //菜单界面
void colour();                         //设置界面颜色
void changecode();                     //修改密码
int  sectionPrint(int times);  //单词预览
void wordstudy();                      //新词学习
void ETC();             //英译中
void CTE();				//中译英
void wordspell(int j);                      //单词拼写
int  sort(int i);     //错题集整理
//void addku();                          //词库增加
//void correctku();                      //词库修改
//void deleteku();                       //单词删除
void addword();                        //词库补充
void suffle(int i);   	       //单词背诵：数组（伪）无规则排序
void deleteword();
void save();
void load();
void Edit();
void cuotiben_read();                  //从错题本读入文件
void cuotiben_write();                 //从错题本写入文件
void cuotiben(int a);                  //错题本
void sort_wrong();                     //错词排序
void test_wrong();                     //错词测试




void enroll()                           //定义函数：注册和登录
{
	wordku temp[1000];
	FILE *fp, *fp1, *fp2;
	fp = fopen("name.txt", "a+");
	int count = 0;                        //定义打卡次数    
	int  m, i;
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
		strcpy(name, n);
		strcpy(p.account, n);
		printf("\t\t\t\t\t 请设置密码[不能超过20个字符]:");
		gets_s(c);
		strcpy(p.code, c);
		fprintf(fp, "%s %s\n", p.account, p.code);
		fclose(fp);
		printf("\t\t\t\t\t 您已注册成功! 您的账号为:%s\n", p.account);
		filename = strcat(name, ".txt");
		fp1 = fopen(filename, "a+");
		fp2 = fopen("wordku.txt", "a+");
		for (i = 0; i < 100; i++)
		{
			fscanf(fp2, "%s", temp[i].word);
			fscanf(fp2, "%s", temp[i].tag);
			fscanf(fp2, "%s", temp[i].trans_cn);
			fprintf(fp1, "%s %s %s\n", temp[i].word, temp[i].tag, temp[i].trans_cn);
		}
		fclose(fp1);
		fclose(fp2);
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
					system("cls");
					load();
					menu();
				}
			}
			else
			{
				continue;
			}
			printf("\t\t\t\t\t 登录失败\n");
			printf("\t\t\t\t\t 请重新输入\n");
			getchar();
			system("cls");
			enroll();
		}
	}
}
void menu()            //定义函数：菜单
{
	int i, j, k,m,times;
	system("cls");
	printf("\t\t\t\t 0:颜色设置\n");   //定义菜单选项，从0-4自主选择
	printf("\t\t\t\t 1:修改密码\n");
	printf("\t\t\t\t 2:单词学习\n");
	printf("\t\t\t\t 3:词库编辑\n");
	printf("\t\t\t\t 4:退出\n");
	printf("\t\t\t\t 请自由选择数字[0-4]:");
	scanf("%d", &i);
		switch (i)
		{
		case 0: colour(); break;
		case 1: changecode(); break;
		case 2:
			printf("\t\t\t\t 1:单词预览\n");
			printf("\t\t\t\t 2:单词背诵\n");
			printf("\t\t\t\t 3:英译中\n");
			printf("\t\t\t\t 4.中译英\n");
			printf("\t\t\t\t 5:错题集整理\n");
			printf("\t\t\t\t 请自由选择数字[1-5]:");
				scanf("%d", &j);
				if (j == 1) {
					printf("\t\t\t\t 输入你想要预览的单词数量：");
					scanf("%d", &times);
					sectionPrint(times);
				}
				else if (j == 2)
				{
					printf("\t\t\t\t 输入你要背诵单词的数量：");
					scanf("%d", &m);
					wordspell(m);
				}
				else if (j == 3) {
					ETC();
				}
				else if (j == 4)
					CTE();
				else if (j == 5)
					sort(i);
			else
				menu();
				break;
		case 3:
			printf("\t\t\t\t 1:词库增加\n");
			printf("\t\t\t\t 2:词库修改\n");
			printf("\t\t\t\t 3:单词删除\n");
			printf("\t\t\t\t 请自由选择数字[1-4]:");
			scanf("%d", &k);
			switch (k)
			{
			case 1:addword(); break;
			case 2:Edit(); break;
			case 3:deleteword; break;
			}
			break;
		case 4:
			enroll();
			break;
		}
		menu();
}
void colour()
{
	char con[5];
	char color[20] = "color ";
	int i;
	getchar();
	puts("\t\t\t\t\t****************背景颜色和文字颜色****************\t\t\t\t\t\n");
	printf("\t\t\t\t\t|-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\t\t\t\t\t\n");
	printf("\t\t\t\t\t|                                                |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         0 = 黑色          8 = 灰色             |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         1 = 蓝色          9 = 浅蓝色           |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         2 = 绿色          A = 淡绿色           |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         3 = 浅绿色        B = 淡浅绿色         |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         4 = 红色          C = 淡红色           |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         5 = 紫色          D = 淡紫色           |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         6 = 黄色          E = 淡黄色           |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|         7 = 白色          F = 亮白色           |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\t\t\t\t\t\n");
	printf("\t\t\t\t\t请输入两位数，第一位为背景颜色，第二位为文字颜色\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t");
	fflush(stdin);
	gets_s(con);             //获取背景和文字颜色显示选项  
	strcat(color, con);     //合并color和选项  
	system(color);         //调用system（）函数实现显示颜色变化  
	printf("\n");
	printf("\t\t\t\t\t请输入1/0选择继续修改颜色or返回菜单\n");
	printf("\t\t\t\t\t\t\t");
	scanf("%d", &i);
	if (i == 0)
	{
		menu();
	}
	if (i == 1)
	{
		colour();
	}
	system("cls");
}
void changecode()                         //定义函数：修改密码
{
	getchar();
	FILE *fp;
	int m;
	printf("\t\t\t\t\t 请输入新密码:");
	gets_s(p.code);                      //输入新的密码
	fp = fopen("name.txt", "a+");            //以读写模式打开
	for (m = 0; m < 100; m++)
	{
		fscanf(fp, "%s", man[m].account);
		fscanf(fp, "%s", man[m].code);
	}
	strcpy(man[number].code, p.code);
	fclose(fp);
	fp = fopen("name.txt", "r+");
	for (m = 0; m < 100; m++)
	{
		fprintf(fp, "%s %s\n", man[m].account, man[m].code);
	}
	fclose(fp);
	printf("\t\t\t\t\t 修改成功!\n");
	menu();
}
int sectionPrint(int times)       //每页十组单词，用户通过点击按键选择页数
{
	getchar();
	int i, j, num;
	for (j = 0; j < times / 10; j++)
	{
		system("cls");                    //清除页面内容
		printf("press i to choose the word you want to learn \n press x to exit \n press q to the previous page \n press any other keys to the next page\n");
		// 点击i选择要学习的单词 ，x代表退出 ，q代表前一页，任意其他的字母代表下一页
		for (i = 10 * j; i < (j + 1) * 10; i++)
		{
			printf("%d.%s\n", i + 1, L[i].word);
		}
		if (j == (times / 10 - 1) && times % 10 != 0)
		{
			for (i = 10 * (j + 1); i < times; i++)
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
				printf("\t\b\b%d.%s\n\t%s\n\t%s\n\tpress enter to return to menu\n\t", num, L[num - 1].word, L[num - 1].tag, L[num - 1].trans_cn);
				getchar();
				getchar();
				j = j - 1;
			}
	}
}

void ETC()	    //输入英文找中文
{
	getchar();
	printf("\t\t\t\t Your word：");
	char word[15];
	gets_s(word, 15);
	int i;
	for (i = 0; i < amount; i++)
	{
		if (strcmp(word, L[i].word) == 0)
		{
			printf("%s\n%s", L[i].tag, L[i].trans_cn);
			getchar();
			break;
		}
		else
		{
			continue;
		}
		printf("此单词不在词库中");
		getchar();
	}
}
void CTE()	    //输入中文找英文
{
	getchar();
	printf("释义：\n");
	char trans_cn[100];
	gets_s(trans_cn, 100);
	int i;
	for (i = 0; i < amount; i++)
	{
		if (strcmp(trans_cn, L[i].trans_cn) == 0)
		{
			printf("%s\n%s", L[i].tag, L[i].word);
			break;
		}
		else
		{
			continue;
		}
		printf("此单词不在词库中");
	}
}
void wordspell(int j)	    //单词拼写
{
	wordku temp[200];
	int i;
	int corrNum=0;		//正确单词个数
	char word[100];
	for (i = 0; i < j; i++)
	{
		system("cls");
		printf("%s\n", L[i].trans_cn);
		printf("请输入中文所对的英文单词：\n");
		scanf_s("%s", word, 100);
		if (strcmp(word, L[i].word) == 0)
		{
			printf("You are correct!\n please press enter to the next word\n");
			corrNum++;
			getchar();
			getchar();
		}
		else
		{
			printf("Um,you are wrong!\n please try again\n");
			L[i].wrongnumber++;
			getchar();
			getchar();
			i = i - 1;
		}
	}
	printf("Your score is %d", corrNum * 10);
}


int sort(int i)       	//错题整理
{
	int j;
	int n = 0;
	for (j = 0; j < i; j++)
	{
		if (L[j].wrongnumber != 0)
		{
			M[n] = L[j];
			n++;
		}
	}
	return n;
}

void addword()                            //定义函数：词库补充
{
	char ch;
	printf("\t\t\t\t\t请输入您要添加的单词：");
	getchar();
	gets_s(L[amount].word);
	printf("\t\t\t\t\t该词的词性：");
	gets_s(L[amount].tag);
	printf("\t\t\t\t\t中文意思:");
	gets_s(L[amount].trans_cn);
	printf("\t\t\t\t\t您是否还要继续？ Y/Any other :");
	amount++;
	save();
	scanf("%c", &ch);
	getchar();
	if (ch == 'Y')
	{
		addword();
	}
	else
	{
		return;
	}
	getchar();
}

void deleteword()                       //定义函数：单词删除
{
	char word[20];
	int i,j;
	int m;
	printf("\t\t\t\t\t   请输入您要删除的单词：");
	getchar();
	gets_s(word);
	for (i = 0; i < amount; i++)
	{
		if (!strcmp(word, L[i].word))		//查找符合项
		{
			amount++;
			break;
		}
		else
			printf("未找到对应的单词");
	}
	for (j = i + 1; j < 1000; j++)
	{
		L[j - 1] = L[j];		//删除的元素之后所有项向前移一位
	}
	printf("press any key to continue\n");
	getchar();
	menu();
}

void suffle(int i)	//数组（伪）无规则排序
{
	srand(time(0));
	int j;
	wordku temp;
	for (i; i > 1; i--)
	{
		srand(time(0));
		int n = rand() % (i + 1);
		if (n == i)
		{
			continue;
		}
		temp = L[n];
		for (j = 0; j < i - n - 1; j++)
		{
			L[n + j] = L[n + j + 1];
		}
		L[i - 1] = temp;
	}
}



void init(int i = 1000)
{
	int j;
	for (j = 0; j < i; j++)
	{
		L[j] = { "","","",0 };
	}
}

void save()               //存储新单词
{
	int i;
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, name, "a");
	for (i = 0; i < amount;i++)
	{
		fprintf_s(fp, "%s %s %s\n", L[i].word, L[i].tag, L[i].trans_cn);
	}
	fclose(fp);
}

void load()
{
	int j;
	FILE *fp,*fp1;
	errno_t err;
	char count[20],*file;
	filename = strcat(name, ".txt");
	err = fopen_s(&fp, filename, "r+");
	for (j = 0; j < 100; j++)
	{
		fscanf_s(fp, "%s", (L + j)->word, 15);
		fscanf_s(fp, "%s", (L + j)->tag, 5);
		fscanf_s(fp, "%s", (L + j)->trans_cn, 100);
	}
	fclose(fp);
}


void Edit()
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

int main()
{
	init();
	enroll();
}