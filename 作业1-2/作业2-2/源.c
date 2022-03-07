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


Int* createChain() {
	Int* pre = NULL, * tmp = NULL, * head = NULL, * end = NULL;
	int i;
	head = (Int*)malloc(sizeof(Int));
	end = (Int*)malloc(sizeof(Int));
	head->a = 0;
	head->next = end;

	end->a = 0;
	end->next = NULL;
	return head;
}

Int* insertChain(Int* head, int a) {
	Int* now = NULL, * pre = NULL, * tmp = NULL;
	now = head->next;
	pre = head;
	while (now->next != NULL)
	{
		if (now->a >= a) {
			tmp = (Int*)malloc(sizeof(Int));
			pre->next = tmp;
			tmp->a = a;
			tmp->next = now;
			break;
		}
		else {
			pre = now;
			now = now->next;
		}

	}
	if (now->next == NULL) {
		tmp = (Int*)malloc(sizeof(Int));
		pre->next = tmp;
		tmp->a = a;
		tmp->next = now;
	}


	return head;
}

void display(Int* head) {
	int i;
	Int* p = head->next, * pre = head;
	if (p->next != NULL) printf("%d", p->a);
	while (p->next != NULL) {
		p = p->next;
		if (p->a != 0) {
			printf("->%d", p->a);
		}

	}
	printf("\n");
}

	void connectchain(Int* head1, Int*  head2) {
	Int* tmp = head2->next, * pre = head2;
	while (tmp->next != NULL) {
		pre = tmp;
		tmp = tmp->next;
	}
	pre->next = head1->next;
}



int main()
{
	int a[1000];
	char c;
	int i = 0;
	int n = 0;
	int j = 0;
	Int* head1 = NULL;
	Int* head2 = NULL;
	Int* head3 = NULL;
	while ((c = getchar()) != '\n')
	{
		if (c != ' ')
		{
			ungetc(c, stdin);//将c送回输入流
			scanf_s("%d", &a[n++]);
		}
	}
	head1 = createChain();
	head2 = createChain();
	head3 = createChain();
	for (i = 0; i < n; i++) {
		if (a[i] > 0)
			head1 = insertChain(head1, a[i]);
		else if (a[i] < 0)
			head2 = insertChain(head2, a[i]);
		/*if (a[i] != 0)
			head3 = insertChain(head3,a[i]);*/
	}
	display(head1);
	display(head2);
	connectchain(head1, head2);
	display(head2);
	


	Free(head2);

	return 0;
}