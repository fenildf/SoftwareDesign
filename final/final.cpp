#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE  300 
typedef int errno_t;

int amount = 0;
char name[20];
int number;
char *filename;
char wrongName[20];
int number_wrong = 0;                  //错词数
char *wrongFilename;
int wrongNum;                         // 
int user_amount=0;

typedef struct {                        //定义单词库结构体wordku
	char word[15];                     //单词
	char tag[5];                       //词性
	char trans_cn[20];				   //释义
}wordku;
wordku L[1000];

struct wrongwords {                     //定义错词库结构体wrongku
	char word[15];                     //单词
	char tag[5];                       //词性
	char trans_cn[20];                 //词义
	int  priority;                     //优先级
}wrongku[SIZE];

typedef struct {                       //定义用户结构体users
	char account[20];                  //账号
	char code[20];                     //密码
	int  times;                        //打卡次数
}user;
user p;
user man[100];

void Init();                            //初始化界面
void enroll();                          //用户注册登录
void menu();                            //菜单界面
void colour();                          //设置界面颜色
void changecode();                      //修改密码
int  wordpreview(int times);            //单词预览
void suffle(int i);   	                //单词背诵：数组（伪）无规则排序
int  intest();                          //随机产生单词
void wordstudy();                       //新词学习
void ETC();                             //英译中
void CTE();			                	//中译英
void wordspell(int j);                  //单词拼写
void cuotiben_read();                   //从错词本读入文件
void cuotiben_write();                  //从错词本写入文件
void cuotiben(int a);                   //错词本
void sort_wrong();                      //错词排序
void test_wrong();                      //错词测试
void addword();                         //词库增加
void Edit();                            //词库修改
void deleteword();                      //单词删除
void save();                            //存储新单词
void load();                            //把文件内的内容写入结构体

void Init()      //初始界面
{
	printf("\t\t\t\t\t**********************************\t\t\t\t\t\n");
	printf("\t\t\t\t\t**                              **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**      欢迎使用背单词程序      **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**                              **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**  设计者：**、**、***  **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**                              **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**********************************\t\t\t\t\t\n");
}

void chushihua()  //词库初始化
{
	int i = 0, count = 0;
	FILE *fp;
	fp = fopen("wordku.txt", "r+");
	while (!feof(fp))   //文件结束返回非零值即为真
	{
		fscanf(fp, "%s%s%s", L[i].word, L[i].tag, L[i].trans_cn);
		i++;
	}
}

void enroll()                           //定义函数：注册和登录

