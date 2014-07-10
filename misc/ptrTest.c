#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i=0;
	char w,x[10],y,z[10];
	int *p;
	for(i=0;i<10;i++)
		x[i]=z[i]=(char)1;
	p=(int*)&y;
	*p=0x09080706;
	for(i=0;i<10;i++)
		printf("x[%d]=%d z[%d]=%d\n",i,(int)x[i],i,(int)z[i]);
	return 0;
}
