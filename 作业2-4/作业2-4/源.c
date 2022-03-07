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
void DestroyUBN(struct UBigNumber* pUBN)
{
    while (pUBN->pHead != NULL)
    {
        struct Node* p = pUBN->pHead;  //��ɾ�����
        pUBN->pHead = p->next;  //βָ��ǰ��
        free(p);  //�ͷŽ��
    }
}
