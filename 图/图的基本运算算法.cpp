#include<stdio.h>
#include<malloc.h>

#define MAXV 5					//最大顶点个数 
#define INF 32767				//定义 ∞ 
//∞ == INF ,int 型的最大范围（2位）= 2^(2*8-1)，TC告诉我们int占用2个字节，而VC和GCC告诉我们int占用4个字节
//图：Graph
//顶点：Vertex
//邻接：Adjacency
//矩阵：Matrix
//表：List
//边：Edge 

typedef struct vertex {
	int number;					//顶点的编号 	
}VertexType; 					//别名，顶点的类型 

typedef struct matrix {
	int n;						//顶点个数
	int e;						//边数 
	int adjMat[MAXV][MAXV];		//邻接矩阵数组			
	VertexType ver[MAXV];		//存放顶点信息 
}MatGraph;						//别名，完整的图邻接矩阵类型

typedef struct eNode {
	int adjVer;					//该边的邻接点编号 
	int weight;					//该边的的信息，如权值 
	struct eNode* nextEdge;		//指向下一条边的指针 
}EdgeNode; 						//别名，边结点的类型 

typedef struct vNode {
	EdgeNode* firstEdge;		//指向第一个边结点 
}VNode; 						//别名，邻接表的头结点类型 

typedef struct list {
	int n;						//顶点个数
	int e;						//边数
	VNode adjList[MAXV];		//邻接表的头结点数组 
}ListGraph;						//别名，完整的图邻接表类型 

//创建图的邻接表 
void createAdjListGraph(ListGraph*& LG, int A[MAXV][MAXV], int n, int e) {
	int i, j;
	EdgeNode* p;
	LG = (ListGraph*)malloc(sizeof(ListGraph));
	for (i = 0; i < n; i++) {
		LG->adjList[i].firstEdge = NULL;						//给邻接表中所有头结点指针域置初值 
	}
	for (i = 0; i < n; i++) {									//检查邻接矩阵中的每个元素 
		for (j = n - 1; j >= 0; j--) {
			if (A[i][j] != 0) {									//存在一条边 
				p = (EdgeNode*)malloc(sizeof(EdgeNode));		//申请一个结点内存
				p->adjVer = j;									//存放邻接点 
				p->weight = A[i][j];							//存放权值
				p->nextEdge = NULL;

				p->nextEdge = LG->adjList[i].firstEdge;			//头插法 
				LG->adjList[i].firstEdge = p;
			}
		}
	}
	LG->n = n;
	LG->e = e;
}

//输出邻接表 
void displayAdjList(ListGraph* LG) {
	int i;
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

//输出邻接矩阵
void displayAdjMat(MatGraph MG) {
	int i, j;
//	printf(" ");
//	for (i = 0; i < MG.n; i++) {
//		printf("%4d",i);
//	}
//	printf("\n");
	for (i = 0; i < MG.n; i++) {
//		printf("%d",i);
		for (j = 0; j < MG.n; j++) {
			if (MG.adjMat[i][j] == 0) {
				printf("%4s", "0");
			}
			else if (MG.adjMat[i][j] == INF) {
				printf("%4s", "∞");
			}
			else {
				printf("%4d", MG.adjMat[i][j]);
			}
		}
		printf("\n");
	}
}

//邻接表转换为邻接矩阵
void ListToMat(ListGraph* LG, MatGraph &MG) {
	int i, j;
	EdgeNode* p;
	for (i = 0; i < MAXV; i++) {					//初始化置 0
		for (j = 0; j < MAXV; j++) {
			MG.adjMat[i][j] = 0;
		}
	}
	for (i = 0; i < LG->n; i++) {					//扫描所有单链表
		p = LG->adjList[i].firstEdge;				//p 指向第 i 个单链表的头结点
		while (p != NULL) {							//遍历单链表
			MG.adjMat[i][p->adjVer] = p->weight;
			p = p->nextEdge;
		}
	}
	MG.n = LG->n;
	MG.e = LG->e;
}

//邻接矩阵转换为邻接表 
void MatToList(MatGraph MG, ListGraph* &LG) {
	int i, j;
	EdgeNode* p;
	LG = (ListGraph*)malloc(sizeof(ListGraph));
	for (i = 0; i < MG.n; i++) {
		LG->adjList[i].firstEdge = NULL;						//给邻接表中所有头结点指针域置初值 
	}
	for (i = 0; i < MG.n; i++) {								//检查邻接矩阵中的每个元素 
		for (j = MG.n - 1; j >= 0; j--) {
			if (MG.adjMat[i][j] != 0) {							//存在一条边 
				p = (EdgeNode*)malloc(sizeof(EdgeNode));		//申请一个结点内存
				p->adjVer = j;									//存放邻接点 
				p->weight = MG.adjMat[i][j];					//存放权值
				p->nextEdge = NULL;

				p->nextEdge = LG->adjList[i].firstEdge;			//头插法 
				LG->adjList[i].firstEdge = p;
			}
		}
	}
	LG->n = MG.n;
	LG->e = MG.e;
}

//销毁图
void destroyAdjListGraph(ListGraph* LG) {
	int i;
	EdgeNode* pre, * p;
	for (i = 0; i < LG->n; i++) {
		pre = LG->adjList[i].firstEdge;				//挨个释放内存 
		if (pre != NULL) {
			p = pre->nextEdge;
			while (p != NULL) {
				free(pre);
				pre = p;
				p = p->nextEdge;
			}
			free(pre);
		}
	}
	free(LG);
}

int main() {
	ListGraph* LG;						//邻接表 
	MatGraph MG;						//邻接矩阵 
	int array1[MAXV][MAXV] = {			//不带权无向图 
		{0,1,0,1,1},
		{1,0,1,1,0},
		{0,1,0,1,1},
		{1,1,1,0,1},
		{1,0,1,1,0}
	};
	int array2[MAXV][MAXV] = {			//不带权有向图 
		{0,1,0,1,0},
		{0,0,1,1,0},
		{0,0,0,1,1},
		{0,0,0,0,0},
		{1,0,0,1,0}
	};
	int array3[MAXV][MAXV] = {			//带权无向图 
		{  0,  8,INF,  5,INF},
		{  8,  0,  3,INF,INF},
		{INF,  3,  0,  9,  6},
		{  5,INF,  9,  0,INF},
		{INF,INF,  6,INF,  0}
	};
	int array4[MAXV][MAXV] = {			//带权有向图 
		{  0,  8,INF,  5,INF},
		{INF,  0,  3,INF,INF},
		{INF,INF,  0,INF,  6},
		{INF,INF,  9,  0,INF},
		{INF,INF,INF,INF,  0}
	};
	int e = 5;
	createAdjListGraph(LG, array4, MAXV, e);		//创建邻接表图 
	
	printf("邻接表为：\n");
	displayAdjList(LG);								//输出邻接表
	printf("\n");

	ListToMat(LG, MG);								//邻接表转换为邻接矩阵
	printf("邻接矩阵为：\n");
	displayAdjMat(MG);								//输出邻接矩阵 
	printf("\n");

	MatToList(MG, LG);								//邻接矩阵转换为邻接表
	printf("邻接表为：\n");
	displayAdjList(LG);								//输出邻接表 
	printf("\n");

	return 0;
}
