#include<stdio.h>

int main()
{
	int a[]={1,2,3};
	int b[5]={1,2,3};
	int c[10]={};
	int d[10];
	int i;
	printf("size of a: %zu\n",sizeof(a));
	for(i=0;i<5;i++)
		printf("%d",b[i]);
	puts("");
	for(i=0;i<10;i++)
		printf("%d",c[i]);
	puts("");
	for(i=0;i<10;i++)
		printf("%d",d[i]);
	puts("");
	return 0;
}
