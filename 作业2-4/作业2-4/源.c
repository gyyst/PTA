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

int Compare(struct UBigNumber* A, struct UBigNumber* B);

int main()
{
    struct UBigNumber A, B, C, D, tmp;
    int compare;
    A = InputUBN();
    B = InputUBN();
    compare = Compare(&A, &B);
    //printf("%d",compare);
    if (compare == 0)
    {
        C = AddUBN(&A, &B);
        D = SubUBN(&A, &B);
        printf("-");
        PrintUBN(C);
        printf("\n");
        printf("-");
        PrintUBN(D);
    }
    else if (compare == 1) {
        C = AddUBN(&A, &B);
        D = SubUBN(&B, &A);
        printf("-");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);
    }
    else if (compare == 2) {
        C = AddUBN(&A, &B);
        D = SubUBN(&A, &B);
        printf("-");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);

    }
    else if (compare == 3) {
        C = SubUBN(&A, &B);
        D = AddUBN(&A, &B);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);
    }
    else if (compare == 4) {
        C = SubUBN(&B, &A);
        D = AddUBN(&A, &B);
        printf("-");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);

    }
    else if (compare == 5) {
        C = SubUBN(&B, &A);
        D = AddUBN(&A, &B);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);
    }
    else if (compare == 6) {
        C = SubUBN(&A, &B);
        D = AddUBN(&A, &B);
        printf("-");
        PrintUBN(C);
        printf("\n");
        printf("-");
        PrintUBN(D);

    }
    else if (compare == 7) {
        C = SubUBN(&B, &A);
        D = AddUBN(&A, &B);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        printf("-");
        PrintUBN(D);

    }
    else if (compare == 8) {// -123 123
        C = SubUBN(&B, &A);
        D = AddUBN(&A, &B);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        printf("-");
        PrintUBN(D);

    }
    else if (compare == 9) {
        C = AddUBN(&A, &B);
        D = SubUBN(&A, &B);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);

    }
    else if (compare == 10) {
        C = AddUBN(&A, &B);
        D = SubUBN(&B, &A);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        printf("-");
        PrintUBN(D);
    }
    else if (compare == 11)//123 123
    {
        C = AddUBN(&A, &B);
        D = SubUBN(&B, &A);
        //printf(" ");
        PrintUBN(C);
        printf("\n");
        //printf(" ");
        PrintUBN(D);

    }



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
    result.zhengfu = 1;
    //跳过非数字字符
    do {
        ch = getchar();
        if (ch == '-') result.zhengfu = 0;
    } while (ch < '0' || ch > '9');
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

int Compare(struct UBigNumber* a, struct UBigNumber* b) {
    struct Node* p1 = a->pHead, * p2 = b->pHead;
    if (a->zhengfu == 0 && b->zhengfu == 0) {
        if (a->digitCount > b->digitCount)
            return 0;//a与b都是负数，a的位数比b多，b>a
        else if (a->digitCount < b->digitCount)
            return 1;//a与b都是负数，b的位数比b多，a>b
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 0;//b>a 例-115 -114
                else if (p1->digit < p2->digit)
                    return 1;//b<a -114 -115
                else
                {
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }return 2;//a b各个数字都相同


        }

    }
    else if (a->zhengfu == 1 && b->zhengfu == 0) {//a>b
        if (a->digitCount > b->digitCount)
            return 3;//a为正数，b为负数，a的绝对值大于b
        else if (a->digitCount < b->digitCount)
            return 4;//a为正数，b为负数，a的绝对值小于b       123 -1234
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 3;//a>b
                else if (p1->digit < p2->digit)
                    return 4;//a为正数，b为负数，a的绝对值小于b
                else
                {
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }return 5;
        }
    }
    else if (a->zhengfu == 0 && b->zhengfu == 1) {//a<b
        if (a->digitCount > b->digitCount)
            return 6;//a为负数，b为正数，a的绝对值大于b -123 12
        else if (a->digitCount < b->digitCount)
            return 7;//a为负数，b为正数，a的绝对值小于b -123 1234
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 6;//a>b
                else if (p1->digit < p2->digit)
                    return 7;//a为负数，b为正数，a的绝对值小于b
                else
                {
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }return 8;
        }



    }
    else if (a->zhengfu == 1 && b->zhengfu == 1) {
        if (a->digitCount > b->digitCount)
            return 9;//a>b>0
        else if (a->digitCount < b->digitCount)
            return 10;//b>a>0
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 9;//a>b>0
                else if (p1->digit < p2->digit)
                    return 10;//b>a>0
                else
                {
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }return 11;//a b各个数字都相同


        }
    }
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
