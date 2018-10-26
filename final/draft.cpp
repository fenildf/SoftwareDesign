#include<stdio.h>
#include<stdilb.h>
#include<string.h>
#include<conio.h>
#include<struct.h>

void kong();                           //初始化界面
int  enroll();                         //用户注册登录
void menu();                           //菜单界面
void colour();                         //设置界面颜色
void changecode();                     //修改密码
int  sectionPrint(sql L[],int times);  //单词预览
void wordstudy();                      //新词学习
void review(sql L[],int j)             //英译中
void wordspell();                      //单词拼写
int  sort(sql L[],sql M[], int i);     //错题集整理
void addku();                          //词库增加
void correctku();                      //词库修改
void deleteku();                       //单词删除
void addword();                        //词库补充
void suffle(sql L[],int i);   	       //单词背诵：数组（伪）无规则排序
 


typedef struct{                        //定义文件结构体，储存该应用的账号密码
	char name[20];                     //账号
	char code[20];                     //密码
}FILE;

typedef struct {                       //定义用户结构体users
	char account[20];                  //账号
    char code[20];                     //密码
}user;
user p;

typedef struct {                       //定义单词库结构体wordku
	char word[15];                     //单词
	char tag[5];                       //词性
	char trans_cn[20];                 //释义
}wordku;
          
typedef stuct{                         //定义错题集结构体wrongku
	char word[15];                     //错词
	char tag[5];                       //词性
	char trans_cn[20];                 //释义
}wrongku;

typedef struct {                       //定义sq1结构体
	char word[15];                     //
	char tag[5];
	char trans_cn[100];
	int wrong;
}sql;

void kong()  //初始界面
{
	printf("\t\t\t\t\t**********************************\t\t\t\t\t\n");
	printf("\t\t\t\t\t**                              **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**      欢迎使用背单词程序      **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**                              **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**  设计者：吴昊、曹丹、吴雨欣  **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**                              **\t\t\t\t\t\n");
	printf("\t\t\t\t\t**********************************\t\t\t\t\t\n");
}
 
