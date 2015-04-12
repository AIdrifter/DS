#include<stdio.h>
#include"utility.h"

int getData(int type,void *data)
{
	switch(type)
	{
		case __DS__INT__:
			return scanf("%d",(int*)data);
		case __DS__SHORT__:
			return scanf("%hd",(short*)data);
		case __DS__FLOAT__:
			return scanf("%f",(float*)data);
		case __DS__DOUBLE__:
			return scanf("%lf",(double*)data);
		case __DS__LONG__:
			return scanf("%ld",(long*)data);
		case __DS__LONGLONG__:
			return scanf("%lld",(long long*)data);
		case __DS__CHAR__:
			return scanf("%c",(char*)data);
		case __DS__STRING__:
			return scanf("%s",(char*)data);
	}
	return 0;
}

void printData(int type, void *data)
{
	switch(type)
	{
		case __DS__INT__:
			printf("%d",*(int*)data); return;
		case __DS__SHORT__:
			printf("%hd",*(short*)data); return;
		case __DS__FLOAT__:
			printf("%f",*(float*)data); return;
		case __DS__DOUBLE__:
			printf("%f",*(double*)data); return;
		case __DS__LONG__:
			printf("%ld",*(long*)data); return;
		case __DS__LONGLONG__:
			printf("%lld",*(long long*)data); return;
		case __DS__CHAR__:
			printf("%c",*(char*)data); return;
		case __DS__STRING__:
			printf("%s",(char*)data); return;
	}
}

void sPrintData(char *str, int type, void *data)
{
	switch(type)
	{
		case __DS__INT__:
			sprintf(str,"%d",*(int*)data); return;
		case __DS__SHORT__:
			sprintf(str,"%hd",*(short*)data); return;
		case __DS__FLOAT__:
			sprintf(str,"%f",*(float*)data); return;
		case __DS__DOUBLE__:
			sprintf(str,"%f",*(double*)data); return;
		case __DS__LONG__:
			sprintf(str,"%ld",*(long*)data); return;
		case __DS__LONGLONG__:
			sprintf(str,"%lld",*(long long*)data); return;
		case __DS__CHAR__:
			sprintf(str,"%c",*(char*)data); return;
		case __DS__STRING__:
			sprintf(str,"%s",(char*)data); return;
	}
}
