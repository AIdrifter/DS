#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	clock_t start, end;
	int i;
	double x=1.0000001;
	start=clock();
	for(i=0;i<100000000;i++)
		x=x*1.0000001;
	end=clock();
	return 0;
}
