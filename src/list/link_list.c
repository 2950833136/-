#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int          data; // 存放数据
    struct node* next; // 下一个节点
} ListNode;            // 单节点类型

// 初始化线性表
void InitList(ListNode* L)
{
    L       = (ListNode*)malloc(sizeof(ListNode));
    L->next = NULL;
}

// 建立单链表
// 头插法
void CreateListF(ListNode* L, int array[], int n)
{
    ListNode* s;
    L       = (ListNode*)malloc(sizeof(ListNode));
    L->next = NULL; // 创建头结点，其 next 域置为 NULL
    for (int i = 0; i < n; i++)
    {                                                  // 循环建立数据节点 s
        s       = (ListNode*)malloc(sizeof(ListNode)); // 新建节点
        s->data = array[i];                            // 赋值
        s->next = L->next;                             // 将结点 s 插入到原首结点之前，头结点之后
        L->next = s;
    }
}
// 尾插法
void CreateListR(ListNode** L, int array[], int n)
{
    ListNode* s;
    ListNode* r;
    *L = (ListNode*)malloc(sizeof(ListNode)); // 创建头结点
    r  = *L;                                   // r 始终指向尾结点，初始时指向头结点 （头结点序号为 0）
    for (int i = 0; i < n; i++)
    {                                                  // 循环建立数据节点 s
        s       = (ListNode*)malloc(sizeof(ListNode)); // 新建节点
        s->data = array[i];                            // 赋值
        r->next = s;                                   // 将结点 s 插入到结点 r 之后
        r       = s;
    }
    r->next = NULL; // 尾结点其 next 域置为 NULL
}

// 销毁线性表
void DestroyList(ListNode* L)
{
    ListNode *pre = L, *p = L->next; // pre 指向结点 p 的前驱节点
    // 扫描单链表 L
    while (p != NULL)
    {
        free(pre); // 释放 pre 结点
        pre = p;   // pre、p 同步后移一个结点
        p   = pre->next;
    }
    free(pre); // 循环结束时 p 为 NULL，pre指向尾结点释放它
}

// 判断是否为空
bool ListEmpty(ListNode* L)
{
    return L->next == NULL;
}

// 求线性表的长度
int ListLength(ListNode* L)
{
    // p 指向头结点，n置为0
    int       n = 0;
    ListNode* p = L;
    // 不为空，依次遍历
    while (p->next != NULL)
    {
        n++;
        p = p->next;
    }
    return n; // 返回长度
}

// 输出线性表
void Display(ListNode* L)
{
    // p 指向首结点 （首结点序号为 1）
    ListNode* p = L->next;
    while (p != NULL)
    {                           // 不为空，依次遍历
        printf("%d ", p->data); // 打印
        p = p->next;            // p 移向下一个节点
    }
    printf("\n");
}

// 查找某个数据元素值
bool GetData(ListNode* L, int i, int* data)
{
    // p 指向首结点 （首结点序号为 1）
    ListNode* p = L->next;
    if (i <= 0)
    {
        return false;
    }
    int j = 0;
    // 找第 i 个结点 p
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        *data = p->data;
        return true;
    }
}

// 按元素值查找
int LocateData(ListNode* L, int data)
{
    // p 指向头结点 ，i 置为 1（首结点序号为 1）
    int       i = 1;
    ListNode* p = L->next;
    // 查找 data 值，其序号为 i
    while (p != NULL && p->data != data)
    {
        p = p->next;
        i++;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        return i;
    }
}

// 插入数据元素
bool ListInsert(ListNode* L, int i, int data)
{
    // p 指向头结点 （头结点序号为 0）
    ListNode *p = L, *s;
    if (i <= 0)
    {
        return false;
    }
    int j = 0;
    // 查找第 i-1 个结点 p
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {                                                  // 找到第 i-1 个结点 p ,插入新结点并返回 true
        s       = (ListNode*)malloc(sizeof(ListNode)); // 新建节点
        s->data = data;                                // 创建新结点 s,其值为 data
        s->next = p->next;                             // 头插法
        p->next = s;
        return true;
    }
}

// 删除数据元素
bool ListDelete(ListNode* L, int i, int* data)
{
    ListNode *p = L, *q; // p 指向头结点 （头结点序号为 0）
    if (i <= 0)
    { // i 错误返回假
        return false;
    }
    int j = 0; // j 置为 0
    while (j < i - 1 && p != NULL)
    { // 查找第 i 个结点 p
        j++;
        p = p->next;
    }
    if (p == NULL)
    { // 未找到
        return false;
    }
    else
    {                // 找到第 i-1 个结点 p
        q = p->next; // q 指向第 i 个结点
        if (q == NULL)
        { // 若不存在第 i 个结点
            return false;
        }
        *data    = q->data;
        p->next = q->next; // 删除 q 结点，第 i-1 个结点 指向第 i+1 个结点
        free(q);           // 释放 q 结点
        return true;
    }
}

int main()
{
#if defined(WIN32) || defined(_WIN32)
    system("chcp 65001");
#endif
    int       array[] = {1, 3, 5, 7, 9};
    int       n       = sizeof(array) / sizeof(int);
    ListNode* L       = (ListNode*)malloc(sizeof(ListNode));
    CreateListR(&L, array, n);
    printf("输出单链表为：");
    Display(L);

    int i = 5, j = 0;
    GetData(L, i, &j);
    printf("查找第 %d 个元素是值为 %d\n", i, j);

    int x   = 9;
    int num = LocateData(L, x);
    printf("查找值为 %d 是第 %d 个元素\n", x, num);
    
    int insert_num = 11;
    ListInsert(L, 6, insert_num);
    printf("插入 %d 成功!\n", insert_num);
    Display(L);

    int delete_num = 0;
    ListDelete(L, 6, &delete_num);
    printf("删除 %d 成功!\n", delete_num);
    Display(L);

    DestroyList(L);
    return 0;
}
