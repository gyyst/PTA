#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>


struct Node
{
    int digit;  //数字
    struct Node* next, * prev;  //前后指针
};

struct UBigNumber
{
    int digitCount;  //位数
    int zhengfu;//正负号
    struct Node* pHead, * pTail;  //指向头结点和尾结点
};


//动态分配1个结点，返回结点指针
//当分配失败时，简化程序，退出运行
struct Node* _NewNode();
//表示无符号大数用带头结点的双向链表
void _InitUBN(struct UBigNumber* pUBN);
//输入无符号大数
struct UBigNumber InputUBN();
//无符号大数尾部添加1位数字
void _AppendDigit(struct UBigNumber* pUBN, int digit);
//无符号大数首部添加1位数字
void _AppendFrontDigit(struct UBigNumber* pUBN, int digit);
//无符号大数的规范表示，去除高位多余的0，至少含1位数字
void _Normalize(struct UBigNumber* pUBN);
//两个无符号大数相加
struct UBigNumber AddUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//无符号整数相减
struct UBigNumber SubUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//打印无符号大数
void PrintUBN(struct UBigNumber ubn);
//销毁无符号大数，释放空间
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
    if (p == NULL)  //分配失败
    {
        printf("Error:out of memory\n");
        exit(-1);  //简化程序，退出运行
    }
    return p;

}


//建立表示无符号大数用带头结点的双向链表
void _InitUBN(struct UBigNumber* pUBN)
{
    struct Node* p = _NewNode();
    pUBN->pHead = pUBN->pTail = p;  //建立头结点
    p->next = p->prev = NULL;
    pUBN->digitCount = 0;
}


//输入无符号大数
struct UBigNumber InputUBN()
{
    struct UBigNumber result;
    _InitUBN(&result);

    char ch;
    //跳过非数字字符
    do
        ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == ' ') result.zhengfu = 1;
        else if (ch == '-')result.zhengfu = 0;    
    }
    while (ch >= '0' && ch <= '9')
    {
        _AppendDigit(&result, ch - '0');  //添加1位
        ch = getchar();
    }
    _Normalize(&result);
    return result;
}


//无符号大数尾部添加1位数字
void _AppendDigit(struct UBigNumber* pUBN, int digit)
{  //原来只有一个高位0
    if (pUBN->digitCount == 1 && pUBN->pTail->digit == 0)
    {
        pUBN->pTail->digit = digit;  //位数不变，数值为0
        return;
    }
    struct Node* p = _NewNode();  //申请新结点
    p->digit = digit;  //设置结点数值
    p->next = NULL;  //修改双向链表，将新结点添加到尾部
    p->prev = pUBN->pTail;
    pUBN->pTail->next = p;
    pUBN->pTail = p;
    ++pUBN->digitCount;  //修改位数
}


//无符号大数首部添加1位数字
void _AppendFrontDigit(struct UBigNumber* pUBN, int digit)
{
    struct Node* p = _NewNode();  //申请新结点
    p->digit = digit;  //设置结点数值
    p->next = pUBN->pHead->next;  //修改双向链表，将新结点添加在头结点后
    if (p->next != NULL)
        p->next->prev = p;
    p->prev = pUBN->pHead;
    pUBN->pHead->next = p;
    if (pUBN->pTail == pUBN->pHead)
        pUBN->pTail = p;  //当原来只有头结点时，新结点也是尾结点
    ++pUBN->digitCount;  //修改位数
}


//无符号大数的规范表示，去除高位多余的0，至少含1位数字
void _Normalize(struct UBigNumber* pUBN)
{
    if (pUBN->digitCount == 0)
        _AppendDigit(pUBN, 0);
    while (pUBN->digitCount > 1 && pUBN->pHead->next->digit == 0)
    {   //去除高位多余的0
        struct Node* p;
        p = pUBN->pHead->next;  //待删除的结点
        pUBN->pHead->next = p->next;  //正向链表中删除
        p->next->prev = pUBN->pHead;  //反向链表中删除
        free(p);  //释放结点
        --pUBN->digitCount;  //调整位数
    }
}


//两个无符号大数相加
struct UBigNumber AddUBN(struct UBigNumber* pA, struct UBigNumber* pB)
{
    struct UBigNumber result, * pResult = &result;
    _InitUBN(pResult);
    int iCarry = 0;  //进位，初始0
    struct Node* p1, * p2;
    p1 = pA->pTail;  //从低位开始处理
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)  //两数相同位处理
    {
        int digit = p1->digit + p2->digit + iCarry;
        iCarry = digit / 10;  //新进位
        digit %= 10;  //当前结果位
        _AppendFrontDigit(pResult, digit);  //添加至结果最高位
        p1 = p1->prev;  //准备处理前一位
        p2 = p2->prev;
    }
    while (p1 != pA->pHead)  //第一位大数剩余位处理
    {
        int digit = p1->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead)  //第二位大数剩余位处理
    {
        int digit = p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit(pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0)  //最后进位处理
        _AppendFrontDigit(pResult, iCarry);
    return result;
}


//两个无符号大数相减
struct UBigNumber SubUBN(struct UBigNumber* pA, struct UBigNumber* pB)
{
    struct UBigNumber result, * pResult = &result;
    _InitUBN(pResult);
    int iCarry = 0;  //退位，初始0
    struct Node* p1, * p2;
    p1 = pA->pTail;  //从低位开始处理
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)  //两数相同位处理
    {
        int digit = p1->digit - p2->digit - iCarry;
        iCarry = 0; //初始化
        if (digit < 0)
        {
            digit += 10;
            iCarry = 1;  //前一位退1
        }
        _AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while (p1 != pA->pHead)  //最后退位处理
    {
        int digit = p1->digit - iCarry;
        iCarry = 0;
        if (digit < 0)
        {
            digit += 10;
            iCarry = 1;  //前一位退1
        }
        _AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    _Normalize(pResult);
    return result;
}


//打印无符号大数
void PrintUBN(struct UBigNumber ubn)
{  //断言：至少有1位数字
    assert(ubn.digitCount > 0 && ubn.pHead->next != NULL);
    struct Node* la = ubn.pHead->next;  //头结点无数据，跳过
    while (la)
    {
        printf("%d", la->digit);
        la = la->next;
    }
}


//销毁无符号大数，释放空间
void DestroyUBN(struct UBigNumber* pUBN)
{
    while (pUBN->pHead != NULL)
    {
        struct Node* p = pUBN->pHead;  //待删除结点
        pUBN->pHead = p->next;  //尾指针前移
        free(p);  //释放结点
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
//	Int* p = creatChain();  //申请新结点
//	Int* tmp = head;
//	while (tmp->next != NULL) tmp=tmp->next;
//	p->a = digit;              
//	p->next = NULL;                //修改双链表，添加成为新尾部结点
//	p->pre = tmp;
//
//}
//Int* insertNumber(Int* head) {
//	char ch;
//	//跳过非数字字符
//	do
//		ch = getchar();
//	while (ch < '0' || ch > '9');
//	while (ch >= '0' && ch <= '9')
//	{
//		_AppendDigit(head, (int)ch); //添加1位
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