int enroll()                           //定义函数：注册和登录
{ 
	int count=0;                        //定义打卡次数    
	int  m;
	char n[20],c[20];
	printf("\t\t\t\t\t 1.注册            \t\t\t\t\t")；
	printf("\t\t\t\t\t 2:登录            \t\t\t\t\t");
	printf("\t\t\t\t\t 请选择注册或登录：\t\t\t\t\t");
	scanf("%d",&m);
	if((p=fopen("name.txt","r+"))==NULL)   //name.text为存储账号和密码的文件
	{
		p=fopen("name.txt","w+");                
	}
    if(m==1)
	{
		FILE *fp;                         //定义一个指向文件的指针变量fp
     	fp=fopen("name.txt","r+");        //将fopen函数的返回值赋给指针变量fp
	    printf("\t\t\t  请设置账号名[不能超过20个字符]：\t\t\t\t\t");
	    getchar();
	    gets(n);
	    strcpy(p.account,n);
	    printf("\t\t\t  请设置密码[不能超过20个字符]：  \t\t\t\t\t");
    	gets(c);
	    strcpy(p.code,c);
     	fprintf(fp,"%s %s",p.account,p.code);
	    fclose(fp);
	    printf("\t\t\t  您已注册成功! 您的账号为:%d              \t\t\t\t\t",p.account);
	}
	else                                   //登录
	{
		printf("\t\t\t         请输入账号:          \t\t\t\t\t");        
	    getchar();
	    gets();
	    fgets(fp,"%s %s,p.account,p.code");
	    fclose(fp);
    	if(!strcmp(p.account,n))
		{
			printf("\t\t\t\t    请输入密码:");
	        gets(c);
			if(!strcmp(p.code,c))
			{
				printf("\t\t    登陆成功!      \t\t\t\t");
			    printf("\t\t    坚持打卡第%d天 \t\t\t\t",++count);       //登录成功则打卡
			}
		    else 
			{
				printf("\t\t     密码错误!   \t\t\t\t");
				printf("\t\t     请重新输入! \t\t\t\t");
				enroll();
			}
		}
		else 
		{
			printf("\t\t\t\t     用户名错误! \t\t\t\t");
			printf("\t\t\t\t     请重新输入! \t\t\t\t");
			enroll();
		}
		count++;
		fclose(fp);
		return p.account();
	}


	void menu()            //定义函数：菜单
	{
		int i,j,k;                                         
		printf("\t\t\t\t          0:颜色设置           \t\t\t\t");   //定义菜单选项，从0-4自主选择
    	printf("\t\t\t\t          1:修改密码		 \t\t\t\t");
	    printf("\t\t\t\t          2:单词学习		  \t\t\t\t");
	    printf("\t\t\t\t          3:词库编辑         \t\t\t\t");
		printf("\t\t\t\t          4:退出             \t\t\t\t");
	    printf("\t\t\t请自由选择数字[0-3]：\n")；         
	    scanf("%d",&i)；
		switch(i)
		{
			case 0: colour();break;
            case 1: changecode(); break;
	    	case 2:
				printf("\t\t\t\t   1:单词预览       \t\t\t\t");
				printf("\t\t\t\t   2:单词背诵	    \t\t\t\t");
				printf("\t\t\t\t   3:英译中         \t\t\t\t");
				printf("\t\t\t\t   4:错题集整理     \t\t\t\t");
			    printf("\t\t\t请自由选择数字[1-4]:  \t\t\t\t")； 
					scanf("%d",&j);
				if(j == 1)   
					sectionPrint();               //未完成
				else if(j == 2)
				    
				else if(j == 3)
				    review(sql L[],int j);        //参数未设置
				else if(j == 4)
					sort(sql L[],sql M[], int i)；
				else
					menu();
				break;
			case 3:
				printf("\t\t\t\t   1:词库增加        \t\t\t\t");
				printf("\t\t\t\t   2:词库修改        \t\t\t\t");
				printf("\t\t\t\t   3:单词删除        \t\t\t\t");
				printf("\t\t\t\t   4:词库补充        \t\t\t\t");
				printf("\t\t\t请自由选择数字[1-4]:   \t\t\t\t")；
					scanf("%d",&k);
				if(k==1)   
					addku();
				else if(k==2)
					correctku();
				else if(k==3)
					deleteku();
				else if(k==4)
					addword();
				else
					menu();
				break;
			case 4:
				exit();
				break;
		}
void colour()
{
	char con[5];  
	char color[20]="color ";  
	int i;

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
	gets(con);             //获取背景和文字颜色显示选项  
	strcat(color,con);     //合并color和选项  
	system(color);         //调用system（）函数实现显示颜色变化  
	printf("\n");
    printf("\t\t\t\t\t请输入1/0选择继续修改颜色or返回菜单\n");
	printf("\t\t\t\t\t\t\t");
	scanf("%d",&i);
	if(i==0)
	{
		menu();
	}
	if(i==1)
	{
		colour();
	}
}


void changecode()                         //定义函数：修改密码
{
	FILE *fp;
	printf("\t\t\t\t   请输入新密码：\t\t\t\t");     
	fgets(p.code);                        //输入新的密码
	fp=fopen("name.txt","w+");            //以读写模式打开
	fprintf(fp,"%s %s",p.account,p.code); 
	fclose(fp);
	printf("\t\t\t\t    修改成功!    \t\t\t\t");
	menu();
}

int sectionPrint(sql L[],int times)       //每页十组单词，用户通过点击按键选择页数
{
	int i,j,num;
	for (j=0;j<times/10;j++)              
	{
		system("cls");                    //清除页面内容
		printf("press i to choose the word you want to learn \n press x to exit \n press q to the previous page \n press any other keys to the next page\n");
		// 点击i选择要学习的单词 ，x代表退出 ，q代表前一页，任意其他的字母代表下一页
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

void review(sql L[],int j)	    //英译中答题
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
			printf("You are correct!\n please press enter to the next word\n");
			getchar();
			getchar();
		}
		else
		{
			printf("Um,you are wrong!\n please try again\n");
			L[i].wrong++;
			getchar();
			getchar();
			i = i - 1;
		}
	}
}

int sort(sql L[],sql M[], int i)       	//错题整理
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

void addword()                            //定义函数：词库补充
{
	FILE *p;
	char word[15],tag[5],trans_cn[20];
	char ch;
	p=fopen("wordku.txt","a+");           //word.txt为词库文件
	if(p==0)
	{
		printf("\t\t\t\t\t file error\n");
		exit(1);
	}
	printf("\t\t\t\t\t请输入您要添加的单词：");
	getchar();
    gets(word);
	printf("\t\t\t\t\t该词的词性：");
	gets(tag);
	printf("\t\t\t\t\t中文意思:");
    gets(trans_cn)
	printf("\t\t\t\t\t您是否还要继续？ Y/N :");
	scanf("%s",&ch);
	if(ch=='Y')
		{
			addword();
		}
	if(ch=='Y')
		{
			return;
		}
}
 
void deleteword()                       //定义函数：单词删除
{
	char word[20];
	int i=0;
	int m;
	printf("\t\t\t\t\t   请输入您要删除的单词：");
	getchar();
	gets(word);
	while(strcmp(wordku[i].word,word)!=0&&i<SIZE)
		i++;
	if(i<SIZE)
	{
		for( ;i<SIZE;i++)
			wordku[i]=ku[i+1];
		puts("\t\t\t\t\t 删除成功！");
	}
	else
	{
		puts("\t\t\t\t\t 没有找到对应的单词！\n");
	}
	printf("\t\t\t\t\t   请输入0返回菜单\n");
	printf("\t\t\t\t\t\t\t");
	scanf("%d",&m);
	if(m==0)
	{
		return;
	}
}

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



extern int amount = 100;

void init(sql L[],int i=1000)
{
	int j;
	for (j = 0; j < i; j++)
	{
		L[j].wrong = 0;
	}
}

void save(sql *L,char *name)               //存储新单词
{
	FILE *fp;
	errno_t err;
	strcat_s(name, 15, ".txt");
	err = fopen_s(&fp, name, "a");
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
		//fscanf_s(fp, "%d", (L + j)->wrong, sizeof(int));
	}
	fclose(fp);
}

void add(sql *L, int i,char *name)		//i为增加单词的数量
{
	int j;
	for (j =  0; j < i; j++, L++)
	{
		printf_s("Please input the word\n");
		gets_s(L->word, 15);
		printf_s("The tag:\n");
		gets_s(L->tag, 5);
		printf_s("The trans_cn:\n");
		gets_s(L->trans_cn, 100);
		save(L,name);
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

//主函数
void main()
{
	int 
	enroll();
	menu();
	return 0;

}