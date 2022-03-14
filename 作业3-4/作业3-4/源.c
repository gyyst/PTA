#include <stdio.h>
////将n个盘中从x柱搬至z柱，可借助y柱
//void Hanoi(int n, char x, char y, char z);
//
//int main()
//{
//    int n;  //盘子数量
//    scanf_s("%d", &n);
//    Hanoi(n, 'A', 'B', 'C');
//    return 0;
//}
////将n个盘中从x柱搬至z柱，可借助y柱
//void Hanoi(int n, char x, char y, char z)
//{
//    if (n == 1) {
//        printf("%c->%c\n", x, z); //一个盘子时可直接搬动
//    }
//    else {
//        Hanoi(n - 1, x, z, y);//将n-1个盘中从x柱搬至y柱，借助z柱
//        printf("%c->%c\n", x, z);//剩余一个盘子时可直接搬动
//        Hanoi(n - 1, y, x, z);//将n-1个盘中从y柱搬至z柱，借助x柱
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