{
	wordku temp[1000];
	FILE *fp, *fp1, *fp2;
	fp = fopen("name.txt", "a+");
	int  m, i;
	char n[20], c[20];
	printf("\t\t\t\t\t _________________________________ \t\t\t\t\t\n");
	printf("\t\t\t\t\t|                                 |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|             1.注册              |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|             2.登陆              |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|          请选择注册或登录：     |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|                                 |\t\t\t\t\t\n");
	printf("\t\t\t\t\t|_________________________________|\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t");
	scanf("%d", &m);
	if (m == 1)
	{
		printf("\t\t\t\t\t 请设置账号名[不能超过20个字符]: ");
		getchar();
		gets_s(n);
		while(!feof(fp))
		{
			fscanf(fp, "%s", man[user_amount].account);
			fscanf(fp, "%s", man[user_amount].code);
			fscanf(fp, "%d", &man[user_amount].times);
			//user_amount++;
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
		strcpy(wrongName, n);
		strcpy(name, n);
		strcpy(p.account, n);
		printf("\t\t\t\t\t 请设置密码[不能超过20个字符]:");
		gets_s(c);
		strcpy(p.code, c);
		p.times = 1;
		fprintf(fp, "%s %s %d\n", p.account, p.code,p.times);
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
			fscanf(fp, "%d", &man[m].times);
			if (man[m].times != 0)
			{
				user_amount++;
			}
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
					strcpy(wrongName, n);
					wrongFilename = strcat(wrongName, "w.txt");
					number = m;
					strcpy(name, man[m].account);
					printf("\t\t\t\t\t 坚持打卡第%d天,继续坚持呀 ^=^\t\t\t\t\t\n", man[m].times++);
					fp = fopen("name.txt", "w+");
					for (m = 0; m < user_amount; m++)
					{
						fprintf(fp, "%s %s %d\n", man[m].account,man[m].code,man[m].times);
					}
					fclose(fp);
					getchar();
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
	int i, j, k, number, times, count;
	system("cls");
	printf("\t\t\t\t\t-----------------------------\t\t\t\t\t\n");
	printf("\t\t\t\t\t         *1.颜色设置*        \t\t\t\t\t\n");
	printf("\t\t\t\t\t         *2.修改密码*        \t\t\t\t\t\n");
	printf("\t\t\t\t\t         *3.单词学习*        \t\t\t\t\t\n");
	printf("\t\t\t\t\t         *4.词库编辑*        \t\t\t\t\t\n");
	printf("\t\t\t\t\t         *5.退出*            \t\t\t\t\t\n");
	printf("\t\t\t\t\t-----------------------------\t\t\t\t\t\n");
	printf("\t\t\t\t\t        我是菜单小能手!      \t\t\t\t\t\n");
	printf("\t\t\t\t\t       请自由选择数字[1-5]:  \t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t");
	scanf("%d", &i);
	switch (i)
	{
	case 1: colour(); break;
	case 2: changecode(); break;
	case 3:
		printf("\t\t\t\t\t-----------------------------\t\t\t\t\t\n");
		printf("\t\t\t\t\t         *1.单词预览*        \t\t\t\t\t\n");
		printf("\t\t\t\t\t         *2.单词背诵*        \t\t\t\t\t\n");
		printf("\t\t\t\t\t         *3.英译中*          \t\t\t\t\t\n");
		printf("\t\t\t\t\t         *4.中译英*          \t\t\t\t\t\n");
		printf("\t\t\t\t\t         *5.错题集整理*      \t\t\t\t\t\n");
		printf("\t\t\t\t\t-----------------------------\t\t\t\t\t\n");
		printf("\t\t\t\t\t      今天也要努力学单词呀!! \t\t\t\t\t\n");
		printf("\t\t\t\t\t       请自由选择数字[1-5]:  \t\t\t\t\t\n");
		printf("\t\t\t\t\t\t\t");
		scanf("%d", &j);
		if (j == 1)
		{
			printf("\t\t\t\t 输入你想要预览的单词数量:");
			scanf("%d", &times);
			wordpreview(times);
		}
		else if (j == 2)
		{
			printf("\t\t\t\t 输入你要背诵单词的数量：");
			scanf("%d", &number);
			wordspell(number);
		}
		else if (j == 3) {
			ETC();
		}
		else if (j == 4) {
			CTE();
		}
		else if (j == 5)
		{
			test_wrong();
		}
		else
			menu();
		break;
	case 4:
		printf("\t\t\t\t\t-----------------------------\t\t\t\t\t\n");
		printf("\t\t\t\t\t         *1.词库增加*        \t\t\t\t\t\n");
		printf("\t\t\t\t\t         *2.词库修改*        \t\t\t\t\t\n");
		printf("\t\t\t\t\t         *3.单词删除*        \t\t\t\t\t\n");
		printf("\t\t\t\t\t-----------------------------\t\t\t\t\t\n");
		printf("\t\t\t\t\t      请自由选择数字[1-3]:   \t\t\t\t\t\n");
		printf("\t\t\t\t\t\t\t");
		scanf("%d", &k);
		switch (k)
		{
		case 1:addword(); break;
		case 2:Edit(); break;
		case 3:deleteword(); break;
		}
		break;
	case 5:
		enroll();
		break;
	}
	menu();
}

void colour()          //修改背景文字颜色
{
	char con[5];
	char color[20] = "color ";
	int i;
	printf("\t\t\t\t\t\t\t");
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

void changecode()               //定义函数：修改密码
{
	getchar();
	FILE *fp;
	int m;
	printf("\t\t\t\t\t 请输入新密码:");
	gets_s(p.code);                          //输入新的密码
	fp = fopen("name.txt", "a+");          //以读写模式打开
	for (m = 0; m < 100; m++)
	{
		fscanf(fp, "%s", man[m].account);
		fscanf(fp, "%s", man[m].code);
		fscanf(fp, "%d", &man[m].times);
	}
	strcpy(man[number].code, p.code);
	fclose(fp);
	fp = fopen("name.txt", "r+");
	for (m = 0; m < 100; m++)
	{
		fprintf(fp, "%s %s %d\n", man[m].account, man[m].code,man[m].times);
	}
	fclose(fp);
	printf("\t\t\t\t\t 修改成功!\n");
	menu();
}

int wordpreview(int times)       //每页十组单词，用户通过点击按键选择页数
{
	printf("\t\t\t\t\t\t\t");
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
				scanf("%d", &num);
				system("cls");
				printf("\t\t\t%d.%s\n\t%s\n\t%s\n\tpress enter to return to menu\n\t", num, L[num - 1].word, L[num - 1].tag, L[num - 1].trans_cn);
				getchar();
				getchar();
				j = j - 1;
			}
	}
}

void ETC()	    //输入英文找中文
{
	getchar();
	printf("\t\t\t\t\t\t\t Your word：");
	char word[15];
	gets_s(word);
	int i;
	for (i = 0; i < amount; i++)
	{
		if (strcmp(word, L[i].word) == 0)
		{
			printf("\t\t\t\t\t\t %s\n \t\t\t\t\t\t %s", L[i].tag, L[i].trans_cn);
			getchar();
			break;
		}
		else
			if (i < amount - 1)
			{
				continue;
			}
		printf("此单词不在词库中\n");
		system("pause");
	}
}

void CTE()	     //输入中文找英文
{
	getchar();
	printf("\t\t\t\t\t");
	printf("释义：");
	char trans_cn[100];
	gets_s(trans_cn);
	int i;
	for (i = 0; i < amount; i++)
	{
		if (strcmp(trans_cn, L[i].trans_cn) == 0)
		{
			printf("\t\t\t\t\t\t %s \n \t\t\t\t\t\t %s", L[i].tag, L[i].word);
			getchar();
			break;
		}
		else
			if (i < amount - 1)
			{
				continue;
			}
		printf("此单词不在词库中\n");
		system("pause");
	}
}

int intest()    //产生随机单词以进行测试
{
	srand((unsigned)(time(NULL)) + rand());
	return(rand() % 99 + 1);
}

void wordspell(int num)	    //单词拼写
{
	int i, m;
	int corrNum = 0;		//正确单词个数
	char word[100];
	for (i = 0; i < num; i++)
	{
		system("cls");
		m = intest();
		printf("%s\n", L[m].trans_cn);
		printf("请输入中文所对应的英文单词：\n");
		scanf("%s", word);
		if (strcmp(word, L[m].word) == 0)
		{
			printf("You are correct!\nplease press enter to the next word\n");
			corrNum++;
			getchar();
			getchar();
			continue;
		}
		else
		{
			cuotiben(m);
			printf("Um,you are wrong!\n Come on,please!\n");
			getchar();
			continue;
		}
		wrongNum = num - corrNum;
	}
	int  rate = 100 * ((float)corrNum / (float)num);
	switch (rate)      //正确率
	{
	case 0:
	case 10:
	case 20:
	case 30:
		printf("\t\t\t\t\t您的正确率为%d%%\n", rate);
		printf("\t\t\t\t\t还需努力!\n");
		getchar();
		getchar();
		break;
	case 40:
	case 50:
	case 60:
		printf("\t\t\t\t\t您的正确率为%d%%\n", rate);
		printf("\t\t\t\t\t还不错!\n");
		getchar();
		getchar();
		break;
	case 70:
	case 80:
	case 90:
	case 100:
		printf("\t\t\t\t\t您的正确率为%d%%\n", rate);
		printf("\t\t\t\t\tGreat!好样的!\n");
		getchar();
		getchar();
		break;
	}
}

void cuotiben_read()    //错题本从文件读入
{
	FILE *fp3;
	int i = 0;
	fp3 = fopen(wrongFilename, "r+");
	while (!feof(fp3))   //文件结束返回非零值即为真
	{
		fscanf(fp3, "%s %s %s %d", wrongku[i].word, wrongku[i].tag, wrongku[i].trans_cn, &wrongku[i].priority);
		i++;
	}
	number_wrong = i;
	fclose(fp3);
}

void cuotiben_write()    //错题写入文件
{
	FILE *fp4;
	int i = 0;
	fp4 = fopen(wrongFilename, "r+");
	for (i; i < number_wrong + wrongNum; i++)
	{
		fprintf(fp4, "%s %s %s %d\n", wrongku[i].word, wrongku[i].tag, wrongku[i].trans_cn, wrongku[i].priority);
	}
	fclose(fp4);
}

void cuotiben(int a)     //加入错词本
{
	int i = 0, count = 0;
	for (i = 0; i < number_wrong; i++)
	{
		if (strcmp(wrongku[i].word, L[a].word) == 0)
		{
			wrongku[i].priority++;
			break;
		}
	}
	if (i == number_wrong)
	{
		number_wrong++;
		count = number_wrong - 1;
		strcpy(wrongku[count].word, L[a].word);
		strcpy(wrongku[count].tag, L[a].tag);
		strcpy(wrongku[count].trans_cn, L[a].trans_cn);
		wrongku[count].priority = 3;      //当答对3次后即可从错题集删除
	}
	cuotiben_write();
}

void sort_wrong()  //按照错词的优先级排序
{
	int i, k, index;
	for (k = 0; k < number_wrong - 1; k++)           //冒泡法
	{
		index = k;
		for (i = k + 1; i < number_wrong; i++)
			if (wrongku[i].priority > wrongku[index].priority)
				index = i;
		if (index != k)
		{
			wrongku[number_wrong] = wrongku[index];
			wrongku[index] = wrongku[k];
			wrongku[k] = wrongku[number_wrong];
		}
	}
	for (i = 0; i < number_wrong; i++)
	{
		if (wrongku[i].priority == 0)
		{
			number_wrong = i; break;
		}
	}
	cuotiben_write();
}

void test_wrong()  //错词测试
{
	int i, num;
	char word[30];
	sort_wrong();
	printf("请输入您的目标复习个数:");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		printf("%s\n请输入对应的单词：", wrongku[i].trans_cn);
		scanf("%s", word);
		if (strcmp(wrongku[i].word, word) == 0)
		{
			printf("正确!\n");
			wrongku[i].priority--;
		}
		else
		{
			printf("错误!\n");
			wrongku[i].priority++;
		}
	}
	sort_wrong();
}

