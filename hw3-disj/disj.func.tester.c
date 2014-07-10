#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"disj.h"

typedef struct disj_t disj;

int main()
{
	disj *p;
	p = NULL;
	size_t cap;
	int choice , ret;
	char cmd[1024000];
	long data1 , data2;
    for(;;)
    {
        if( p == NULL )
        {
            puts("The dis-joint set needs to be initialized.");
            printf("How many elements do you have?\n");
            scanf("%zu",&cap);
			p = disjAlloc( );
			if( p != NULL )
			{
				if( disjInit( p, cap) == __DS__DISJ__NORMAL__ )
				{
					printf( "Disjoint sets have been initialized\n" );
				}
				else{
					free(p);
					p=NULL;
				}
			}
        }
        else
        {
			puts( "Valid operations: 1)union 2)find 3)same set 4)set size 5)free 6)quit" );
            for( choice = 0 ; choice <= 0 || choice > 6 ; sscanf( cmd , "%d"  ,&choice ) )
                scanf("%s",cmd);
            if( choice == 1 )
            {
                printf( "Input a value: ");
				scanf("%ld" , &data1 );
				printf( "Input another value: ");
				scanf( "%ld" , &data2 );
                ret = disjUnion( p , data1 , data2 );
                if( ret == __DS__DISJ__SAMESET__ )
					printf("%ld and %ld are already in the same set\n" , data1 , data2 );
            }
            else if( choice == 2 )
            {
                printf( "Input a value: ");
				scanf("%ld" , &data1 );
                printf( "%ld is in the set whose representative is %ld\n" , data1 , disjFind( p , data1 ));
            }
            else if( choice == 3 )
            {
                printf( "Input a value: ");
				scanf("%ld" , &data1 );
				printf( "Input another value: ");
				scanf( "%ld" , &data2 );
                ret = disjSameSet( p , data1 , data2 );
				if( ret == __DS__DISJ__DIFFSET__ )
					printf("%ld and %ld are in different sets\n" , data1 , data2 );
				else
					printf("%ld and %ld are in the same set\n" , data1 , data2 );
            }
            else if( choice == 4 )
            {
                printf( "Input a value: ");
				scanf("%ld" , &data1 );
				printf( "The size of the set containing %ld is %zu\n" , data1 , disjSetSize( p , data1 ) );
            }
            else if( choice == 5)
			{
				disjFree( p );
				p=NULL;
			}
			else
                break;
        }
    }
    return 0;
}
