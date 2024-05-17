#include <malloc.h>
#include <stdio.h>

#define MAXV 7     //最大顶点个数
#define INF  32767 //定义 ∞
//∞ == INF ,int 型的最大范围（2位）= 2^(2*8-1)，TC告诉我们int占用2个字节，而VC和LGCC告诉我们int占用4个字节
//图：LGraph
//顶点：Vertex
//邻接：Adjacency
//矩阵：Matrix
//表：List
//边：EdLGe
//深度优先遍历：Depth First Search （DFS）
//广度优先比例：Breadth First Search （BFS）

typedef struct eNode {
    int           adjVer;   //该边的邻接点编号
    int           weight;   //该边的的信息，如权值
    struct eNode* nextEdge; //指向下一条边的指针
} EdgeNode;                 //别名，边结点的类型

typedef struct vNode {
    EdgeNode* firstEdge; //指向第一个边结点
} VNode;                 //别名，邻接表的头结点类型

typedef struct list {
    int   n;             //顶点个数
    int   e;             //边数
    VNode adjList[MAXV]; //邻接表的头结点数组
} ListGraph;             //别名，完整的图邻接表类型

typedef struct quene { //定义顺序队
    int  front;        //队头指针
    char data[MAXV];   //存放队中元素
    int  rear;         //队尾指针
} SqQueue;             //struct Queue 的别名

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
int enQueue(SqQueue*& q, char c) {
    if (q->rear == MAXV - 1) { //判断队列是否满了
        return -1;             //返回 -1
    }
    q->rear++;            //头指针加 1
    q->data[q->rear] = c; //传值
    return c;             //返回 c
}

//出队列
int deQueue(SqQueue*& q, char ch) {
    if (q->front == q->rear) { //判断是否空了
        return -1;             //返回假 -1
    }
    q->front++;             //尾指针加 1
    ch = q->data[q->front]; //取值
    return ch;              //返回 ch
}

//创建图的邻接表
void createAdjListGraph(ListGraph*& LG, int A[MAXV][MAXV], int n, int e) {
    int       i, j;
    EdgeNode* p;
    LG = (ListGraph*)malloc(sizeof(ListGraph));
    for (i = 0; i < n; i++) {
        LG->adjList[i].firstEdge = NULL; //给邻接表中所有头结点指针域置初值
    }
    for (i = 0; i < n; i++) { //检查邻接矩阵中的每个元素
        for (j = n - 1; j >= 0; j--) {
            if (A[i][j] != 0) {                                    //存在一条边
                p           = (EdgeNode*)malloc(sizeof(EdgeNode)); //申请一个结点内存
                p->adjVer   = j;                                   //存放邻接点
                p->weight   = A[i][j];                             //存放权值
                p->nextEdge = NULL;

                p->nextEdge              = LG->adjList[i].firstEdge; //头插法
                LG->adjList[i].firstEdge = p;
            }
        }
    }
    LG->n = n;
    LG->e = e;
}

//输出邻接表
void displayAdjList(ListGraph* LG) {
    int       i;
    EdgeNode* p;
    for (i = 0; i < MAXV; i++) {
        p = LG->adjList[i].firstEdge;
        printf("%d:", i);
        while (p != NULL) {
            if (p->weight != INF) {
                printf("%2d[%d]->", p->adjVer, p->weight);
            }
            p = p->nextEdge;
        }
        printf(" NULL\n");
    }
}

//深度优先遍历
int  visitedDFS[MAXV] = {0}; //全局数组，记录是否遍历
void DFS(ListGraph* LG, int v) {
    EdgeNode* p;
    visitedDFS[v] = 1;            //记录已访问，置 1
    printf("%2d", v);             //输出顶点编号
    p = LG->adjList[v].firstEdge; //p 指向顶点 v 的第一个邻接点
    while (p != NULL) {
        if (visitedDFS[p->adjVer] == 0 && p->weight != INF) { //如果 p->adjVer 没被访问，递归访问它
            DFS(LG, p->adjVer);
        }
        p = p->nextEdge; //p 指向顶点 v 的下一个邻接点
    }
}

//广度优先遍历
void BFS(ListGraph* LG, int v) {
    int       ver; //定义出队顶点
    EdgeNode* p;
    SqQueue*  sq;               //定义指针
    initQueue(sq);              //初始化队列
    int visitedBFS[MAXV] = {0}; //初始化访问标记数组
    enQueue(sq, v);             //初始点进队
    printf("%2d", v);
    visitedBFS[v] = 1;                                            //打印并标记要出队顶点
    while (!emptyQueue(sq)) {                                     //队为空结束循环
        ver = deQueue(sq, v);                                     //出队，并得到出队信息
        p   = LG->adjList[ver].firstEdge;                         //指向出队的第一个邻接点
        while (p != NULL) {                                       //查找 ver 的所有邻接点
            if (visitedBFS[p->adjVer] == 0 && p->weight != INF) { //如果没被访问
                printf("%2d", p->adjVer);                         //打印该顶点信息
                visitedBFS[p->adjVer] = 1;                        //置已访问状态
                enQueue(sq, p->adjVer);                           //该顶点进队
            }
            p = p->nextEdge; //找下一个邻接点
        }
    }
    printf("\n");
}

int main() {
    ListGraph* LG;

    int array[MAXV][MAXV] = {
        {0, 4, 6, 6, INF, INF, INF},
        {INF, 0, 1, INF, 7, INF, INF},
        {INF, INF, 0, INF, 6, 4, INF},
        {INF, INF, 2, 0, INF, 5, INF},
        {INF, INF, INF, INF, 0, INF, 6},
        {INF, INF, INF, INF, 1, 0, 8},
        {INF, INF, INF, INF, INF, INF, 0}};

    int e = 12;
    createAdjListGraph(LG, array, MAXV, e);

    printf("邻接表为：\n");
    displayAdjList(LG);
    printf("\n");

    printf("深度优先遍历为：");
    DFS(LG, 0);
    printf("\n");

    printf("广度优先遍历为：");
    BFS(LG, 0);
    printf("\n");

    return 0;
}
