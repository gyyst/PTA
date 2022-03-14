#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Int
{
	int a;
	struct Int* next;

};
typedef struct Int Int;

Int* createChain(Int* head) {
	head = (Int*)malloc(sizeof(Int));
	head->next = NULL;
	return head;

}
int findInt(Int*head,int m) {
	Int* tmp = head;
	int i;
	for (i = 0; i < m; i++) {
		tmp = tmp->next;
	}
	return tmp->a;
}

Int* insertChain(Int*head ,int a) {
	Int* tmp = head;

	while (tmp->next)
		tmp = tmp->next;
	tmp->a = a;
	tmp->next = (Int*)malloc(sizeof(Int));
	tmp = tmp->next;

	tmp->next = NULL;
	return head;
}
//left为当前分治段的开始下标；right为当前分治段的结束下标
//head为表的地址；*max为存储当前搜索到的最大值；*min为存储当前搜索到的最小值
void erfen(int left, int right, Int* head, int* max, int* min)
{
	int mid;
	if (right - left <= 1)
	{
		if (findInt(head, left) > findInt(head, right)) {
			if (findInt(head, left) > *max)*max = findInt(head, left);
			if (findInt(head, right) < *min)*min = findInt(head, right);
		}
		else {
			if (findInt(head, right) > *max)*max = findInt(head, right);
			if (findInt(head, left) < *min)*min = findInt(head, left);
		}
		return;
	}


mid = left + (right - left) / 2;	
erfen(left, mid, head, max,min);
erfen(mid + 1, right, head, max, min);
}
void display(Int*head) {
	Int* tmp = head;
	while (tmp->next!=NULL) {
		printf("%d ", tmp->a);
		tmp = tmp->next;
	}

}




int main() {
	Int* head=NULL;
	int a[10000];
	int n = 0,i;
	char c;
	int* max=(int*)malloc(sizeof(int)), * min = (int*)malloc(sizeof(int));
	head=createChain(head);
	/*while (scanf_s("%d", &a[n++]) != EOF) {
		insertChain(head, a[n - 1]);
	}*/
	while ((c = getchar()) != '\n')
				{
					if (c != ' ')
					{
						ungetc(c, stdin);//将c送回输入流
						scanf_s("%d", &a[n++]);
						head=insertChain(head, a[n - 1]);
					}
				}
	*max = *min = a[0];
	erfen(0, n - 1, head, max, min);
	printf("%d,%d", *min, *max);

	return 0;
}