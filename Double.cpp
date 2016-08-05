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
	printf("请输入双向链表元素，按Ctrl+Z结束：\n");
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
	}//用p找到插入位置
	if (!p || j>i - 1)
		return ERROR;
	q = (DulNode*)malloc(sizeof(DulNode));
	if (q == NULL)
		return ERROR;
	q->data = e;
	q->next = p->next;
	q->prior = p;//先搞定插入结点的前驱和后继
	p->next->prior = q;
	p->next = q;//再搞定后结点的前驱和前结点的后继
	return OK;
}

status DeleteDouble(DuLinklist &L, int i, int &e){
	DuLinklist p;
	p = L;
	int j = 0;
	while (p->next&&j < i ){
		p = p->next;
		j++;
	}//用P确定删除的位置
	if (!p->next || j>i){
		e = p->data;
		p->prior->next = p->next;
		free(p);
		return OK;
	}//若P为最后一个结点，则将null赋值给p前一个结点的后继
	e = p->data;
	p->prior->next = p->next;//将p的后结点作为p的前结点的后继
	p->next->prior = p->prior;//将p的前结点作为p的后结点的前驱
	free(p);//释放p结点
	return OK;
}

int main(){
	DuLinklist L1;
	CreatDouble(L1);
	printf("建立的双向链表为：\n");
	Print(L1);
	int i, e;
	printf("请输入插入元素的位置：\n");
	scanf("%d", &i);
	while (i<1 || i>DoubleLength(L1) + 1){
		printf("插入位置有误，重新输入！\n");
		scanf("%d", &i);
	}
	printf("请输入插入元素：\n");
	scanf("%d", &e);
	InsertDouble(L1, i, e);
	printf("插入后的双向链表为：\n");
	Print(L1);
	int i1, e1;
	printf("请输入删除元素的位置：\n");
	scanf("%d", &i1);
	while (i1<1 || i1>DoubleLength(L1) ){
		printf("删除位置有误，重新输入！\n");
		scanf("%d", &i);
	}
	DeleteDouble(L1, i1, e1);
	printf("删除后的双向链表为：\n");
	Print(L1);
	printf("被删除元素为：%d\n",e1);
	system("pause");
	return 0;
}