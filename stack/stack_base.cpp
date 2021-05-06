#include <iostream>
#include <malloc.h>

#define maxsize 100 //最大空间
using namespace std;

typedef struct Stack {
    int data[maxsize];
    int top;
} SqStack; //栈的类型

//初始化
void InitStack(SqStack*& s) {
    s      = (SqStack*)malloc(sizeof(SqStack)); //分配一个顺序栈空间，首地址存放在 s 中
    s->top = -1;                                //栈顶指针置为 -1
}

//销毁栈
void DestroyStack(SqStack*& s) {
    free(s);
}

//判断是否空
bool StackEmpty(SqStack* s) {
    return (s->top == -1) ? true : false;
}

//进栈
bool Push(SqStack*& s, int x) {
    if (s->top == maxsize - 1) { //栈满情况
        return false;
    } else {
        s->top++;            //栈顶指针加一
        s->data[s->top] = x; //元素 x 放在栈顶指针处
        return true;
    }
}

//出栈
bool Pop(SqStack*& s, int& x) {
    if (s->top == -1) { //栈空情况
        return false;
    } else {
        x = s->data[s->top]; //取栈顶元素
        s->top--;            //栈顶指针减一
        return true;
    }
}

//取栈顶元素
bool GetTop(SqStack* s, int& x) {
    if (s->top == -1) { //栈空情况
        return false;
    } else {
        x = s->data[s->top]; //取栈顶元素
        return true;
    }
}

int main() {
    int      i, n;
    int      x, y;
    int      a[maxsize];
    SqStack* s;
    InitStack(s);
    cout << "输入个数: ";
    cin >> n;
    cout << "输入值: ";
    for (i = 0; i < n; i++) {
        cin >> a[i];
        Push(s, a[i]);
    }
    cout << "栈顶元素: ";
    GetTop(s, x);
    cout << x << endl;
    cout << "栈的输出: ";
    while (!StackEmpty(s)) {
        Pop(s, y);
        cout << y << " ";
    }
    cout << endl;
    return 0;
}
