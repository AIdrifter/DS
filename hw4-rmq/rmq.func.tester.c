#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utility.h"
#include "rmq.h"

#define DOUBLE_NEG_INF (-1.0/0.0)
#define SHORT_NEG_INF SHRT_MIN

typedef struct rmq_t rmq;

int doubleGT(const void *a, const void *b)
{
	double da=*(double*)a;
	double db=*(double*)b;
	if(da==db)return 0;
	return (da>db)?1:-1;
}
int shortGT(const void *a, const void *b)
{
	short da=*(short*)a;
	short db=*(short*)b;
	if(da==db)return 0;
	return (da>db)?1:-1;
}

int main()
{
    rmq *p = NULL;
    size_t cap, tSize;
    int type;
    void *data = malloc(sizeof(double)*10);
    double double_neg_inf = DOUBLE_NEG_INF;
    short short_neg_inf = SHORT_NEG_INF;
    while(1){
        char cmd[10240] = {0};
        int ret;
        if(p == NULL){
            printf("The rmq needs to be initialized.\n");
            printf("Init step 1. Type: d for double, others for short.\n");
            scanf("%s", cmd);
            type = (cmd[0] == 'd')?__DS__DOUBLE__:__DS__SHORT__;
            printf("Init step 2. Capacity: \n");
            scanf("%zu", &cap);
            p = rmqAlloc();
            if(p == NULL)
                ret = __DS__RMQ__OUT_OF_MEM__;
            else{
                if(type == __DS__DOUBLE__)
                    ret = rmqInit(p, sizeof(double), cap, doubleGT, &double_neg_inf);
                else
                    ret = rmqInit(p, sizeof(short), cap, shortGT, &short_neg_inf);
            }
                
            if(ret != __DS__RMQ__NORMAL__){
                printf("Not enough memory.\n");
                if(p != NULL)
                    rmqFree(p);
                p = NULL;
            }
            else{
                printf("Initialization done.\n");
            }

        }
        else{
            int choice = 0;
            tSize = rmqTypeSize(p);
            printf("size/capacity: %zu/%zu\n", rmqSize(p), rmqCap(p));
            printf("Valid operation: 1)push back, 2)pop back, 3)set element, 4)get range max\n");
            printf("                 5)get element, 6)set new capacity, 7)empty, 8)free, 9)quit\n");
            while(choice <= 0 || choice > 9){
                scanf("%s", cmd);
                sscanf(cmd, "%d", &choice);
            }
            if(choice == 1){
                printf("input a %s value:", (type == __DS__DOUBLE__)?"double":"short"); 
                getData(type, data);
                ret = rmqPushBack(p, data);
                if(ret) 
                    printf("the rmq is full!\n");
            }
            else if(choice == 2){
                ret = rmqPopBack(p, data);
                if(ret == 0){
                    printf("The result is ");
                    printData(type, data);
                    printf(".\n");
                }
                else
                    printf("The rmq is empty.\n");
            }
            else if(choice == 3){
                size_t index;
                printf("input the index of container:");
                scanf("%zu", &index);
                printf("input a %s value:", (type == __DS__DOUBLE__)?"double":"short"); 
                getData(type, data);
                ret = rmqSet(p, index, data);
                if(ret)
                    printf("The index %zu is out of size.\n", index);
            }
            else if(choice == 4){
                size_t start, end;
                printf("input the start & end index of range:");
                scanf("%zu", &start);
                scanf("%zu", &end);
                ret = rmqRangeMax(p, start, end, data);
                if(ret == 0){
                    printf("The result is ");
                    printData(type, data);
                    printf(".\n");
                }
                else if(ret == __DS__RMQ__OUT_OF_SIZE__)
                    printf("The index %zu is out of size.\n", end);
                else
                    printf("start index %zu is larger than end index %zu.\n", start, end);
            }
            else if(choice == 5){
                size_t index;
                printf("input the index of container:");
                scanf("%zu", &index);
                ret = rmqGet(p, index, data);
                if(ret == 0){
                    printf("The result is ");
                    printData(type, data);
                    printf(".\n");
                }
                else
                    printf("The index %zu is out of size.\n", index);
            }
            else if(choice == 6){
                size_t index;
                printf("input new capacity of container:");
                scanf("%zu", &index);
                ret = rmqSetCap(p, index);
                if(ret)
                    printf("The new capacity %zu is out of memory.\n", index);
            }
            else if(choice == 7){
                if(rmqEmpty(p))
                    printf("The rmq is empty.\n");
                else
                    printf("The rmq is not empty.\n");
            }
            else if(choice == 8){
                rmqFree(p);
                p = NULL;
            }
            else if(choice == 9)
                break;
        }
    }
}

