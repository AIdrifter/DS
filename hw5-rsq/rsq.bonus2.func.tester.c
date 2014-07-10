#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utility.h"
#include "rsq.h"

typedef struct rsq_t rsq;

void doubleSum(const void *a, const void *b, void *pRet){
    *(double*)pRet = *(double*)a + *(double*)b;
}
void shortSum(const void *a, const void *b, void *pRet){
    *(short*)pRet = *(short*)a + *(short*)b;
}

int main()
{
    rsq *p = NULL;
    size_t cap, tSize;
    int type;
    void *data = malloc(sizeof(double)*10);
    double double_zero = 0.0;
    short short_zero = 0;
    while(1){
        char cmd[10240] = {0};
        int ret;
        // void *data;
        if(p == NULL){
            printf("The rsq needs to be initialized.\n");
            printf("Init step 1. Type: d for double, others for short.\n");
            scanf("%s", cmd);
            type = (cmd[0] == 'd')?__DS__DOUBLE__:__DS__SHORT__;
            printf("Init step 2. Capacity: \n");
            scanf("%zu", &cap);
            p = rsqAlloc();
            if(p == NULL)
                ret = __DS__RSQ__OUT_OF_MEM__;
            else{
                if(type == __DS__DOUBLE__)
                    ret = rsqInit(p, sizeof(double), cap, doubleSum, NULL, &double_zero);
                else
                    ret = rsqInit(p, sizeof(short), cap, shortSum, NULL, &short_zero);
            }
                
            if(ret){
                printf("Not enough memory.\n");
                if(p != NULL)
                    rsqFree(p);
                p = NULL;
            }
            else{
                printf("Initialization done.\n");
            }

        }
        else{
            int choice = 0;
            tSize = rsqTypeSize(p);
            printf("size/capacity: %zu/%zu\n", rsqSize(p), rsqCap(p));
            printf("Valid operation: 1)push back, 2)pop back, 3)set element, 4)get range sum\n");
            printf("                 5)get element, 6)set new capacity, 7)empty, 8)free, 9)quit\n");
            while(choice <= 0 || choice > 9){
                scanf("%s", cmd);
                sscanf(cmd, "%d", &choice);
            }
            if(choice == 1){
                printf("input a %s value:", (type == __DS__DOUBLE__)?"double":"short"); 
                getData(type, data);
                ret = rsqPushBack(p, data);
                if(ret) 
                    printf("the rsq is full!\n");
            }
            else if(choice == 2){
                ret = rsqPopBack(p, data);
                if(ret == 0){
                    printf("The result is ");
                    printData(type, data);
                    printf(".\n");
                }
                else
                    printf("The rsq is empty.\n");
            }
            else if(choice == 3){
                size_t index;
                printf("input the index of container:");
                scanf("%zu", &index);
                printf("input a %s value:", (type == __DS__DOUBLE__)?"double":"short"); 
                getData(type, data);
                ret = rsqSet(p, index, data);
                if(ret)
                    printf("The index %zu is out of size.\n", index);
            }
            else if(choice == 4){
                size_t start, end;
                printf("input the start & end index of range:");
                scanf("%zu", &start);
                scanf("%zu", &end);
                ret = rsqRangeSum(p, start, end, data);
                if(ret == 0){
                    printf("The result is ");
                    printData(type, data);
                    printf(".\n");
                }
                else if(ret == __DS__RSQ__OUT_OF_SIZE__)
                    printf("The index %zu is out of size.\n", end);
                else
                    printf("start index %zu is larger than end index %zu.\n", start, end);
            }
            else if(choice == 5){
                size_t index;
                printf("input the index of container:");
                scanf("%zu", &index);
                ret = rsqGet(p, index, data);
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
                ret = rsqSetCap(p, index);
                if(ret)
                    printf("The new capacity %zu is out of memory.\n", index);
            }
            else if(choice == 7){
                if(rsqEmpty(p))
                    printf("The rsq is empty.\n");
                else
                    printf("The rsq is not empty.\n");
            }
            else if(choice == 8){
                rsqFree(p);
                p = NULL;
            }
            else if(choice == 9)
                break;
        }
    }
}

