#include<stdio.h>
#include<stdlib.h>
#define SWAP(x,y,temp) ((temp)=(x),(x)=(y),(y)=(temp))
/* only works for n <= 11 */
int col[]={1,2,3,4,5,6,7,8,9,10,11};

void recursive(int depth, int n)
{
	int i, temp;
	if(depth == n)
	{
		for(i = 0; i < n; i++)
			printf("%d%c", col[i], i < n-1 ? ' ' : '\n');
		return;
	}
	for(i = depth; i < n; i++)
	{
		SWAP(col[i],col[depth],temp);
		recursive(depth+1, n);
		SWAP(col[i],col[depth],temp);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	recursive(0, n);
	return 0;
}
