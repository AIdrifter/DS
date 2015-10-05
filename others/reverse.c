#include <stdio.h>
#include <stdlib.h>

void strrev(char *p)
{
    char *q = p;
    while(q && *q) ++q;
    for(--q; p < q; ++p, --q){
      *p = *p ^ *q,
      *q = *p ^ *q,
      *p = *p ^ *q;
       puts(p);
    }
}

int main(){
	char *str=malloc(30);
	memcpy(str,"1 2 3 4 5 6 7 8 9",18);
	strrev(str);
	puts(str);
}