void addword()            //定义函数：词库补充
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

void deleteword()          //定义函数：单词删除
{
	char word[20];
	int i, j;
	printf("\t\t\t\t\t   请输入您要删除的单词：");
	getchar();
	gets_s(word);
	for (i = 0; i < amount; i++)
	{
		if (!strcmp(word, L[i].word))		//查找符合项
		{
			amount--;
			break;
		}
		else
			printf("未找到对应的单词");
	}
	for (j = i + 1; j < 1000; j++)
	{
		L[j - 1] = L[j];		 //删除的元素之后所有项向前移一位
	}
	printf("press any key to continue\n");
	getchar();
	menu();
}

void suffle(int i)	        //数组（伪）无规则排序
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

void save()               //存储新单词
{
	int i;
	FILE *fp = fopen(name, "w");
	for (i = 0; i < amount; i++)
	{
		fprintf(fp, "%s %s %s\n", L[i].word, L[i].tag, L[i].trans_cn);
	}
	fclose(fp);
}

void load()            //把文件内的内容写入结构体
{
	filename = strcat(name, ".txt");
	FILE *fp = fopen(filename, "r+");
	char count[20], *file;
	while(!feof(fp))
	{
		fscanf(fp, "%s", (L + amount)->word, 15);
		fscanf(fp, "%s", (L + amount)->tag, 5);
		fscanf(fp, "%s", (L + amount)->trans_cn, 100);
		amount++;
	}
	fclose(fp);
}

void Edit()                //词库编辑
{
	int i;
	char Search[15];
	printf("Input the word you want to edit:\n");
	getchar();
	gets_s(Search);
	for (i = 0; i < amount; i++)
	{
		if (strcmp(Search, L[i].word) == 0)
		{
			printf("修改单词:");
			gets_s(L[i].word);
			printf("修改词性:");
			gets_s(L[i].tag);
			printf("修改释义:");
			gets_s(L[i].trans_cn);
			getchar();
			save();
			break;
		}
		else
			if (i < amount - 1)
			{
				continue;
			}
		printf("此单词不在词库中\n");
		getchar();
	}
}

int main()
{
	Init();
	//colour();
	enroll();
	chushihua();
	cuotiben_read();
	menu();
	cuotiben_write();
	return 0;
}

