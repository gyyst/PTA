#include <stdio.h>
////��n�����д�x������z�����ɽ���y��
//void Hanoi(int n, char x, char y, char z);
//
//int main()
//{
//    int n;  //��������
//    scanf_s("%d", &n);
//    Hanoi(n, 'A', 'B', 'C');
//    return 0;
//}
////��n�����д�x������z�����ɽ���y��
//void Hanoi(int n, char x, char y, char z)
//{
//    if (n == 1) {
//        printf("%c->%c\n", x, z); //һ������ʱ��ֱ�Ӱᶯ
//    }
//    else {
//        Hanoi(n - 1, x, z, y);//��n-1�����д�x������y��������z��
//        printf("%c->%c\n", x, z);//ʣ��һ������ʱ��ֱ�Ӱᶯ
//        Hanoi(n - 1, y, x, z);//��n-1�����д�y������z��������x��
//    }
//}
int main() {
	int i=0,x, y=0, z=0,n;
	scanf_s("%d",&n);
	x = n;
	while (z != n) {
		if (i % 3 == 0) {
			x -= 1;
			y += 1;
			printf("A->C\n");
			if (x > z) {
				x -= 1;
				z += 1;
				printf("A->B\n");
			}
			i++;
		}
		if (i%3==1) {
			y -= 1;
			z += 1;
			printf("B->C\n");
			if (x > y) {
				x -= 1;
				y += 1;
				printf("A->B\n");
			}
			i++;
		}
		if (i % 3 == 2) {
			z -= 1;
			x += 1;
			printf("C->A\n");
			if (y > z) {
				y -= 1;
				z += 1;
				printf("B->C\n");
			}
			else
			{
				z -= 1;
				y += 1;
				printf("C->B\n");
			}
			i++;
		}
	
	}



	return 0;
}