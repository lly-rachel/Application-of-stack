#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE  100
#define TURE  1
#define FALSE 0
#define OK    1
#define ERROR 0
#define OVERFLOW -2

typedef int SElemtype;
typedef int Status;

typedef struct StackNode
{
	SElemtype data;
	struct StackNode* next;
}StackNode, * LinkStack;

Status InitStack(LinkStack& S)//��ʼ��
{
	S = NULL;
	return OK;
}

Status DestoryStack(LinkStack& S)//����
{
	LinkStack p = S;
	while (p)
	{
		S = S->next;
		free(p);
		p = S;
	}
	S = NULL;
	return OK;
}

Status ClearStack(LinkStack& S)//���
{
	while (S)
	{
		S->data = NULL;
		S = S->next;
	}
	if (S == NULL)
		return OK;
}

Status Push(LinkStack& S, SElemtype e)//��ջ
{
	LinkStack p = (LinkStack)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return OK;
}

Status Pop(LinkStack& S, SElemtype &e)//��ջ
{
	if (S == NULL)  return ERROR;//��ջ
	LinkStack p = S;
	e = S->data;
	S = S->next;
	free(p);
	return OK;
}

Status Gethead(LinkStack& S)//ȡջ��Ԫ��
{
	if (S==NULL)  return ERROR;
	return S->data;
}

void ShowStack(LinkStack& S)
{
	LinkStack p = S;
	if (S == NULL) printf("ջΪ�գ�\n");
	for (; p; p = p->next)
	{
		printf("%d ", p->data);
	}
	printf("\n\n");
}


/*�������躯��*/
int Calculate(int a, char theta, int b)
{
	switch (theta)
	{
	case '+':return(a + b); 
	case '-':return(a - b); 
	case '*':return(a * b); 
	case '/':return(a / b); 
	}
}

char Compare(char a, char b)
{
	int i, j;
	char pre[][7] = {
	{ '>','>','<','<','<','>','>' },
	{ '>','>','<','<','<','>','>' },
	{ '>','>','>','>','<','>','>' },
	{ '>','>','>','>','<','>','>' },
	{ '<','<','<','<','<','=','0' },
	{ '>','>','>','>','0','>','>' },
	{ '<','<','<','<','<','0','=' } };
	switch (a)
	{
	case'+':i = 0; break;
	case'-':i = 1; break;
	case'*':i = 2; break;
	case'/':i = 3; break;
	case'(':i = 4; break;
	case')':i = 5; break;
	case'#':i = 6; break;
	}
	switch (b)
	{
	case'+':j = 0; break;
	case'-':j = 1; break;
	case'*':j = 2; break;
	case'/':j = 3; break;
	case'(':j = 4; break;
	case')':j = 5; break;
	case'#':j = 6; break;
	}
	return pre[i][j];
}

int GetNum(char c)
{
	return c - '0';
}

int ExpEvaluation()//ʵ��
{
	LinkStack ovs, optr;
	InitStack(ovs);
	InitStack(optr);
	Push(optr, (int)'#');
	printf("����ָ�'#'��������");
	char c = getchar();
	int num = 0, a, b, op, t;
	while (c != '#' || (char)Gethead(optr) != '#')
	{
		ShowStack(ovs);
		while (c >= '0' && c <= '9')//��������
		{
			num = num * 10 + GetNum(c);
			c = getchar();
		}
		if (num)
		{
			Push(ovs, num);//���ֽ�ջ
			num = 0;
		}
		else//�ַ�
		{
			switch (Compare(c, (char)Gethead(optr)))
			{
			case'>':Push(optr, (int)c);
					c = getchar();
					break;
			case'=':
			case'<':Pop(optr, op);
					Pop(ovs, a);
					Pop(ovs, b);
					t=Calculate(b, (char)op, a);
					Push(ovs, t);
					break;
			}
		}
	}
	t = Gethead(ovs);
	return t;
}

void main()
{
	printf("����ǣ�%d\n", ExpEvaluation());
}