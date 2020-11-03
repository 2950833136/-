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
void createAdjListGraph(ListGraph* &LG, int A[MAXV][MAXV], int n, int e) {
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
void displayAdjMat(MatGraph LG) {
	int i, j;
	for (i = 0; i < MAXV; i++) {
		for (j = 0; j < MAXV; j++) {
			if (LG.adjMat[i][j] == 0) {
				printf("%4s", "0");
			}
			else if (LG.adjMat[i][j] == 32767) {
				printf("%4s", "��");
			}
			else {
				printf("%4d", LG.adjMat[i][j]);
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
void displayPath(MatGraph LG, int dist[], int path[], int S[], int v) {
	int i, j, k;
	int aPath[MAXV];								//���һ�����·��������
	int d;											//�������
	for (i = 0; i < LG.n; i++) {					//ѭ������Ӷ��� v �� i ��·��
		if (S[i] == 1 && i != v) {
			printf("�Ӷ��� %d ������ %d ��·������Ϊ��%d\t ·��Ϊ:", v, i, dist[i]);
			d = 0;
			aPath[d] = i;							//���·���ϵ��յ�
			k = path[i];
			if (k == -1) {							//û��·��
				printf("��·��\n");
			}
			else {									//����·�������
				while (k != v) {
					d++;
					aPath[d] = k;
					k = path[k];
				}
				d++;
				aPath[d] = v;						//���·���ϵ����
				printf("%d ", aPath[d]);			//������
				for (j = d - 1; j >= 0; j--) {		//�����������
					printf("%d ", aPath[j]);
				}
				printf("\n");
			}
		}
	}
}

//Dijkstra�㷨
void Dijkstra(MatGraph LG, int v) {
	int dist[MAXV];									//�洢Ȩֵ
	int path[MAXV];									//�Ƿ���·��
	int S[MAXV];									//S[i]==0��ʾ���� i ��S��, S[i]==1 ��ʾ ���� i �� U ��
	int MinDis;										//��С��Ȩֵ
	int u = 0;										//��¼���·���Ķ���
	int i, j;
	for (i = 0; i < LG.n; i++) {
		dist[i] = LG.adjMat[v][i];					//�����ʼ��
		S[i] = 0;									//S[] ��ʼ��
		if (LG.adjMat[v][i] < 32767) {				//·����ʼ��
			path[i] = v;							//���� v ������ i �б�ʱ���ö��� i ��ǰһ������Ϊ v
		}
		else {
			path[i] = -1;							//���� v ������ i �ޱ�ʱ���ö��� i ��ǰһ������Ϊ -1
		}
	}
	S[v] = 1;										//Դ���� v ���� S
	path[v] = 0;									
	for (i = 0; i < LG.n - 1; i++) {				//ѭ���� v �����ж�������·��
		MinDis = INF;								//����󳤶ȳ�ֵ
		for (j = 0; j < LG.n; j++) {
			if (S[j] == 0 && dist[j] < MinDis) {	//ѡȡ���� S �У��� U �У��Ҿ���·�����ȵĶ��� u
				u = j;
				MinDis = dist[j];					//�õ����㡢·������
			}
		}
		S[u] = 1;									//���� u ���� S
		for (j = 0; j < LG.n; j++) {				//�޸����·��
			if (S[j] == 0) {
				if (LG.adjMat[u][j] < INF && dist[u] + LG.adjMat[u][j] < dist[j]) {
					dist[j] = dist[u] + LG.adjMat[u][j];
					path[j] = u;
				}
			}
		}
	}
	displayPath(LG, dist, path, S, v);				//������·��
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
