#include <malloc.h>
#include <stdio.h>

#define MaxSize 1024

typedef struct Quene {  // 定义顺序队
    int  front;         // 队头指针
    char data[MaxSize]; // 存放队中元素
    int  rear;          // 队尾指针
} SqQueue;              // struct Queue 的别名

// 初始化队列
void initQueue(SqQueue*& q) {
    q        = (SqQueue*)malloc(sizeof(SqQueue)); // 分配一个空间
    q->front = q->rear = -1;                      // 置 -1
}

// 销毁队列
void destroyQueue(SqQueue*& q) {
    free(q);
}

// 判断队列是否为空
bool emptyQueue(SqQueue*& q) {
    if (q->front == q->rear) { // 首指针和尾指针相等，说明为空
        return true;
    } else {
        return false;
    }
}

// 进队列
bool enQueue(SqQueue*& q, char c) {
    if (q->rear == MaxSize - 1) { // 判断队列是否满了
        return false;
    }
    q->rear++;            // 头指针加 1
    q->data[q->rear] = c; // 传值
    return true;          // 返回真
}

// 出队列
bool deQueue(SqQueue*& q, char ch) {
    if (q->front == q->rear) { // 判断是否空了
        return false;          // 返回假
    }
    q->front++;             // 尾指针加 1
    ch = q->data[q->front]; // 取值
    printf("%c", ch);       // 输出值
    return true;            // 返回真
}

int main() {
    SqQueue* Q;
    initQueue(Q);
    printf("初始化成功\n");

    // 销毁队列
    // destroyQueue(Q);

    int   n   = 0;
    char* str = (char*)malloc(sizeof(char) * MaxSize);
    printf("请输入要加入元素：");
    scanf("%s", str);
    while (n < MaxSize) {
        char c = str[n];
        n++;
        if (c != '\0') {
            enQueue(Q, c);
        } else {
            break;
        }
    }
    printf("加入成功");
    printf("\n");

    char ch;
    printf("队列元素：");
    while (!emptyQueue(Q)) { // 判断是否为空
        deQueue(Q, ch);
    }

    return 0;
}
