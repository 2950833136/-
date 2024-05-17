#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024

typedef struct Quene
{                       // 定义顺序队
    int  front;         // 队头指针
    char data[MAXSIZE]; // 存放队中元素
    int  rear;          // 队尾指针
} SqQueue;              // struct Queue 的别名

// 初始化队列
void initQueue(SqQueue** q)
{
    *q          = (SqQueue*)malloc(sizeof(SqQueue)); // 分配一个空间
    (*q)->front = (*q)->rear = -1;                   // 置 -1
}

// 销毁队列
void destroyQueue(SqQueue* q)
{
    free(q);
}

// 判断队列是否为空
bool emptyQueue(SqQueue* q)
{
    // 首指针和尾指针相等，说明为空
    return (q->front == q->rear);
}

// 进队列
bool enQueue(SqQueue* q, char c)
{
    // 判断队列是否满了
    if (q->rear == MAXSIZE - 1)
    {
        return false;
    }
    q->rear++;            // 头指针加 1
    q->data[q->rear] = c; // 传值
    return true;          // 返回真
}

// 出队列
bool deQueue(SqQueue* q, char* c)
{
    // 判断是否空了
    if (q->front == q->rear)
    {
        return false;
    }
    q->front++;             // 尾指针加 1
    *c = q->data[q->front]; // 取值
    return true;            // 返回真
}

int main()
{
#if defined(WIN32) || defined(_WIN32)
    system("chcp 65001");
#endif
    SqQueue* Q = NULL;
    initQueue(&Q);
    printf("初始化成功\n");

    int   n   = 0;
    char* str = (char*)malloc(sizeof(char) * MAXSIZE);
    printf("请输入要加入元素：");
    scanf("%s", str);
    while (n < MAXSIZE && str[n] != '\0')
    {
        enQueue(Q, str[n]);
        n++;
    }
    printf("\n");

    char c;
    printf("队列元素：");
    while (!emptyQueue(Q))
    {
        deQueue(Q, &c);
        printf("%c ", c);
    }

    // 销毁队列
    destroyQueue(Q);
    return 0;
}
