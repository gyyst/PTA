#include<stdio.h>

int nx[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
int a[50][50];
int b[50][50] = {0};
int count=1;
void dfs(int a[50][50],int m ,int n) {
	int nowx;
	int nowy;
	int flag=a[m][n];
	b[m][n] = count;
	
	for (int i = 0; i <= 3; i++) {
		nowx = m + nx[i][0];
		nowy = n + nx[i][1];
		
		if (a[nowx][nowy]==flag && b[nowx][nowy]==0) {
			b[nowx][nowy] = count;
			dfs(a, nowx, nowy);
			
		}
	}
	
}










int main() {
	
	int m, n,i,j;
	scanf_s("%d %d",&m,&n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf_s("%d",&a[i][j]);
		}
	
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (b[i][j] == 0) {
				dfs(a, i, j);
				count++;
			}
			
		}

	}



	printf("%d",count-1);





	return 0;
}