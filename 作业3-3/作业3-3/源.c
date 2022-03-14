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


//下列函数返回的大数占用的内存资源由函数调用者负责释放
//输入无符号大数
struct UBigNumber InputUBN();
//打印无符号大数
void PrintUBN(struct UBigNumber ubn);
//两个无符号大数相加
struct UBigNumber AddUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//销毁无符号大数，释放空间
void DestoryUBN(struct UBigNumber* pA);

//下列函数是无符号大数处理辅助函数
//建立表示无符号大数用带头结点双链表
void _InitUBN(struct UBigNumber* pUBN);
//无符号大数尾部添加一位数
void _AppendDigit(struct UBigNumber* pUBN, int digit);
//无符号大数前部添加一位数
void _AppendFrontDigit(struct UBigNumber* pUBN, int digit);
//无符号大数规范表示，去除高位多余0，至少含一位数字
void _Normalize(struct UBigNumber* pUBN);
//动态分配一个结点，返回结点指针
//分配失败时，简化程序，退出运行
struct Node* _NewNode();

//两个无符号大数相减
struct UBigNumber SubUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//两个无符号大数相乘
struct UBigNumber MultiplyUBN(struct UBigNumber* pA, struct UBigNumber* pB);

//无符号大数乘1位数
struct UBigNumber _MultiplyDigit(struct UBigNumber* pA, int digit);
//返回无符号大数中[start, end)数字子序列组成的无符号大数
//超出范围部分数字忽略，忽略后子序列不存在时返回0
struct UBigNumber _FetchSub(struct UBigNumber* pA, int start, int end);


int Compare(struct UBigNumber* A, struct UBigNumber* B);

int main()
{
    struct UBigNumber A, B, C, D,E, tmp;
    int compare;
    A = InputUBN();
    B = InputUBN();
    E = MultiplyUBN(&A, &B); //无符号大数相乘
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
    if (A.zhengfu == 0 && B.zhengfu == 0 || A.zhengfu > 0 && B.zhengfu > 0) {
        printf("\n");
        PrintUBN(E);
    }
    else {
        printf("\n");
        printf("-");
        PrintUBN(E);
    }


    DestoryUBN(&A);
    DestoryUBN(&B);
    DestoryUBN(&C);
    DestoryUBN(&D);

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
void DestoryUBN(struct UBigNumber* pUBN)
{
    while (pUBN->pHead != NULL)  //清空后应该只剩一个头结点
    {
        struct Node* p = pUBN->pHead;  //待删除结点
        pUBN->pHead = p->next;          //尾指针前移
        free(p);                       //释放结点
    }
}
struct UBigNumber MultiplyUBN(struct UBigNumber* pA, struct UBigNumber* pB)
{
    //递归终止条件
    if (pB->digitCount == 1)
        return _MultiplyDigit(pA, pB->pTail->digit);
    else if (pA->digitCount == 1)
        return _MultiplyDigit(pB, pA->pTail->digit);
    // 计算拆分长度
    int m = pA->digitCount;
    int n = pB->digitCount;

    int h = (m > n ? m : n) / 2;
    /* 拆分为a, b, c, d */
    struct UBigNumber a, b, c, d;

    a = _FetchSub(pA, 0, m - h); //高m-h位
    b = _FetchSub(pA, m - h, m); //低h位
    c = _FetchSub(pB, 0, n - h);  //高m-h位
    d = _FetchSub(pB, n - h, n);  //低h位
    // 计算z2, z0, z1, 此处的乘法使用递归
    struct UBigNumber z0, z1, z2;

    z2 = MultiplyUBN(&a, &c); //z2 = a * c;
    z0 = MultiplyUBN(&b, &d); //z0 = b * d;
    struct UBigNumber  t1, t2, t3, t4, t5, result;
    t1 = AddUBN(&a, &b);    //t1 = a+b
    t2 = AddUBN(&c, &d);     //t2 = c+d
    //销毁各不再使用的无符号大数
    DestoryUBN(&a);
    DestoryUBN(&b);
    DestoryUBN(&c);
    DestoryUBN(&d);
    t3 = MultiplyUBN(&t1, &t2); //t3 = (a+b)*(c+d)
    t4 = AddUBN(&z0, &z2);   //t4 = z0 + z2
    z1 = SubUBN(&t3, &t4);   //z1 = (a+b)*(c+d) - z2 - z0

    int i;
    for (i = 0; i < 2 * h; ++i) //z2 *= (10^(2*h))
        _AppendDigit(&z2, 0);
    for (i = 0; i < h; ++i) //z1 *= (10 ^ h)
        _AppendDigit(&z1, 0);
    t5 = AddUBN(&z2, &z1); //t5= z2*10^2h + z1 * 10^h
    result = AddUBN(&t5, &z0); //result = z2*10^2h + z1 * 10^h +z0

    DestoryUBN(&z0);
    DestoryUBN(&z1);
    DestoryUBN(&z2);
    DestoryUBN(&t1);
    DestoryUBN(&t2);
    DestoryUBN(&t3);
    DestoryUBN(&t4);
    DestoryUBN(&t5);
    return result;
}

//无符号大数乘1位数
struct UBigNumber _MultiplyDigit(struct UBigNumber* pA, int digit2)
{
    struct UBigNumber result;
    _InitUBN(&result);
    if (digit2 == 0)
    {
        _AppendDigit(&result, 0);
        return result;
    }

    int iCarry = 0; //进位，初始0
    struct Node* p1;
    p1 = pA->pTail; //从低位开始处理
    while (p1 != pA->pHead)   //第一大数剩余位处理
    {
        int digit = p1->digit * digit2 + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit(&result, digit);
        p1 = p1->prev;
    }
    if (iCarry != 0) //最后进位处理
        _AppendFrontDigit(&result, iCarry);
    return result;
}
//返回无符号大数中[start, end)数字子序列组成的无符号大数
//超出范围部分数字忽略，忽略后子序列不存在时返回0
struct UBigNumber _FetchSub(struct UBigNumber* pA, int start, int end)
{
    struct UBigNumber result;
    _InitUBN(&result);
    int i = 0;
    struct Node* p = pA->pHead->next;
    while (i < start && p != NULL)
    {
        p = p->next;
        ++i;
    }
    while (i < end && p != NULL)
    {
        _AppendDigit(&result, p->digit); //添加在尾部
        p = p->next;
        ++i;
    }
    _Normalize(&result);
    return result;
}