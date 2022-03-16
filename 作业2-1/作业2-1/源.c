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

//Int* createChain1() {
//	Int* pre = NULL, * tmp = NULL, * head = NULL, * end = NULL;
//	int i;
//	head = (Int*)malloc(sizeof(Int));
//	head->next = NULL;
//	
//	return head;
//}

Int* insertChain(Int* head,int a,int m) {
	Int* tmp = head,*pre=NULL;
	int i;
	for (i = 1; i <= m; i++) {
		pre = tmp;
		tmp = tmp->next;
	}
	pre->a = a;
	return head;

}
Int* createChain(Int* head, int m) {
	Int* pre = NULL, * tmp = NULL, * end = NULL;
	int i;
	tmp = (Int*)malloc(sizeof(Int));
	head = tmp;
	for (i = 1; i <= m; i++) {
		pre = tmp;
		tmp->a = i;
		tmp->next = (Int*)malloc(sizeof(Int));
		tmp = tmp->next;
		if (i == m)
			pre->next = head;
	}

	return head;
}

void display(Int* head, int m) {
	int i;
	Int* p = head;
	for (i =1; i <= m; i++) {
		printf("%4d", p->a);
		p = p->next;
	}
    printf("\n");
}
// void selectMeber1(Int* head, int n) {
// 	Int* p = NULL, * tmp = head, * pre = NULL;
// 	int count;
// 	while (tmp->next != tmp) {
// 		for (count = 1; count < n; count++) {
// 			pre = tmp;
// 			tmp = tmp->next;
// 		}
// 		pre->next = tmp->next;
// 		printf("%4d", tmp->a);
// 		tmp = tmp->next;
// 	}
// 	printf("%4d", tmp->a);
// }
void selectMeber(Int* head,Int* head2, int n) {
	Int* p = NULL, * tmp = head, * pre =tmp;
	int count;
    int num;
	int countmember=1;
	while (tmp->next != tmp) {
		for (count = 1; count < n; count++) {
			pre = tmp;
			tmp = tmp->next;
		}
		pre->next = tmp->next;
        num=tmp->a;
		//free(tmp);
		//printf("%4d", tmp->a);
		head2 = insertChain(head2, num,countmember);
		countmember++;
		tmp = tmp->next;
	}
	//printf("%4d", tmp->a);
	head2 = insertChain(head2, tmp->a, countmember);
	//head2 = xunhuan(head2);
}

int main() {
	int m, n ;
	Int* head = NULL, * head2 = NULL,* temp = NULL;
	scanf("%d", &m);
	head = createChain(head, m);
	head2 = createChain(head2,m);
	while (scanf("%d", &n) != EOF) {
		selectMeber(head,head2, n);
		head = createChain(head, m);
		temp = head;
		head = head2;
		head2 = temp;

	}

		display(head, m);
	return 0;
}
