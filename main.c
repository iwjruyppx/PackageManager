#include "main.h"

#include "CWM_ERROR_CODE.h"
#include "CWM_PACKAGE_QUEUE.h"

pPackageQueueClass_t qHandle;
PackageQueue_t queue1;
PackageQueue_t queue2;

static uint8_t queue1Mem[100];
static uint8_t queue2Mem[100];

int timestamp = 0;

void queueInit(void)
{
    qHandle = CWM_GET_PACKAGE_QUEUE_HANDLE();
    qHandle->init(&queue1, queue1Mem, 100);
    qHandle->init(&queue2, queue2Mem, 100);
}
typedef struct{
    int timestamp;
}Time_t, pTime_t;

Time_t time1;
Time_t time2;

static void queue1DataSet(void)
{
    time1.timestamp = timestamp*1;
    qHandle->set(&queue1, (uint8_t *)&time1, sizeof(Time_t));
}

static void queue2DataSet(void)
{
    time2.timestamp = timestamp*10;
    qHandle->set(&queue2, (uint8_t *)&time2, sizeof(Time_t));
}

static void queue1DataGet(void)
{
    Time_t info;
    while(qHandle->getCount(&queue1))
    {
        if(qHandle->get(&queue1, (uint8_t *)&info))
        {
            printf("Queue1:%d\n", info.timestamp);
        }
    }
}
static void queue2DataGet(void)
{
    Time_t info;
    while(qHandle->getCount(&queue2))
    {
        if(qHandle->get(&queue2, (uint8_t *)&info))
        {
            printf("Queue2:%d\n", info.timestamp);
        }
    }
}


int main( void )
{
    queueInit();
    while(1)
    {   
        queue1DataSet();
        queue2DataSet();
        queue2DataSet();
        
        queue1DataGet();
        printf("Queue2Get_In\n");
        queue2DataGet();
        printf("Queue2Get_Out\n");
        printf("Queue2Get_In1\n");
        queue2DataGet();
        printf("Queue2Get_Out1\n");
        
        timestamp++;
    }
}

