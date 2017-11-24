
/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>

#include "CWM_ERROR_CODE.h"
#include "CWM_PACKAGE_QUEUE.h"

/*Header[0]:count*/
#define PACKAGE_HEADER_SIZE    2

static int GetEmptySize(pPackageQueue_t ptr)
{
    int EmptySize = 0;
    int front = ptr->front;
    int rear = ptr->rear;

    if((front == rear) ||(front > rear))
        EmptySize = ptr->Length -(front - rear);
    else
        EmptySize = rear -front;

    return EmptySize;
}

static int GetUseSize(pPackageQueue_t ptr)
{
    int size = 0;
    int front = ptr->front;
    int rear = ptr->rear;

    if((front == rear) ||(front > rear))
        size = front - rear;
    else
        size = ptr->Length -(rear - front);
    
    return size;
}

static int PACKAGE_QUEUE_INIT(pPackageQueue_t mem, void *memory, int size)
{
    mem->front = 0;
    mem->rear = 0;
    mem->Length = size;
    mem->mem = memory;
    if(NULL == mem->mem)
        return CWM_ERROR_MEMORY_ALLOC_FAIL;
    
    memset(mem->mem, 0x00, size);
    return CWM_NON;
}

/*data format: byte[0] = count, byte[1~1+count] = data*/
static int PACKAGE_QUEUE_SET(pPackageQueue_t mem, uint8_t *data, uint16_t size)
{
    int i;
    if(GetEmptySize(mem) <= (size + PACKAGE_HEADER_SIZE))
        return CWM_ERROR_QUEUE_FULL;

    mem->mem[mem->front] = (uint8_t)size;
    mem->front = (mem->front+1)%mem->Length;
    
    mem->mem[mem->front] = (uint8_t)(size >> 8);
    mem->front = (mem->front+1)%mem->Length;
        
    for(i =0;i<size;i++ )
    {
        mem->mem[mem->front] = data[i];
        mem->front = (mem->front+1)%mem->Length;
    }
    return CWM_NON;
}

/*data format: byte[0] = count, byte[1~1+count] = data*/
static int PACKAGE_QUEUE_GET(pPackageQueue_t mem, uint8_t *data)
{
    int i;
    int size;
    int count;
    uint16_t temp = 0;
    size = GetUseSize(mem);
    if(0 == size)
        return CWM_NON;
    
    /*Read first byte to get this package size*/
    temp = (uint16_t)mem->mem[mem->rear];
    mem->rear = (mem->rear+1)%mem->Length;
    temp |= ((uint16_t)mem->mem[mem->rear]) << 8;
    mem->rear = (mem->rear+1)%mem->Length;
    
    count = (int)temp;
    for(i =0;i<count;i++ )
    {
        data[i] = mem->mem[mem->rear];
        mem->rear = (mem->rear+1)%mem->Length;
    }
    return count;
}

static int PACKAGE_QUEUE_GET_COUNT(pPackageQueue_t mem)
{
    return GetUseSize(mem);
}

static PackageQueueClass_t FP_PACKAGE_QUEUE = {
    .init = PACKAGE_QUEUE_INIT,
    .set= PACKAGE_QUEUE_SET,
    .get= PACKAGE_QUEUE_GET,
    .getCount= PACKAGE_QUEUE_GET_COUNT,
};

pPackageQueueClass_t CWM_GET_PACKAGE_QUEUE_HANDLE(void)
{
    return &FP_PACKAGE_QUEUE;
}

/**********End Special Queue*/
/******************************************/
