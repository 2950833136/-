#define _CRT_SECURE_NO_WARNINGS //VS忽略警告，其它应该不需要

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024
#define STR_SIZE 1024

typedef struct Node {    // 定义二叉链
    char         key;    // 数据元素
    struct Node* lchild; // 指向左孩子节点
    struct Node* rchild; // 指向右孩子节点
} BTNode;                // struct Node 的别名

typedef struct Quene {     // 定义顺序队
    BTNode* key[MAX_SIZE]; // 存放队中元素
    int     front;         // 队头指针
    int     rear;          // 队尾指针
} SqQueue;                 // struct Queue 的别名

//初始化队列
void initQueue(SqQueue*& q) {
    q        = (SqQueue*)malloc(sizeof(SqQueue)); //分配一个空间
    q->front = q->rear = -1;                      //置 -1
}

//判断队列是否为空
bool emptyQueue(SqQueue*& q) {
    if (q->front == q->rear) { //首指针和尾指针相等，说明为空
        return true;           //返回真
    } else {
        return false; //返回假
    }
}

//进队列
bool enQueue(SqQueue*& q, BTNode*& BT) {
    if (q->rear == MAX_SIZE - 1) { //判断队列是否满了
        return false;              //返回假
    }
    q->rear++;            //头指针加 1
    q->key[q->rear] = BT; //传值
    return true;          //返回真
}

//出队列
bool deQueue(SqQueue*& q, BTNode*& BT) {
    if (q->front == q->rear) { //判断是否空了
        return false;          //返回假
    }
    q->front++;            //尾指针加 1
    BT = q->key[q->front]; //取值
    return true;           //返回真
}

//创建二叉树
int createBTNode(BTNode*& BT, char* str, int n) {
    char ch = str[n]; //把第 n 个字符赋给ch,方便后面判断
    n       = n + 1;
    if (ch != '\0') {    //如果 ch 不等于结束符就继续创建，否则就结束
        if (ch == '#') { //以 # 号代表 NULL，下面没有了
            BT = NULL;
        } else {
            BT      = new BTNode;                       //新建一个二叉链
            BT->key = ch;                               //把字符存入二叉链
            n       = createBTNode(BT->lchild, str, n); //左递归创建
            n       = createBTNode(BT->rchild, str, n); //右递归创建
        }
    }
    return n; //返回 n,记录字符串使用到哪里了
}
//二级指针创建
//void createBTNode2(BTNode** BT) {
//	char ch;
//	ch = getchar();
//	if (ch == '#') {
//		*BT = NULL;
//	}
//	else {
//		if (!(*BT = (BTNode*)malloc(sizeof(BTNode)))) {
//			printf("内存分配失败！");
//			return;
//		}
//		else {
//			(*BT)->key = ch;
//			createBTNode(&((*BT)->lchild));		//分配成功则接着建立左子树和右子树
//			createBTNode(&((*BT)->rchild));
//		}
//	}
//}

//先序遍历
void preOrder(BTNode*& BT) {
    if (BT != NULL) {          //判断不为空
        printf("%c", BT->key); //访问根节点
        preOrder(BT->lchild);  //递归，先序遍历左子树
        preOrder(BT->rchild);  //递归，先序遍历右子树
    }
}

//中序遍历
void inOrder(BTNode*& BT) {
    if (BT != NULL) {
        inOrder(BT->lchild);
        printf("%c", BT->key);
        inOrder(BT->rchild);
    }
}

//后序遍历
void postOrder(BTNode*& BT) {
    if (BT != NULL) {
        postOrder(BT->lchild);
        postOrder(BT->rchild);
        printf("%c", BT->key);
    }
}

//层次遍历
void levelOrder(BTNode*& BT) {
    SqQueue* q;   //定义队列
    initQueue(q); //初始化队列
    if (BT != NULL) {
        enQueue(q, BT); //根节点指针进队列
    }
    while (emptyQueue(q) != true) { //队不为空循环
        deQueue(q, BT);             //出队时的节点
        printf("%c", BT->key);      //输出节点存储的值
        if (BT->lchild != NULL) {   //有左孩子时将该节点进队列
            enQueue(q, BT->lchild);
        }
        if (BT->rchild != NULL) { //有右孩子时将该节点进队列
            enQueue(q, BT->rchild);
        } //一层一层的把节点存入队列
    }     //当没有孩子节点时就不再循环
}

/*****************************************************************************
* @date  : 2020/4/19
* @brief : 水平画树
* @input :
*   root: 树
*	left: 判断左右
*	str : 可变字符串
* @output:
*   none: none
*****************************************************************************/
void draw_level(BTNode* root, bool left, char* str) {
    if (root->rchild) {
        draw_level(root->rchild, false, strcat(str, (left ? "|     " : "      ")));
    }

    printf("%s", str);
    printf("%c", (left ? '\\' : '/'));
    printf("-----");
    printf("%c\n", root->key);

    if (root->lchild) {
        draw_level(root->lchild, true, strcat(str, (left ? "      " : "|     ")));
    }
    // "      " : "|     " 长度6
    str[strlen(str) - 6] = '\0';
}

/*****************************************************************************
* @date  : 2020/4/19
* @brief : 根节点画树
* @input :
*   root : 树
* @output:
*   none : none
*****************************************************************************/
void draw(BTNode* root) {
    char str[STR_SIZE];
    memset(str, '\0', STR_SIZE);

    if (root->rchild) {
        draw_level(root->rchild, false, str);
    }
    printf("%c\n", root->key);
    if (root->lchild) {
        draw_level(root->lchild, true, str);
    }
}

int main() {

    //例子：ABDH###E##CF##G##
    BTNode* BT;
    printf("输入字符串：");
    char* str = (char*)malloc(sizeof(char) * STR_SIZE);
    scanf("%s", str);

    if (strlen(str) == createBTNode(BT, str, 0)) {
        printf("二叉树建立成功\n");
    }
    //createBTNode2(&BT);

    draw(BT);

    printf("先序遍历结果：");
    preOrder(BT);
    printf("\n");

    printf("中序遍历结果：");
    inOrder(BT);
    printf("\n");

    printf("后序遍历结果：");
    postOrder(BT);
    printf("\n");

    printf("层序遍历结果：");
    levelOrder(BT);
    printf("\n");

    return 0;
}
