#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef struct DULNODE{
	struct DULNODE *prior;
	int data;
	struct DULNODE *next;
}DulNode,*DuLinklist;

void Print(DuLinklist L){
	DuLinklist p;
	p = L->next;
	while (p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void CreatDouble(DuLinklist &L){
	DuLinklist p,nail;
	L = (DulNode*)malloc(sizeof(DulNode));
	L->next = NULL;
	nail = L;
	p = (DulNode*)malloc(sizeof(DulNode));
	printf("������˫������Ԫ�أ���Ctrl+Z������\n");
	while ((scanf("%d", &(p->data))) != EOF){
		p->next = NULL;
		p->prior = nail;
		nail->next = p;
		nail = p;
		p = (DulNode*)malloc(sizeof(DulNode));
	}
}

int DoubleLength(DuLinklist L){
	DuLinklist p;
	p = L;
	int j = 0;
	while (p->next){
		p = p->next;
		j++;
	}
	return j;
}

status InsertDouble(DuLinklist &L, int i, int e){
	int j = 0;
	DuLinklist p, q;
	p = L;
	while (p&&j < i - 1){
		p = p->next;
		j++;
	}//��p�ҵ�����λ��
	if (!p || j>i - 1)
		return ERROR;
	q = (DulNode*)malloc(sizeof(DulNode));
	if (q == NULL)
		return ERROR;
	q->data = e;
	q->next = p->next;
	q->prior = p;//�ȸ㶨�������ǰ���ͺ��
	p->next->prior = q;
	p->next = q;//�ٸ㶨�����ǰ����ǰ���ĺ��
	return OK;
}

status DeleteDouble(DuLinklist &L, int i, int &e){
	DuLinklist p;
	p = L;
	int j = 0;
	while (p->next&&j < i ){
		p = p->next;
		j++;
	}//��Pȷ��ɾ����λ��
	if (!p->next || j>i){
		e = p->data;
		p->prior->next = p->next;
		free(p);
		return OK;
	}//��PΪ���һ����㣬��null��ֵ��pǰһ�����ĺ��
	e = p->data;
	p->prior->next = p->next;//��p�ĺ�����Ϊp��ǰ���ĺ��
	p->next->prior = p->prior;//��p��ǰ�����Ϊp�ĺ����ǰ��
	free(p);//�ͷ�p���
	return OK;
}

int main(){
	DuLinklist L1;
	CreatDouble(L1);
	printf("������˫������Ϊ��\n");
	Print(L1);
	int i, e;
	printf("���������Ԫ�ص�λ�ã�\n");
	scanf("%d", &i);
	while (i<1 || i>DoubleLength(L1) + 1){
		printf("����λ�������������룡\n");
		scanf("%d", &i);
	}
	printf("���������Ԫ�أ�\n");
	scanf("%d", &e);
	InsertDouble(L1, i, e);
	printf("������˫������Ϊ��\n");
	Print(L1);
	int i1, e1;
	printf("������ɾ��Ԫ�ص�λ�ã�\n");
	scanf("%d", &i1);
	while (i1<1 || i1>DoubleLength(L1) ){
		printf("ɾ��λ�������������룡\n");
		scanf("%d", &i);
	}
	DeleteDouble(L1, i1, e1);
	printf("ɾ�����˫������Ϊ��\n");
	Print(L1);
	printf("��ɾ��Ԫ��Ϊ��%d\n",e1);
	system("pause");
	return 0;
}