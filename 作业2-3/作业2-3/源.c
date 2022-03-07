#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>


struct Node
{
    int digit;  //����
    struct Node* next, * prev;  //ǰ��ָ��
};

struct UBigNumber
{
    int digitCount;  //λ��
    int zhengfu;//������
    struct Node* pHead, * pTail;  //ָ��ͷ����β���
};


//��̬����1����㣬���ؽ��ָ��
//������ʧ��ʱ���򻯳����˳�����
struct Node* _NewNode();
//��ʾ�޷��Ŵ����ô�ͷ����˫������
void _InitUBN(struct UBigNumber* pUBN);
//�����޷��Ŵ���
struct UBigNumber InputUBN();
//�޷��Ŵ���β�����1λ����
void _AppendDigit(struct UBigNumber* pUBN, int digit);
//�޷��Ŵ����ײ����1λ����
void _AppendFrontDigit(struct UBigNumber* pUBN, int digit);
//�޷��Ŵ����Ĺ淶��ʾ��ȥ����λ�����0�����ٺ�1λ����
void _Normalize(struct UBigNumber* pUBN);
//�����޷��Ŵ������
struct UBigNumber AddUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//�޷����������
struct UBigNumber SubUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//��ӡ�޷��Ŵ���
void PrintUBN(struct UBigNumber ubn);
//�����޷��Ŵ������ͷſռ�
void DestroyUBN(struct UBigNumber* pA);


int main()
{
    struct UBigNumber A, B, C, D;
    A = InputUBN();
    B = InputUBN();
    C = AddUBN(&A, &B);
    D = SubUBN(&A, &B);

    PrintUBN(A);
    printf("+");
    PrintUBN(B);
    printf("=");
    PrintUBN(C);
    printf("\n");

    PrintUBN(A);
    printf("-");
    PrintUBN(B);
    printf("=");
    PrintUBN(D);

    DestroyUBN(&A);
    DestroyUBN(&B);
    DestroyUBN(&C);
    DestroyUBN(&D);

    return 0;
}


struct Node* _NewNode()
{
    struct Node* p;
    p = (struct Node*)malloc(sizeof(struct Node));
    if (p == NULL)  //����ʧ��
    {
        printf("Error:out of memory\n");
        exit(-1);  //�򻯳����˳�����
    }
    return p;

}


//������ʾ�޷��Ŵ����ô�ͷ����˫������
void _InitUBN(struct UBigNumber* pUBN)
{
    struct Node* p = _NewNode();
    pUBN->pHead = pUBN->pTail = p;  //����ͷ���
    p->next = p->prev = NULL;
    pUBN->digitCount = 0;
}


//�����޷��Ŵ���
struct UBigNumber InputUBN()
{
    struct UBigNumber result;
    _InitUBN(&result);

    char ch;
    //�����������ַ�
    do
        ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == ' ') result.zhengfu = 1;
        else if (ch == '-')result.zhengfu = 0;    
    }
    while (ch >= '0' && ch <= '9')
    {
        _AppendDigit(&result, ch - '0');  //���1λ
        ch = getchar();
    }
    _Normalize(&result);
    return result;
}


//�޷��Ŵ���β�����1λ����
void _AppendDigit(struct UBigNumber* pUBN, int digit)
{  //ԭ��ֻ��һ����λ0
    if (pUBN->digitCount == 1 && pUBN->pTail->digit == 0)
    {
        pUBN->pTail->digit = digit;  //λ�����䣬��ֵΪ0
        return;
    }
    struct Node* p = _NewNode();  //�����½��
    p->digit = digit;  //���ý����ֵ
    p->next = NULL;  //�޸�˫���������½����ӵ�β��
    p->prev = pUBN->pTail;
    pUBN->pTail->next = p;
    pUBN->pTail = p;
    ++pUBN->digitCount;  //�޸�λ��
}


