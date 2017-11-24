#ifndef __CWM_PACKAGE_QUEUE_H__
#define __CWM_PACKAGE_QUEUE_H__

typedef struct
{
    volatile int front;
    volatile int rear;
    int Length;     //total queue leng
    int ItemSize;   // queue data size
    uint8_t *mem;
}PackageQueue_t, *pPackageQueue_t;


/*
    int (*init)(pPackageQueue_t, void*, int);
        input[0]: pPackageQueue_t 
        input[1]: memory point
        input[2]: memory alloc size
        return: Error message.

    int (*set)(pPackageQueue_t, uint8_t *, uint16_t);
        input[0]: pPackageQueue_t 
        input[1]: data 
        input[2]: size
        return: Error message.

    int (*get)(pPackageQueue_t, uint8_t *);
        input[0]: pPackageQueue_t 
        output[0]: data 
        return[>=0]: Count.
        return[<0]: Error info.

    int (*getCount)(pPackageQueue_t);
        input[0]: pPackageQueue_t 
        return: Count.        
*/

typedef struct {
    int (*init)(pPackageQueue_t, void*, int);
    int (*set)(pPackageQueue_t, uint8_t *, uint16_t);
    int (*get)(pPackageQueue_t, uint8_t *);
    int (*getCount)(pPackageQueue_t);
} PackageQueueClass_t, *pPackageQueueClass_t;

/*
void queueInit(void)
{
    
    pPackageQueueClass_t qHandle;
    static uint8_t queue1Mem[100];
    static uint8_t queue2Mem[100];
    PackageQueue_t queue1;
    PackageQueue_t queue2;

    qHandle = CWM_GET_PACKAGE_QUEUE_HANDLE();
    qHandle->init(&queue1, queue1Mem, 100);
    qHandle->init(&queue2, queue2Mem, 100);
}
void sample(void)
{
    queueInit();

}
*/
pPackageQueueClass_t CWM_GET_PACKAGE_QUEUE_HANDLE(void);

#endif /* __CWM_PACKAGE_QUEUE_H__ */
