#ifndef header
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>
#include<stack>
using namespace std;
#endif // !header

#define LIMIT 100
#define FIRST 1
#define SECOND 2
#define THIRD 3

//运算栈元素的定义
typedef struct TElemType {
	int data;//此处将原来的char类型的data改为了int类型的data，在后续函数用到的比较中int通过ASCII同样可以完成工作，代价是空间多了几个字节
	int op;
}TElemType;

//二叉树的定义
typedef struct BiTNode {
	TElemType tdata;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

//运算链栈的定义
typedef struct LSNode {
	TElemType tdata;
	struct LSNode* next;
}LSNode,*LStack;

//初始化运算链栈
bool InitStack_LS(LStack& S) {
	S = (LStack)malloc(sizeof(LSNode));
	if (NULL == S) return false;
	S->next = NULL;
	return true;
}

void DestroyStack(LStack& S);

//判断运算链栈空
bool StackEmpty_LS(LStack S) {
	if (NULL == S->next) return true;
	return false;
}

//运算链栈入栈
bool Push_LS(LStack& S, TElemType e) {
	LSNode* t;
	t = (LSNode*)malloc(sizeof(LSNode)); //分配节点空间
	if (NULL == t) return false;
	t->tdata = e;
	t->next = S; S = t;
	return true;
}

//运算链栈出栈
bool Pop_LS(LStack& S, TElemType& e) {
	LSNode* t;
	if (nullptr == S) return false;
	t = S;
	e = S->tdata;
	S = S->next;
	free(t);
	return true;
}

//获得运算链栈栈顶元素
bool GetTop_LS(LStack S, TElemType& e) {
	if (NULL == S) return false;
	e = S->tdata;
	return true;
}

//二叉树栈元素的定义
typedef struct {
	struct BiTNode *bit;
	int tag;
}SElemType;

//二叉树链栈的定义
typedef struct TSNode {
	SElemType stree;
	struct TSNode* next;
}TSNode, * TStack;

//初始化二叉树栈
bool InitStack_TS(TStack& T) {
	T = (TStack)malloc(sizeof(TSNode));
	if (T == NULL) return false;
	T->next = NULL;
	return true;
}

//二叉树栈入栈
bool Push_TS(TStack& T, SElemType s) {
	TSNode* t;
	t = (TStack)malloc(sizeof(TSNode));
	if (t == NULL) return false;
	t->stree = s;
	t->next = T;
	T = t;
	return true;
}

//二叉树栈出栈
bool Pop_TS(TStack& T, SElemType &s) {
	TSNode* t;
	if (T == NULL) return false;
	t = T;
	s = T->stree;
	T = T->next;
	free(t);
	return true;
}

bool StackEmpty_TS(TStack T) {
	if (T->next == NULL) return true;
	return false;
}

//赋予运算优先权
void GiveOp(TElemType* e,int n) {
	TElemType* p=e;
	while (n > 0) {
		if (p->data == '+'||p->data == '-') {
			p->op = 1;
		}
		else if (p->data == '*' ||p->data == '/' || p->data == '^') {
			p->op = 2;
		}
		else if (p->data == '(' || p->data == ')') {
			p->op = 3;
		}
		else p->op = 0;
		p++; n--;
	}
}

void InputSelem(SElemType* p, char* str) {
	printf("树结点赋值测试：");//单纯赋了个data，即字符
	while (*str) {
		p->bit->tdata.data = *str;
		str++;
		p++;
	}
	putchar('\n');
}

//根据后缀表达式构造二叉树
TStack	Postfix_to_BiTree(char* str) {
	TStack Ts;
	InitStack_TS(Ts);
	SElemType *tree;
	//SElemType tree[LIMIT];
	//InputSelem(tree, str);
	//SElemType* p=tree;
	//tree = NULL;
	//tree->bit->tdata.data = *str;
	tree = (SElemType*)malloc(sizeof(SElemType));
	SElemType* ptr1, * ptr2;
	ptr1 = (SElemType*)malloc(sizeof(SElemType));
	ptr2 = (SElemType*)malloc(sizeof(SElemType));
	if (NULL == Ts) return NULL;
	while (*str) {
		if ((*str <= '9' && *str >= '0') || (*str <= 'z' && *str >= 'a'))
		{//操作数
			tree->bit->tdata.data = *str;
			tree->bit->lchild = NULL;
			tree->bit->rchild = NULL;
			Push_TS(Ts, *tree);
		}
		else {//操作符
			tree->bit->tdata.data = *str;
			Pop_TS(Ts, *ptr1);
			tree->bit->rchild = ptr1->bit;
			Pop_TS(Ts, *ptr2);
			tree->bit->lchild = ptr2->bit;
			Push_TS(Ts, *tree);
		}
		str++;
	}
	free(ptr1); free(ptr2);
	free(tree);
	return Ts;
}

//访问函数
void visit(TElemType tdata) {
	putchar(tdata.data);
}

//非递归后续遍历二叉树
void PostOrder(BiTree T, void (*visit)(TElemType)) {
	if (T == NULL) return;

	printf("后序的输出测试：");

	TStack S;
	InitStack_TS(S);
	SElemType now;
	now.tag = FIRST;
	Push_TS(S, now);
	while (!StackEmpty_TS(S)) {
		Pop_TS(S, now);
		if (now.tag == FIRST) {
			now.tag = SECOND;
			Push_TS(S, now);
			if (now.bit->lchild) {
				now.bit = now.bit->lchild;
				now.tag = FIRST;
				Push_TS(S, now);
			}
		}
		else if (now.tag == SECOND) {
			now.tag = THIRD;
			Push_TS(S, now);
			if (now.bit->rchild) {
				now.bit = now.bit->rchild;
				now.tag = FIRST;
			}
		}
		else visit(now.bit->tdata);
	}
}

void TestTree(TStack S) {
	SElemType test;
	Pop_TS(S, test);

}


//测试输入是否正确
void testinputvalid(TElemType* ptr, int num) {
	printf("输入正确性测试：");
	for (int i = 0; i < num; i++, ptr++) {
		putchar(ptr->data);
	}
	printf("\n");
}

//测试输入优先级
void testpriority(TElemType* ptr, int num) {
	printf("输入优先级测试：");
	for (int i = 0; i < num; i++, ptr++) {
		printf("%d", ptr->op);
	}
	printf("\n");
}

//测试输入字符数
void testinputnum(int num) {
	printf("输入字符数测试：");
	printf("%d\n", num);
}

void Infix_to_Postfix(TElemType* p, LStack &S, int num) {
	bool flag = false;
	printf("测试输出结果是：");
	for (int i = 0; i < num; i++, p++) {
		TElemType top;
		if (p->data <= '9' && p->data >= '0') printf("%c", p->data);
		else {
			switch (p->data)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				if (flag == false) {
					S->tdata = *p;
					flag = true;
				}
				else {
					GetTop_LS(S, top);
					if (top.op < p->op) Push_LS(S, (*p));
					else {
						do
						{
							Pop_LS(S, top);
							if(top.data!='(')
							printf("%c", top.data);
							if(!StackEmpty_LS(S))		GetTop_LS(S, top);
						} while (!StackEmpty_LS(S) && top.op <= p->op);
						Push_LS(S, *p);
					}
				}
				break;
			case '(':
				if (flag == false) {
					flag = true; p->op = -1; S->tdata = *p;
				}
				else {
					p->op = -1;
					Push_LS(S, *p);
				}
				break;
			case ')':
				while (GetTop_LS(S, top) && top.data != '(') {
					Pop_LS(S, top);
					printf("%c", top.data);
				}
				Pop_LS(S, top);
				break;
			default:
				break;
			}
		}
		if (i == num - 1) {
			while (!StackEmpty_LS(S)) {
				Pop_LS(S, top);			// printf("fucking doubling\n");
				printf("%c", top.data);
			}
		}
	}
}

