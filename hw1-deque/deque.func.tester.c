#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "deque.h"

typedef struct deque_t deque;

int main()
{
    deque *p = NULL;
    size_t cap, tSize;
    int type;
    void *data = malloc(sizeof(double)*10);
    while(1){
        char cmd[10240] = {0};
        int ret;
        if(p == NULL){
            printf("The deque needs to be initialized.\n");
            printf("Init step 1. Type: d for double, others for short.\n");
            scanf("%s", cmd);
            type = (cmd[0] == 'd')?__DS__DOUBLE__:__DS__SHORT__;
            printf("Init step 2. Capacity: \n");
            scanf("%zu", &cap);
            p = dequeAlloc();
            if(p == NULL)
                ret = __DS__DEQUE__OUT_OF_MEM__;
            else
                ret = dequeInit(p, (type == __DS__DOUBLE__)?sizeof(double):sizeof(short), cap);
            if(ret){
                printf("Not enough memory.\n");
                if(p != NULL)
                    dequeFree(p);
                p = NULL;
            }
            else{
                printf("Initialization done.\n");
            }

        }
        else{
            int choice = 0;
            tSize = dequeTypeSize(p);
            printf("size/capacity: %zu/%zu\n", dequeSize(p), dequeCap(p));
            printf("Valid operation: 1)push front, 2)push back, 3)pop front, 4)pop back\n");
            printf("                 5)front, 6)back, 7)empty, 8)free, 9)quit\n");
            while(choice <= 0 || choice > 9){
                scanf("%s", cmd);
                sscanf(cmd, "%d", &choice);
            }
            if(choice == 1 || choice == 2){
                printf("input a %s value:", (type == __DS__DOUBLE__)?"double":"short"); 
                getData(type, data);
                if(choice == 1)
                    ret = dequePushFront(p, data);
                else
                    ret = dequePushBack(p, data);
                if(ret) 
                    printf("the deque is full!\n");
            }
            else if(choice >= 3 && choice <= 6){
                if(choice == 3)
                    ret = dequePopFront(p, data);
                else if(choice == 4)
                    ret = dequePopBack(p, data);
                else if(choice == 5)
                    ret = dequeFront(p, data);
                else
                    ret = dequeBack(p, data);
                    
                if(ret == 0){
                    printf("The result is ");
                    printData(type, data);
                    printf(".\n");
                }
                else
                    printf("The deque is empty\n");
            }
            else if(choice == 7){
                if(dequeEmpty(p))
                    printf("The deque is empty\n");
                else
                    printf("The deque is not empty\n");
            }
            else if(choice == 8){
                dequeFree(p);
                p = NULL;
            }
            else if(choice == 9)
                break;
        }
    }
}

