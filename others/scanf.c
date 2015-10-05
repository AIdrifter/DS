#include <stdio.h>
#include <stdlib.h>

int main(){
	int a=0,b=0,ret=-1;
	/* example
	scanf("%d%d", &a, &b);
	return 2,if a b success
	return 1,if a success
	return 1,if b success
	return 0,if no one success
	return EOF,if something wrong or end of file */
	while(ret=scanf("%d %d",&a,&b)){
		printf("you input %d %d and return %d\n",a,b,ret);

	}

}
