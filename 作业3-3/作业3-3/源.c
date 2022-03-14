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


//���к������صĴ���ռ�õ��ڴ���Դ�ɺ��������߸����ͷ�
//�����޷��Ŵ���
struct UBigNumber InputUBN();
//��ӡ�޷��Ŵ���
void PrintUBN(struct UBigNumber ubn);
//�����޷��Ŵ������
struct UBigNumber AddUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//�����޷��Ŵ������ͷſռ�
void DestoryUBN(struct UBigNumber* pA);

//���к������޷��Ŵ�������������
//������ʾ�޷��Ŵ����ô�ͷ���˫����
void _InitUBN(struct UBigNumber* pUBN);
//�޷��Ŵ���β�����һλ��
void _AppendDigit(struct UBigNumber* pUBN, int digit);
//�޷��Ŵ���ǰ�����һλ��
void _AppendFrontDigit(struct UBigNumber* pUBN, int digit);
//�޷��Ŵ����淶��ʾ��ȥ����λ����0�����ٺ�һλ����
void _Normalize(struct UBigNumber* pUBN);
//��̬����һ����㣬���ؽ��ָ��
//����ʧ��ʱ���򻯳����˳�����
struct Node* _NewNode();

//�����޷��Ŵ������
struct UBigNumber SubUBN(struct UBigNumber* pA, struct UBigNumber* pB);
//�����޷��Ŵ������
struct UBigNumber MultiplyUBN(struct UBigNumber* pA, struct UBigNumber* pB);

//�޷��Ŵ�����1λ��
struct UBigNumber _MultiplyDigit(struct UBigNumber* pA, int digit);
//�����޷��Ŵ�����[start, end)������������ɵ��޷��Ŵ���
//������Χ�������ֺ��ԣ����Ժ������в�����ʱ����0
struct UBigNumber _FetchSub(struct UBigNumber* pA, int start, int end);


int Compare(struct UBigNumber* A, struct UBigNumber* B);

int main()
{
    struct UBigNumber A, B, C, D,E, tmp;
    int compare;
    A = InputUBN();
    B = InputUBN();
    E = MultiplyUBN(&A, &B); //�޷��Ŵ������
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
    result.zhengfu = 1;
    //�����������ַ�
    do {
        ch = getchar();
        if (ch == '-') result.zhengfu = 0;
    } while (ch < '0' || ch > '9');
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

int Compare(struct UBigNumber* a, struct UBigNumber* b) {
    struct Node* p1 = a->pHead, * p2 = b->pHead;
    if (a->zhengfu == 0 && b->zhengfu == 0) {
        if (a->digitCount > b->digitCount)
            return 0;//a��b���Ǹ�����a��λ����b�࣬b>a
        else if (a->digitCount < b->digitCount)
            return 1;//a��b���Ǹ�����b��λ����b�࣬a>b
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 0;//b>a ��-115 -114
                else if (p1->digit < p2->digit)
                    return 1;//b<a -114 -115
                else
                {
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }return 2;//a b�������ֶ���ͬ


        }

    }
    else if (a->zhengfu == 1 && b->zhengfu == 0) {//a>b
        if (a->digitCount > b->digitCount)
            return 3;//aΪ������bΪ������a�ľ���ֵ����b
        else if (a->digitCount < b->digitCount)
            return 4;//aΪ������bΪ������a�ľ���ֵС��b       123 -1234
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 3;//a>b
                else if (p1->digit < p2->digit)
                    return 4;//aΪ������bΪ������a�ľ���ֵС��b
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
            return 6;//aΪ������bΪ������a�ľ���ֵ����b -123 12
        else if (a->digitCount < b->digitCount)
            return 7;//aΪ������bΪ������a�ľ���ֵС��b -123 1234
        else if (a->digitCount == b->digitCount) {
            while (p1 && p2) {
                if (p1->digit > p2->digit)
                    return 6;//a>b
                else if (p1->digit < p2->digit)
                    return 7;//aΪ������bΪ������a�ľ���ֵС��b
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
            }return 11;//a b�������ֶ���ͬ


        }
    }
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
void DestoryUBN(struct UBigNumber* pUBN)
{
    while (pUBN->pHead != NULL)  //��պ�Ӧ��ֻʣһ��ͷ���
    {
        struct Node* p = pUBN->pHead;  //��ɾ�����
        pUBN->pHead = p->next;          //βָ��ǰ��
        free(p);                       //�ͷŽ��
    }
}
struct UBigNumber MultiplyUBN(struct UBigNumber* pA, struct UBigNumber* pB)
{
    //�ݹ���ֹ����
    if (pB->digitCount == 1)
        return _MultiplyDigit(pA, pB->pTail->digit);
    else if (pA->digitCount == 1)
        return _MultiplyDigit(pB, pA->pTail->digit);
    // �����ֳ���
    int m = pA->digitCount;
    int n = pB->digitCount;

    int h = (m > n ? m : n) / 2;
    /* ���Ϊa, b, c, d */
    struct UBigNumber a, b, c, d;

    a = _FetchSub(pA, 0, m - h); //��m-hλ
    b = _FetchSub(pA, m - h, m); //��hλ
    c = _FetchSub(pB, 0, n - h);  //��m-hλ
    d = _FetchSub(pB, n - h, n);  //��hλ
    // ����z2, z0, z1, �˴��ĳ˷�ʹ�õݹ�
    struct UBigNumber z0, z1, z2;

    z2 = MultiplyUBN(&a, &c); //z2 = a * c;
    z0 = MultiplyUBN(&b, &d); //z0 = b * d;
    struct UBigNumber  t1, t2, t3, t4, t5, result;
    t1 = AddUBN(&a, &b);    //t1 = a+b
    t2 = AddUBN(&c, &d);     //t2 = c+d
    //���ٸ�����ʹ�õ��޷��Ŵ���
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

//�޷��Ŵ�����1λ��
struct UBigNumber _MultiplyDigit(struct UBigNumber* pA, int digit2)
{
    struct UBigNumber result;
    _InitUBN(&result);
    if (digit2 == 0)
    {
        _AppendDigit(&result, 0);
        return result;
    }

    int iCarry = 0; //��λ����ʼ0
    struct Node* p1;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit * digit2 + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit(&result, digit);
        p1 = p1->prev;
    }
    if (iCarry != 0) //����λ����
        _AppendFrontDigit(&result, iCarry);
    return result;
}
//�����޷��Ŵ�����[start, end)������������ɵ��޷��Ŵ���
//������Χ�������ֺ��ԣ����Ժ������в�����ʱ����0
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
        _AppendDigit(&result, p->digit); //�����β��
        p = p->next;
        ++i;
    }
    _Normalize(&result);
    return result;
}