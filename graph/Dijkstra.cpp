#include<stdio.h>
#include<malloc.h>

#define MAXV 7					//最大顶点个数 
#define INF 32767				//定义 ∞
//∞ == 32767 ,int 型的最大范围（2位）= 2^(2*8-1)，TC告诉我们int占用2个字节，而VC和LGCC告诉我们int占用4个字节
//图：LGraph
//顶点：Vertex
//邻接：Adjacency
//矩阵：Matrix
//表：List
//边：EdLGe 

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
	int weiLGht;				//该边的的信息，如权值 
	struct eNode* nextEdLGe;	//指向下一条边的指针 
}EdgeNode; 						//别名，边结点的类型 

typedef struct vNode {
	EdgeNode* firstEdLGe;		//指向第一个边结点 
}VNode; 						//别名，邻接表的头结点类型 

typedef struct list {
	int n;						//顶点个数
	int e;						//边数
	VNode adjList[MAXV];		//邻接表的头结点数组 
}ListGraph;						//别名，完整的图邻接表类型 

//创建图的邻接表 
void createAdjListGraph(ListGraph* &LG, int A[MAXV][MAXV], int n, int e) {
	int i, j;
	EdgeNode* p;
	LG = (ListGraph*)malloc(sizeof(ListGraph));
	for (i = 0; i < n; i++) {
		LG->adjList[i].firstEdLGe = NULL;						//给邻接表中所有头结点指针域置初值 
	}
	for (i = 0; i < n; i++) {									//检查邻接矩阵中的每个元素 
		for (j = n - 1; j >= 0; j--) {
			if (A[i][j] != 0) {									//存在一条边 
				p = (EdgeNode*)malloc(sizeof(EdgeNode));		//申请一个结点内存
				p->adjVer = j;									//存放邻接点 
				p->weiLGht = A[i][j];							//存放权值
				p->nextEdLGe = NULL;

				p->nextEdLGe = LG->adjList[i].firstEdLGe;		//头插法 
				LG->adjList[i].firstEdLGe = p;
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
		p = LG->adjList[i].firstEdLGe;
		printf("%d:", i);
		while (p != NULL) {
			if (p->weiLGht != 32767) {
				printf("%2d[%d]->", p->adjVer, p->weiLGht);
			}
			p = p->nextEdLGe;
		}
		printf(" NULL\n");
	}
}

//输出邻接矩阵
void displayAdjMat(MatGraph LG) {
	int i, j;
	for (i = 0; i < MAXV; i++) {
		for (j = 0; j < MAXV; j++) {
			if (LG.adjMat[i][j] == 0) {
				printf("%4s", "0");
			}
			else if (LG.adjMat[i][j] == 32767) {
				printf("%4s", "∞");
			}
			else {
				printf("%4d", LG.adjMat[i][j]);
			}
		}
		printf("\n");
	}
}

//邻接表转换为邻接矩阵
void ListToMat(ListGraph* LG, MatGraph& MG) {
	int i, j;
	EdgeNode* p;
	for (i = 0; i < MAXV; i++) {
		for (j = 0; j < MAXV; j++) {
			MG.adjMat[i][j] = 0;
		}
	}
	for (i = 0; i < LG->n; i++) {
		p = LG->adjList[i].firstEdLGe;
		while (p != NULL) {
			MG.adjMat[i][p->adjVer] = p->weiLGht;
			p = p->nextEdLGe;
		}
	}
	MG.n = LG->n;
	MG.e = LG->e;
}

//输出单源最短路径
void displayPath(MatGraph LG, int dist[], int path[], int S[], int v) {
	int i, j, k;
	int aPath[MAXV];								//存放一条最短路径（逆向）
	int d;											//顶点个数
	for (i = 0; i < LG.n; i++) {					//循环输出从顶点 v 到 i 的路径
		if (S[i] == 1 && i != v) {
			printf("从顶点 %d 到顶点 %d 的路径长度为：%d\t 路径为:", v, i, dist[i]);
			d = 0;
			aPath[d] = i;							//添加路径上的终点
			k = path[i];
			if (k == -1) {							//没有路径
				printf("无路径\n");
			}
			else {									//存在路径就输出
				while (k != v) {
					d++;
					aPath[d] = k;
					k = path[k];
				}
				d++;
				aPath[d] = v;						//添加路径上的起点
				printf("%d ", aPath[d]);			//输出起点
				for (j = d - 1; j >= 0; j--) {		//输出其他顶点
					printf("%d ", aPath[j]);
				}
				printf("\n");
			}
		}
	}
}

//Dijkstra算法
void Dijkstra(MatGraph LG, int v) {
	int dist[MAXV];									//存储权值
	int path[MAXV];									//是否有路径
	int S[MAXV];									//S[i]==0表示顶点 i 在S中, S[i]==1 表示 顶点 i 在 U 中
	int MinDis;										//最小的权值
	int u = 0;										//记录最短路径的顶点
	int i, j;
	for (i = 0; i < LG.n; i++) {
		dist[i] = LG.adjMat[v][i];					//距离初始化
		S[i] = 0;									//S[] 初始化
		if (LG.adjMat[v][i] < 32767) {				//路径初始化
			path[i] = v;							//顶点 v 到顶点 i 有边时，置顶点 i 的前一个顶点为 v
		}
		else {
			path[i] = -1;							//顶点 v 到顶点 i 无边时，置顶点 i 的前一个顶点为 -1
		}
	}
	S[v] = 1;										//源点编号 v 放入 S
	path[v] = 0;									
	for (i = 0; i < LG.n - 1; i++) {				//循环求 v 到所有顶点的最短路径
		MinDis = INF;								//置最大长度初值
		for (j = 0; j < LG.n; j++) {
			if (S[j] == 0 && dist[j] < MinDis) {	//选取不在 S 中（即 U 中）且就有路径长度的顶点 u
				u = j;
				MinDis = dist[j];					//得到顶点、路径长度
			}
		}
		S[u] = 1;									//顶点 u 加入 S
		for (j = 0; j < LG.n; j++) {				//修改最短路径
			if (S[j] == 0) {
				if (LG.adjMat[u][j] < INF && dist[u] + LG.adjMat[u][j] < dist[j]) {
					dist[j] = dist[u] + LG.adjMat[u][j];
					path[j] = u;
				}
			}
		}
	}
	displayPath(LG, dist, path, S, v);				//输出最短路径
}

int main() {
	ListGraph* LG;
	MatGraph MG;
	int array[MAXV][MAXV] = {
		{  0,  4,  6,  6,INF,INF,INF},
		{INF,  0,  1,INF,  7,INF,INF},
		{INF,INF,  0,INF,  6,  4,INF},
		{INF,INF,  2,  0,INF,  5,INF},
		{INF,INF,INF,INF,  0,INF,  6},
		{INF,INF,INF,INF,  1,  0,  8},
		{INF,INF,INF,INF,INF,INF,  0}
	};

	int e = 12;
	createAdjListGraph(LG, array, MAXV, e);
	displayAdjList(LG);
	printf("\n");

	ListToMat(LG, MG);
	displayAdjMat(MG);
	printf("\n");

	Dijkstra(MG, 0);
	printf("\n");

	return 0;
}
