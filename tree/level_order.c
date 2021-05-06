#define _CRT_SECURE_NO_WARNINGS // VS忽略警告，其它应该不需要

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128
#define STR_SIZE 1024

typedef struct Node {    // 定义二叉链
    char         data;   // 数据元素
    struct Node* lchild; // 指向左孩子节点
    struct Node* rchild; // 指向右孩子节点
} BTNode;                // struct Node 的别名

typedef struct Quene {      // 定义顺序队
    int     front;          // 队头指针
    int     rear;           // 队尾指针
    BTNode* data[MAX_SIZE]; // 存放队中元素
} SqQueue;                  // struct Queue 的别名

/**
 * 队列函数
 */
void initQueue(SqQueue** q);             // 初始化队列
bool emptyQueue(SqQueue* q);             // 判断队列空
bool enQueue(SqQueue* q, BTNode* node);  // 入队
bool deQueue(SqQueue* q, BTNode** node); // 出队

/**
 * 二叉树函数
 */
// void createBTNode2(BTNode** BT);                  // 创建二叉树
int  createBTNode(BTNode** BT, char* str, int n); // 创建二叉树
void preOrder(BTNode* BT);                        // 前序遍历
void inOrder(BTNode* BT);                         // 中序遍历
void postOrder(BTNode* BT);                       // 后序遍历
void levelOrder(BTNode* BT);                      // 层次遍历

/**
 * 画树函数
 */
void draw_level(BTNode* node, bool left, char* str); // 画分支
void draw(BTNode* root);                             // 画根节点

/***************************************************************************
 * @date    2019/12/08
 * @brief   层次遍历二叉树
 * @param   BT  二叉树根节点
 ***************************************************************************/
void levelOrder(BTNode* BT) {
    SqQueue* q;       // 定义队列
    initQueue(&q);    // 初始化队列
    if (BT != NULL) { // 根节点指针进队列
        enQueue(q, BT);
    }
    // 一层一层的把节点存入队列，当没有孩子节点时就不再循环
    while (!emptyQueue(q)) {      // 队不为空循环
        deQueue(q, &BT);          // 出队时的节点
        printf("%c", BT->data);   // 输出节点存储的值
        if (BT->lchild != NULL) { // 有左孩子时将该节点进队列
            enQueue(q, BT->lchild);
        }
        if (BT->rchild != NULL) { // 有右孩子时将该节点进队列
            enQueue(q, BT->rchild);
        }
    }
}

int main() {
    // 例子：ABDH###E##CF##G##
    BTNode* BT;
    printf("请输入字符串：");
    char* str = (char*)malloc(sizeof(char) * STR_SIZE);
    scanf("%s", str);
    if (strlen(str) == createBTNode(&BT, str, 0)) {
        printf("二叉树建立成功\n");
    }
    // printf("请输入字符串：");
    // createBTNode2(&BT);
    // draw(BT);

    printf("\n先序遍历结果：");
    preOrder(BT);

    printf("\n中序遍历结果：");
    inOrder(BT);

    printf("\n后序遍历结果：");
    postOrder(BT);

    printf("\n层序遍历结果：");
    levelOrder(BT);

    return 0;
}

// 初始化队列
void initQueue(SqQueue** q) {
    if (!((*q) = (SqQueue*)malloc(sizeof(SqQueue)))) {
        printf("内存分配失败！");
        exit(-1);
    }
    (*q)->front = (*q)->rear = -1; // 置 -1
}

// 判断队列是否为空
bool emptyQueue(SqQueue* q) {
    // 首指针和尾指针相等，说明为空。空-返回真，不空-返回假
    if (q->front == q->rear) {
        return true;
    }
    return false;
}

// 进队列
bool enQueue(SqQueue* q, BTNode* node) {
    // 判断队列是否满了。满（插入失败）-返回假，不满（插入成功）-返回真
    if (q->rear == MAX_SIZE - 1) {
        return false;
    }
    q->rear++;               // 头指针加 1
    q->data[q->rear] = node; // 传值
    return true;
}

