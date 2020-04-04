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

typedef struct
{
	SElemtype* base;
	SElemtype* top;
	int stacksize;
}SqStack;

Status InitStack(SqStack& S)//³õÊ¼»¯
{
	S.base = (SElemtype*)malloc(MAXSIZE * sizeof(SElemtype));
	if (!S.base) return OVERFLOW;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

Status DestoryStack(SqStack& S)//Ïú»Ù
{
	if (S.base)
	{
		free(S.base);
		S.stacksize = 0;
		S.base = S.top = NULL;
	}
	return OK;
}

Status ClearStack(SqStack& S)//Çå¿Õ
{
	if (S.base) S.top = S.base;
	return OK;
}

Status Push(SqStack& S, SElemtype e)//½øÕ»
{
	if (S.top - S.base == MAXSIZE) return ERROR;//Õ»Âú
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack& S, SElemtype& e)//³öÕ»
{
	if (S.top == S.base) return ERROR;//¿ÕÕ»
	e = *--S.top;
	return OK;
}

Status Gethead(SqStack& S)//È¡Õ»¶¥ÔªËØ
{
	if (S.top == S.base)  return ERROR;
	return *(S.top - 1);
}

void ShowStack(SqStack& S)
{
	if (S.top == S.base) printf("Õ»Îª¿Õ£¡\n");
	else
	{
		SElemtype* p = S.top - 1;
		for (; p >= S.base; p--)
		{
			printf("%d ", *p);
		}
		printf("\n\n");
	}
}
