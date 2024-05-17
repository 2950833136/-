#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 // 最大空间

typedef struct Stack
{
    int data[MAXSIZE];
    int top;
} SqStack; // 栈的类型

// 初始化
void InitStack(SqStack** s)
{
    *s        = (SqStack*)malloc(sizeof(SqStack)); // 分配一个顺序栈空间，首地址存放在 s 中
    (*s)->top = -1;                                // 栈顶指针置为 -1
}

// 销毁栈
void DestroyStack(SqStack* s)
{
    free(s);
}

// 判断是否空
bool StackEmpty(SqStack* s)
{
    return (s->top == -1) ? true : false;
}

// 进栈
bool Push(SqStack* s, int x)
{
    // 栈满情况
    if (s->top == MAXSIZE - 1)
    {
        return false;
    }
    else
    {
        s->top++;            // 栈顶指针加一
        s->data[s->top] = x; // 元素 x 放在栈顶指针处
        return true;
    }
}

// 出栈
bool Pop(SqStack* s, int* x)
{
    if (s->top == -1)
    { // 栈空情况
        return false;
    }
    else
    {
        *x = s->data[s->top]; // 取栈顶元素
        s->top--;             // 栈顶指针减一
        return true;
    }
}

// 取栈顶元素
bool GetTop(SqStack* s, int* x)
{
    // 栈空情况
    if (s->top == -1)
    {
        return false;
    }
    else
    {
        *x = s->data[s->top]; // 取栈顶元素
        return true;
    }
}

int main()
{
#if defined(WIN32) || defined(_WIN32)
    system("chcp 65001");
#endif
    int      i = 0;
    int      n = 0;
    int      x = 0;
    int      y = 0;
    int      a[MAXSIZE];
    SqStack* s = NULL;
    InitStack(&s);
    printf("输入个数: ");
    scanf("%d", &n);
    printf("输入值: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        Push(s, a[i]);
    }
    printf("栈顶元素: ");
    GetTop(s, &x);
    printf("%d\n", x);
    printf("栈的输出: ");
    while (!StackEmpty(s))
    {
        Pop(s, &y);
        printf("%d ", y);
    }
    return 0;
}
