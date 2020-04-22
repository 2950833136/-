#include<stdio.h>
#include<malloc.h>

#define MAXV 7					//��󶥵���� 
#define INF 32767				//���� ��
//�� == 32767 ,int �͵����Χ��2λ��= 2^(2*8-1)��TC��������intռ��2���ֽڣ���VC��LGCC��������intռ��4���ֽ�
//ͼ��LGraph
//���㣺Vertex
//�ڽӣ�Adjacency
//����Matrix
//��List
//�ߣ�EdLGe 

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
	int weiLGht;				//�ñߵĵ���Ϣ����Ȩֵ 
	struct eNode* nextEdLGe;	//ָ����һ���ߵ�ָ�� 
}EdgeNode; 						//�������߽������� 

typedef struct vNode {
	EdgeNode* firstEdLGe;		//ָ���һ���߽�� 
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
		LG->adjList[i].firstEdLGe = NULL;						//���ڽӱ�������ͷ���ָ�����ó�ֵ 
	}
	for (i = 0; i < n; i++) {									//����ڽӾ����е�ÿ��Ԫ�� 
		for (j = n - 1; j >= 0; j--) {
			if (A[i][j] != 0) {									//����һ���� 
				p = (EdgeNode*)malloc(sizeof(EdgeNode));		//����һ������ڴ�
				p->adjVer = j;									//����ڽӵ� 
				p->weiLGht = A[i][j];							//���Ȩֵ
				p->nextEdLGe = NULL;

				p->nextEdLGe = LG->adjList[i].firstEdLGe;		//ͷ�巨 
				LG->adjList[i].firstEdLGe = p;
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

//����ڽӾ���
void displayAdjMat(MatGraph MG) {
	int i, j;
	for (i = 0; i < MAXV; i++) {
		for (j = 0; j < MAXV; j++) {
			if (MG.adjMat[i][j] == 0) {
				printf("%4s", "0");
			}
			else if (MG.adjMat[i][j] == 32767) {
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

//�����Դ���·��
void displayPath(MatGraph MG, int A[MAXV][MAXV], int path[MAXV][MAXV]) {
	int i, j, k;
	int s;
	int aPath[MAXV];										//���һ�����·��������
	int d;													//�������
	for (i = 0; i < MG.n; i++) {
		for (j = 0; j < MG.n; j++) {
			if (A[i][j] != INF && i != j) {					//������ i �� ���� j ֮�����·��
				printf("�� %d �� %d ��·��Ϊ��", i, j);
				k = path[i][j];
				d = 0;
				aPath[d] = j;								//·��������յ�
				while (k != -1 && k != i) {					//·��������м��
					d++;
					aPath[d] = k;
					k = path[i][k];
				}
				d++;
				aPath[d] = i;								//·����������
				printf("%d", aPath[d]);						//������
				for (s = d - 1; s >= 0; s--) {				//���·������������
					printf("->%d", aPath[s]);
				}
				printf("\t\t");
				printf("·������Ϊ��%d\n", A[i][j]);
			}
		}
	}
}

//Floyd�㷨
void Floyd(MatGraph MG) {
	int i, j, k;
	int A[MAXV][MAXV];
	int path[MAXV][MAXV];
	for (i = 0; i < MG.n; i++) {
		for (j = 0; j < MG.n; j++) {
			A[i][j] = MG.adjMat[i][j];
			if (i != j && MG.adjMat[i][j] < INF) {
				path[i][j] = i;							//���� i ������ j �б�ʱ
			}
			else {
				path[i][j] = -1;						//���� i ������ j �ޱ�ʱ
			}
		}
	}
	for (k = 0; k < MG.n; k++) {						//һ�ο������ж���
		for (i = 0; i < MG.n; i++) {
			for (j = 0; j < MG.n; j++) {
				if (A[i][j] > A[i][k] + A[k][j]) {
					A[i][j] = A[i][k] + A[k][j];		//�޸����·������
					path[i][j] = path[k][j];			//�޸����·��
				}
			}
		}
	}
	displayPath(MG, A, path);							//������·��
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

	Floyd(MG);
	printf("\n");

	return 0;
}