//中缀转后缀ver1.2
void Infix_to_Postfix2(TElemType* p, LStack& S, int num, char *str) {
	//bool flag = false;//原本使用flag判定第一个字符是否是操作符，由于原来采用头栈结点带有效值的
	//入栈方式，第一个是操作符的话入栈就要将已初始化好的头结点赋值
	S->tdata.op = -1;
	TElemType top;
	printf("测试输出结果是：");
	for (int i = 0; i < num; i++, p++) {
		if (p->data <= '9' && p->data >= '0') {
			printf("%c", p->data);
			*str++ = p->data;
		}
		//	Push(S, *p);
		else {
			switch (p->data)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				putchar('#');
				*str++ = '#';
				GetTop_LS(S, top);
				if (top.op < p->op) Push_LS(S, (*p));
				else {
					do
					{
				//		GetTop_LS(S, top);
						if (top.data == '(') break;
						Pop_LS(S, top);
						*str++ = top.data;
						//if (top.data != '(')
						printf("%c", top.data);
						//if (!StackEmpty_LS(S))	
						GetTop_LS(S, top);
					} while (!StackEmpty_LS(S) && top.op <= p->op);
					Push_LS(S, *p);
				}
				
				break;
			case '(':
				//if (flag == false) { S->tdata.op = -1; flag = true; }
					p->op = -1;
					Push_LS(S, *p);
				break;
			case ')':
				while (GetTop_LS(S, top) && top.data != '(') {
					Pop_LS(S, top);
					*str++ = top.data;
					printf("%c", top.data);
				}
				Pop_LS(S, top);
				break;
			default:
				break;
			}
		}
		if (i == num - 1) {
			while (!StackEmpty_LS(S)) {
				Pop_LS(S, top);			// printf("fucking doubling\n");
				*str++ = top.data;
				printf("%c", top.data);
			}
		}
	}
	*str = '\0';
	putchar('\n');
}

