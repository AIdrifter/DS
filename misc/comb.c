#include<stdio.h>

int C(int n, int m)
{
	if(n<m||m<0)return 0;
	if(n==m||m==0)return 1;
	return C(n-1,m-1)+C(n-1,m);
}

int main()
{
	int n, m;
	scanf("%d%d",&n,&m);
	printf("C(%d,%d)=%d\n",n,m,C(n,m));
	return 0;
}
