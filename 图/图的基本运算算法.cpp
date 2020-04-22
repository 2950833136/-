#include<stdio.h>
#include<malloc.h>

#define MAXV 5					//��󶥵���� 
#define INF 32767				//���� �� 
//�� == INF ,int �͵����Χ��2λ��= 2^(2*8-1)��TC��������intռ��2���ֽڣ���VC��GCC��������intռ��4���ֽ�
//ͼ��Graph
//���㣺Vertex
//�ڽӣ�Adjacency
//����Matrix
//��List
//�ߣ�Edge 

typedef struct vertex {
	int number;					//����ı�� 	
}VertexType; 					//��������������� 

typedef struct matrix {
	int n;						//�������
	int e;						//���� 
	int adjMat[MAXV][MAXV];		//�ڽӾ�������			
	VertexType ver[MAXV];		//��Ŷ�����Ϣ 
}MatGraph;						//������������ͼ�ڽӾ�������

typedef struct eNode {
	int adjVer;					//�ñߵ��ڽӵ��� 
	int weight;					//�ñߵĵ���Ϣ����Ȩֵ 
	struct eNode* nextEdge;		//ָ����һ���ߵ�ָ�� 
}EdgeNode; 						//�������߽������� 

typedef struct vNode {
	EdgeNode* firstEdge;		//ָ���һ���߽�� 
}VNode; 						//�������ڽӱ��ͷ������� 

typedef struct list {
	int n;						//�������
	int e;						//����
	VNode adjList[MAXV];		//�ڽӱ��ͷ������� 
}ListGraph;						//������������ͼ�ڽӱ����� 

//����ͼ���ڽӱ� 
void createAdjListGraph(ListGraph*& LG, int A[MAXV][MAXV], int n, int e) {
	int i, j;
	EdgeNode* p;
	LG = (ListGraph*)malloc(sizeof(ListGraph));
	for (i = 0; i < n; i++) {
		LG->adjList[i].firstEdge = NULL;						//���ڽӱ�������ͷ���ָ�����ó�ֵ 
	}
	for (i = 0; i < n; i++) {									//����ڽӾ����е�ÿ��Ԫ�� 
		for (j = n - 1; j >= 0; j--) {
			if (A[i][j] != 0) {									//����һ���� 
				p = (EdgeNode*)malloc(sizeof(EdgeNode));		//����һ������ڴ�
				p->adjVer = j;									//����ڽӵ� 
				p->weight = A[i][j];							//���Ȩֵ
				p->nextEdge = NULL;

				p->nextEdge = LG->adjList[i].firstEdge;			//ͷ�巨 
				LG->adjList[i].firstEdge = p;
			}
		}
	}
	LG->n = n;
	LG->e = e;
}

//����ڽӱ� 
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

//����ڽӾ���
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
				printf("%4s", "��");
			}
			else {
				printf("%4d", MG.adjMat[i][j]);
			}
		}
		printf("\n");
	}
}

//�ڽӱ�ת��Ϊ�ڽӾ���
void ListToMat(ListGraph* LG, MatGraph &MG) {
	int i, j;
	EdgeNode* p;
	for (i = 0; i < MAXV; i++) {					//��ʼ���� 0
		for (j = 0; j < MAXV; j++) {
			MG.adjMat[i][j] = 0;
		}
	}
	for (i = 0; i < LG->n; i++) {					//ɨ�����е�����
		p = LG->adjList[i].firstEdge;				//p ָ��� i ���������ͷ���
		while (p != NULL) {							//����������
			MG.adjMat[i][p->adjVer] = p->weight;
			p = p->nextEdge;
		}
	}
	MG.n = LG->n;
	MG.e = LG->e;
}

//�ڽӾ���ת��Ϊ�ڽӱ� 
void MatToList(MatGraph MG, ListGraph* &LG) {
	int i, j;
	EdgeNode* p;
	LG = (ListGraph*)malloc(sizeof(ListGraph));
	for (i = 0; i < MG.n; i++) {
		LG->adjList[i].firstEdge = NULL;						//���ڽӱ�������ͷ���ָ�����ó�ֵ 
	}
	for (i = 0; i < MG.n; i++) {								//����ڽӾ����е�ÿ��Ԫ�� 
		for (j = MG.n - 1; j >= 0; j--) {
			if (MG.adjMat[i][j] != 0) {							//����һ���� 
				p = (EdgeNode*)malloc(sizeof(EdgeNode));		//����һ������ڴ�
				p->adjVer = j;									//����ڽӵ� 
				p->weight = MG.adjMat[i][j];					//���Ȩֵ
				p->nextEdge = NULL;

				p->nextEdge = LG->adjList[i].firstEdge;			//ͷ�巨 
				LG->adjList[i].firstEdge = p;
			}
		}
	}
	LG->n = MG.n;
	LG->e = MG.e;
}

//����ͼ
void destroyAdjListGraph(ListGraph* LG) {
	int i;
	EdgeNode* pre, * p;
	for (i = 0; i < LG->n; i++) {
		pre = LG->adjList[i].firstEdge;				//�����ͷ��ڴ� 
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
	ListGraph* LG;						//�ڽӱ� 
	MatGraph MG;						//�ڽӾ��� 
	int array1[MAXV][MAXV] = {			//����Ȩ����ͼ 
		{0,1,0,1,1},
		{1,0,1,1,0},
		{0,1,0,1,1},
		{1,1,1,0,1},
		{1,0,1,1,0}
	};
	int array2[MAXV][MAXV] = {			//����Ȩ����ͼ 
		{0,1,0,1,0},
		{0,0,1,1,0},
		{0,0,0,1,1},
		{0,0,0,0,0},
		{1,0,0,1,0}
	};
	int array3[MAXV][MAXV] = {			//��Ȩ����ͼ 
		{  0,  8,INF,  5,INF},
		{  8,  0,  3,INF,INF},
		{INF,  3,  0,  9,  6},
		{  5,INF,  9,  0,INF},
		{INF,INF,  6,INF,  0}
	};
	int array4[MAXV][MAXV] = {			//��Ȩ����ͼ 
		{  0,  8,INF,  5,INF},
		{INF,  0,  3,INF,INF},
		{INF,INF,  0,INF,  6},
		{INF,INF,  9,  0,INF},
		{INF,INF,INF,INF,  0}
	};
	int e = 5;
	createAdjListGraph(LG, array4, MAXV, e);		//�����ڽӱ�ͼ 
	
	printf("�ڽӱ�Ϊ��\n");
	displayAdjList(LG);								//����ڽӱ�
	printf("\n");

	ListToMat(LG, MG);								//�ڽӱ�ת��Ϊ�ڽӾ���
	printf("�ڽӾ���Ϊ��\n");
	displayAdjMat(MG);								//����ڽӾ��� 
	printf("\n");

	MatToList(MG, LG);								//�ڽӾ���ת��Ϊ�ڽӱ�
	printf("�ڽӱ�Ϊ��\n");
	displayAdjList(LG);								//����ڽӱ� 
	printf("\n");

	return 0;
}