// 出队列
bool deQueue(SqQueue* q, BTNode** node) {
    // 判断是否空了。空（取出失败）-返回假，不空（取出成功）-返回真
    if (q->front == q->rear) {
        return false;
    }
    q->front++;                // 尾指针加 1
    *node = q->data[q->front]; // 取值
    return true;
}

// 创建二叉树
int createBTNode(BTNode** BT, char* str, int n) {
    char ch = str[n++];  // 把第 n 个字符赋给ch,方便后面判断，字符下标后移
    if (ch != '\0') {    // 如果 ch 不等于结束符就继续创建，否则就结束
        if (ch == '#') { // 以 # 号代表 NULL，下面没有了
            *BT = NULL;
        } else {
            if (!(*BT = (BTNode*)malloc(sizeof(BTNode)))) {
                printf("内存分配失败！");
                exit(-1);
            } else {
                (*BT)->data = ch;
                n           = createBTNode(&((*BT)->lchild), str, n); // 左递归创建
                n           = createBTNode(&((*BT)->rchild), str, n); // 右递归创建
            }
        }
    }
    // 返回 n，记录字符串使用到哪里了
    return n;
}
// 创建二叉树
// void createBTNode2(BTNode** BT) {
//     char ch;
//     ch = getchar();
//     if (ch == '#') {
//         *BT = NULL;
//     } else {
//         if (!(*BT = (BTNode*)malloc(sizeof(BTNode)))) {
//             printf("内存分配失败！");
//             return;
//         } else {
//             (*BT)->data = ch;
//             createBTNode2(&((*BT)->lchild)); // 分配成功则接着建立左子树和右子树
//             createBTNode2(&((*BT)->rchild));
//         }
//     }
// }

// 先序遍历
void preOrder(BTNode* BT) {
    if (BT != NULL) {           // 判断不为空
        printf("%c", BT->data); // 访问根节点
        preOrder(BT->lchild);   // 递归，先序遍历左子树
        preOrder(BT->rchild);   // 递归，先序遍历右子树
    }
}

// 中序遍历
void inOrder(BTNode* BT) {
    if (BT != NULL) {
        inOrder(BT->lchild);
        printf("%c", BT->data);
        inOrder(BT->rchild);
    }
}

// 后序遍历
void postOrder(BTNode* BT) {
    if (BT != NULL) {
        postOrder(BT->lchild);
        postOrder(BT->rchild);
        printf("%c", BT->data);
    }
}

/*****************************************************************************
* @date   2020/4/19
* @brief  水平画树
* @param  node	二叉树节点
* @param  left	判断左右
* @param  str 	可变字符串
*****************************************************************************/
void draw_level(BTNode* node, bool left, char* str) {
    if (node->rchild) {
        draw_level(node->rchild, false, strcat(str, (left ? "|     " : "      ")));
    }

    printf("%s", str);
    printf("%c", (left ? '\\' : '/'));
    printf("-----");
    printf("%c\n", node->data);

    if (node->lchild) {
        draw_level(node->lchild, true, strcat(str, (left ? "      " : "|     ")));
    }
    //  "      " : "|     " 长度为 6
    str[strlen(str) - 6] = '\0';
}

/*****************************************************************************
* @date   2020/4/19
* @brief  根节点画树
* @param  root	二叉树根节点
*****************************************************************************/
void draw(BTNode* root) {
    char str[STR_SIZE];
    memset(str, '\0', STR_SIZE);

    /**
     * 1. 在 windows 下，下面是可执行的
     * 2. 在 Linux   下，执行会报 Segmentation fault
     *      需要使用中间变量
     */
    if (root->rchild) {
        draw_level(root->rchild, false, str);
    }
    printf("%c\n", root->data);
    if (root->lchild) {
        draw_level(root->lchild, true, str);
    }
}
