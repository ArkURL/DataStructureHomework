#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<vector>


int non_main() {
	int a, b, sum;
	
	system("cls");
	printf("请输入a、b的值：\n");
	scanf_s("%d %d", &a, &b);
	printf("结果是%.0f\n", pow(a,b));
	return 0;
}