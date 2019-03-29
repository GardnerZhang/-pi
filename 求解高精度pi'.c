#include<stdio.h.>
#include<stdlib.h>

#define maxsize 1000

typedef struct TagDlnode
{
	int data;
	struct TagDlnode *prev;
	struct TagDlnode *next;
}Dlnode, *Dlinklist;

void bigadd(Dlinklist *L2, Dlinklist *L);
void init(Dlinklist *L);
void calcu(Dlinklist *L);
void bigmut(Dlinklist *L_1, int n);
void bigdiv(Dlinklist *L2, int n);



void init(Dlinklist *L)
{
	(*L) = (Dlinklist)malloc(sizeof(Dlnode));
	(*L)->prev = NULL;
	(*L)->next = NULL;
	(*L)->data = 1;
}

void calcu(Dlinklist *L)
{
	Dlinklist L2;
	int n;
	init(&L2);
	for (n = 0; n < maxsize; n++)
	{
		Dlinklist L4;
		L4 = (Dlinklist)malloc(sizeof(Dlnode));
		L4->next = (*L)->next;
		(*L)->next = L4;
		L4->prev = (*L);
		L4->data = 0;
		*L = L4;
	}
	for (n = 1; n < maxsize; n++)
	{
		bigmut(&L2, n);
		bigdiv(&L2,(2 * n + 1));
		bigadd(&L2, L);
	}
}

void bigadd(Dlinklist *L2, Dlinklist *L)
{
	Dlinklist L3 = (Dlinklist)malloc(sizeof(Dlnode));
	L3 = (*L2);
	Dlinklist L4 = (Dlinklist)malloc(sizeof(Dlnode));
	L4 = *L;
	while (L3->prev != NULL)
	{
		L3 = L3->prev;
	}
	while (L4->prev != NULL)
	{
		L4 = L4->prev;
	}
	while (L3->next != NULL&&L4->next !=NULL)
	{
		L4->data = L4->data + L3->data;
		if(L4->data >= 10)
		{
			Dlinklist L5;
			L5 = (Dlinklist)malloc(sizeof(Dlnode));
			L5 = L4;
			while (L5->next != NULL)
			{
				L5->next->data = L5->next->data + L4->data;
				L4->data = L4->data % 10;
				L5 = L5->next;
			}
		}
		L4 = L4->next;
		L3 = L3->next;
	}
}

void bigmut(Dlinklist *L_1, int n)
{
	int m;
	Dlinklist L2_1;
	init(&L2_1);
	Dlinklist  L3 = (Dlinklist)malloc(sizeof(Dlnode));
	L3 = L2_1;
	Dlinklist L4 = (Dlinklist)malloc(sizeof(Dlnode));
    L4 = L3;
	Dlinklist L5 = (Dlinklist)malloc(sizeof(Dlnode));
	while (n > 0)
	{
		L5 = (*L_1);
		while (L5 != NULL)
		{
			m = (n % 10) * (L5)->data;
			if (m < 10)
			{
				(L2_1)->data = m;
			}
			else
			{
				(L2_1)->data = m % 10 + (L2_1)->data;;
				while ((L2_1)->prev != NULL)
				{
					(L2_1)->prev->data = (L2_1)->prev->data + m / 10 + (L2_1)->data / 10;
					(L2_1)->data = (L2_1)->data % 10;
					(L2_1) = (L2_1)->prev;
				}
				if ((L2_1)->prev == NULL)
				{
					Dlinklist L5;
					L5 = (Dlinklist)malloc(sizeof(Dlnode));
					L5->prev = (L2_1)->prev;
					(L2_1)->prev = L5;
					L5->next = (L2_1);
					L5->data = m / 10 + (L2_1)->data / 10;
				}
			}
			L5 = L5->prev;
			if (L2_1->prev == NULL)
			{
				Dlinklist L6;
				L6 = (Dlinklist)malloc(sizeof(Dlnode));
				L6->prev = L2_1->prev;;
				(L2_1)->prev = L6;
				L6->next = L2_1;
			}
			(L2_1) = (L2_1)->prev;
		}
		n = n / 10;
	}
	(*L_1) = (L2_1)->next;
}

void bigdiv(Dlinklist *L2, int n)
{
	int count = 0;
	int n_1 = n;
	int sum = 0;
	Dlinklist L1 = *L2;
	Dlinklist L4;
	L4 = (Dlinklist)malloc(sizeof(Dlnode));
	L4->next = NULL;
	L4->prev = NULL;
	while (L1 != NULL)
	{
		sum = sum * 10 + L1->data;
		L4->data = sum / n;
		sum = sum - (L4->data * n);
		L1 = L1->next;
		Dlinklist L5;
		L5 = (Dlinklist)malloc(sizeof(Dlnode));
		L5->next = L4->next;
		L5->prev = L4;
		L4->next = L5;
		L4 = L4->next;
	}
	while(L1 == NULL && count++ < maxsize)
	{
		sum = sum * 10 + 0;
		L4->data = sum / n;
		sum = sum - (L4->data * n);
		Dlinklist L6;
		L6 = (Dlinklist)malloc(sizeof(Dlnode));
		L6->next->prev = L6->next;
		L6->next = L4->next;
		L6->prev = L4;
		L4->next = L6;
		L4 = L4->next;
	}
	*L2 = L4->prev;
}

int main()
{
	int count = 0,m = 0;
	Dlinklist L;
	init(&L);
	scanf("%d", &count);
	calcu(&L);
	while (m < count)
	{
		if (m == 1)
		{
			printf(".");
		}
		printf("%d",L->data);
		m++;
		L = L->next;
	}
    return 0;
}