//�޷��Ŵ����ײ����1λ����
void _AppendFrontDigit(struct UBigNumber* pUBN, int digit)
{
    struct Node* p = _NewNode();  //�����½��
    p->digit = digit;  //���ý����ֵ
    p->next = pUBN->pHead->next;  //�޸�˫���������½�������ͷ����
    if (p->next != NULL)
        p->next->prev = p;
    p->prev = pUBN->pHead;
    pUBN->pHead->next = p;
    if (pUBN->pTail == pUBN->pHead)
        pUBN->pTail = p;  //��ԭ��ֻ��ͷ���ʱ���½��Ҳ��β���
    ++pUBN->digitCount;  //�޸�λ��
}


//�޷��Ŵ����Ĺ淶��ʾ��ȥ����λ�����0�����ٺ�1λ����
void _Normalize(struct UBigNumber* pUBN)
{
    if (pUBN->digitCount == 0)
        _AppendDigit(pUBN, 0);
    while (pUBN->digitCount > 1 && pUBN->pHead->next->digit == 0)
    {   //ȥ����λ�����0
        struct Node* p;
        p = pUBN->pHead->next;  //��ɾ���Ľ��
        pUBN->pHead->next = p->next;  //����������ɾ��
        p->next->prev = pUBN->pHead;  //����������ɾ��
        free(p);  //�ͷŽ��
        --pUBN->digitCount;  //����λ��
    }
}


//�����޷��Ŵ������
struct UBigNumber AddUBN(struct UBigNumber* pA, struct UBigNumber* pB)
{
    struct UBigNumber result, * pResult = &result;
    _InitUBN(pResult);
    int iCarry = 0;  //��λ����ʼ0
    struct Node* p1, * p2;
    p1 = pA->pTail;  //�ӵ�λ��ʼ����
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)  //������ͬλ����
    {
        int digit = p1->digit + p2->digit + iCarry;
        iCarry = digit / 10;  //�½�λ
        digit %= 10;  //��ǰ���λ
        _AppendFrontDigit(pResult, digit);  //�����������λ
        p1 = p1->prev;  //׼������ǰһλ
        p2 = p2->prev;
    }
    while (p1 != pA->pHead)  //��һλ����ʣ��λ����
    {
        int digit = p1->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead)  //�ڶ�λ����ʣ��λ����
    {
        int digit = p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit(pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0)  //����λ����
        _AppendFrontDigit(pResult, iCarry);
    return result;
}


