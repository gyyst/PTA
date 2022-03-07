#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Int
{
	int a;
	struct Int* next;
};
typedef struct Int Int;

void Free(Int* head) {
	Int* p = head, * prev = head;
	while (p) {
		p = p->next;
		free(prev);
		prev = p;
	}
	free(prev);
}


Int* createChain(Int* head,int m) {
	Int* pre = NULL, * tmp = NULL,  * end = NULL;
	int i;
	tmp = (Int*)malloc(sizeof(Int));
	head = tmp;
	for (i = 1; i <= m; i++) {
		pre = tmp;
		tmp->a = i;
		tmp->next= (Int*)malloc(sizeof(Int));
		tmp = tmp->next;
		if (i == m)
			pre->next = head;
	}
	
	return head;
}
void display(Int* head,int m) {
	int i;
	Int* p = head;
	for (i = 1; i <= m; i++) {
		printf("%d ",p->a);
		p = p->next;
	}

}

void selectMeber(Int* head,int n) {
	Int* p = NULL, * tmp = head, * pre = NULL;
	int count;
	while (tmp->next != tmp) {
		for (count = 1; count < n; count++) {
			pre = tmp;
			tmp = tmp->next;
		}
		pre->next = tmp->next;
		printf("%4d",tmp->a);
		tmp = tmp->next;
	}
	printf("%4d",tmp->a);
}

int main() {
	int m, n;
	Int* head = NULL;

	scanf_s("%d %d",&m,&n);
	head = createChain(head,m);
	selectMeber(head, n);
	free(head);
	return 0;
}