int inputdata(TElemType* ptr, int limit) {//输入数据
	//虽然是传递地址值，但通过地址改变对应的数据也能使实参发生改变
	char c;
	int num = 0;
	while (num < limit)
	{
		c = getchar();
		if (c == '\0' || c == '\n') break;
		ptr->data = c;
		num++; ptr++;
	}
	return num;
}

void fileinput(TElemType *p, int &num) {//从文件输入
	FILE* fp;
	char ch;
	if ((fp = fopen("testdata.txt", "r")) != NULL) {
		ch = fgetc(fp);
		while (ch != '\n' && ch != '\0' && ch != EOF) {
			p->data = ch;
			ch = fgetc(fp);
			num++;
			p++;
		}
	}
}

void teststrinput(char* str) {
	printf("字符串测试结果：");
	while (*str) {
		printf("%c", *str++);
	}
	printf("\n");
}

void printPostfix() {//中缀转后缀
	LStack S;
	InitStack_LS(S);
	TElemType soc[LIMIT];
	TElemType* p = soc;
	printf("请输入表达式：\n");

	int num = 0;

	fileinput(p, num);//通过文件输入检查
	//num = inputdata(p, LIMIT);//通过控制台输入检查
	char str[LIMIT];

	testinputvalid(p, num);//测试输入的数据

	GiveOp(soc, num);//根据输入赋予优先级

	//printf("%d\n", num);//测试输入字符数

	testpriority(p, num);//测试优先级

	Infix_to_Postfix2(p, S, num,str);//中缀转后缀，此时往str中写入转换后的数据

	//TStack T;

	//T = Postfix_to_BiTree(str);

	//SElemType s;

	//Pop_TS(T, s);

	//PostOrder(&s.bit,visit);

	//printf("树构造测试结果：");

	putchar(s.bit->tdata.data);

	//笔记：若在二叉树栈元素定义时定义的是结点类型好像可以至少得到最后一个元素的data
	//但是其他结点好像构造出现问题，取data也发生异常

	//putchar(s.bit->lchild->tdata.data);

	//putchar(s.bit.rchild->tdata.data);

	//putchar('\n');

	teststrinput(str);
}

void calpostfix() {

}


int main() {
	
	printPostfix();
	int ch='q';//char类型赋给int类型，实际上赋予的是ASCII码
	putchar(ch);//似乎putchar只能输出char类型，但实际上可以传递ASCII码输出对应字符
	
	printf("%c", ch);
	return 0;
}