//�����޷��Ŵ������
struct UBigNumber SubUBN(struct UBigNumber* pA, struct UBigNumber* pB)
{
    struct UBigNumber result, * pResult = &result;
    _InitUBN(pResult);
    int iCarry = 0;  //��λ����ʼ0
    struct Node* p1, * p2;
    p1 = pA->pTail;  //�ӵ�λ��ʼ����
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)  //������ͬλ����
    {
        int digit = p1->digit - p2->digit - iCarry;
        iCarry = 0; //��ʼ��
        if (digit < 0)
        {
            digit += 10;
            iCarry = 1;  //ǰһλ��1
        }
        _AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while (p1 != pA->pHead)  //�����λ����
    {
        int digit = p1->digit - iCarry;
        iCarry = 0;
        if (digit < 0)
        {
            digit += 10;
            iCarry = 1;  //ǰһλ��1
        }
        _AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    _Normalize(pResult);
    return result;
}


//��ӡ�޷��Ŵ���
void PrintUBN(struct UBigNumber ubn)
{  //���ԣ�������1λ����
    assert(ubn.digitCount > 0 && ubn.pHead->next != NULL);
    struct Node* la = ubn.pHead->next;  //ͷ��������ݣ�����
    while (la)
    {
        printf("%d", la->digit);
        la = la->next;
    }
}


//�����޷��Ŵ������ͷſռ�
void DestroyUBN(struct UBigNumber* pUBN)
{
    while (pUBN->pHead != NULL)
    {
        struct Node* p = pUBN->pHead;  //��ɾ�����
        pUBN->pHead = p->next;  //βָ��ǰ��
        free(p);  //�ͷŽ��
    }
}



//#include<stdio.h>
//
//typedef struct Int
//{
//	struct Int* pre;
//	int a;
//	struct Int* next;
//};
//typedef struct Int Int;
//Int* creatChain() {
//	Int* head;
//	head = (Int*)malloc(sizeof(Int));
//	head->next = NULL;
//	head->pre = NULL;
//	return head;
//}
//void _AppendDigit(Int* head, int digit)
//{
//	Int* p = creatChain();  //�����½��
//	Int* tmp = head;
//	while (tmp->next != NULL) tmp=tmp->next;
//	p->a = digit;              
//	p->next = NULL;                //�޸�˫������ӳ�Ϊ��β�����
//	p->pre = tmp;
//
//}
//Int* insertNumber(Int* head) {
//	char ch;
//	//�����������ַ�
//	do
//		ch = getchar();
//	while (ch < '0' || ch > '9');
//	while (ch >= '0' && ch <= '9')
//	{
//		_AppendDigit(head, (int)ch); //���1λ
//		ch = getchar();
//	}
//}
//Int* jia(Int* head1, Int* head2) {
//	Int* tmp1 = head1, * tmp2 = head2;
//	Int* pre1 = NULL, * pre2 = NULL;
//	Int* p;
//	while (tmp1->next)tmp1 = tmp1->next;
//	while (tmp2->next)tmp2 = tmp2->next;
//	while (tmp1->pre) {
//		if (tmp2) {
//			tmp1->a += tmp2->a;
//			tmp1->pre += tmp1->a / 10;
//			tmp1->a = tmp1->a % 10;
//			tmp1 = tmp1->pre;
//			tmp2 = tmp2->pre;
//		}
//		else {
//			tmp1->pre += tmp1->a / 10;
//			tmp1->a = tmp1->a % 10;
//			tmp1 = tmp1->pre;
//		}
//		if(tmp1->pre && tmp2->pre && tmp1->a + tmp2->a >=10) {
//			p = (Int*)malloc(sizeof(Int));
//			tmp1->pre = p;
//			p->next = tmp1;
//			p->pre = NULL;
//			p->a = (tmp1->a+tmp2->a) / 10;
//			tmp1->a = tmp1->a % 10;
//			tmp1 = tmp1->pre;
//		}
//	}
//		return;
//	}
//void display(Int* head) {
//	int i;
//	Int* p = head, * pre = head;
//	while (p->next !=NULL) {
//		printf("%d", p->a);
//		p = p->next;
//
//	}
//
//}
//
//int main() {
//	Int* head1, * head2;
//	//head1 = creatChain();
//	//head2 = creatChain();
//	//head1 = insertNumber(head1);
//	//head2 = insertNumber(head2);
//	//head1 = jia(head1,head2);
//	//display(head1);
//	int a[10000];
//	int n = 0,i;
//	char ch;
//	do
//		ch = getchar();
//	while (ch < '0' || ch > '9');
//	while (ch >= '0' && ch <= '9')
//	{
//		a[n++] = (int)ch;
//		ch = getchar();
//	}
//	for (i = 0; i < n; i++) 
//		printf("%d",a[i]);
//	
//	return 0;
//}
// 
// 
// 
// 
// 
// 
// 
// 
// 
//void getnumber(int*a ) {
//    char ch;
//    do
//        ch = getchar();
//    while (ch < '0' || ch > '9');
//    while (ch >= '0' && ch <= '9')
//    {
//        *a++ = (int)ch;
//        ch = getchar();
//    }
//
//	}
//
//int main() {
//	int a[1000], b[1000], c[1000];
//    int i=0, j=0, k=0;
//    getnumber(a);
//    getnumber(b);
//
//
//	return 0;
//}