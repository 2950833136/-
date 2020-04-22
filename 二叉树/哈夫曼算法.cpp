#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX_SIZE	64

typedef struct node {			//���������������� 
	char data;					//���ֵ 
	int weight;					//Ȩ�� 
	int parent;					//����� 
	int lchild;					//���ӽ�� 
	int rchild;					//�Һ��ӽ�� 
}HTNode;

typedef struct code {
	char cd[MAX_SIZE];			//��ŵĹ������� 
	int start;					//��¼cd[]��������������ʼλ�� 
}HCode;

//������������ 
void createHT(HTNode HT[], int n) {
	int i, k;
	int lnode, rnode;
	double min1, min2;
	for (i = 0; i < 2 * n - 1; i++) {						//���н��������ֵ��ֵ -1 
		HT[i].parent = HT[i].lchild = HT[i].rchild = -1;
	}
	for (i = n; i <= 2 * n - 2; i++) {
		min1 = min2 = 32767;
		lnode = rnode = -1;
		for (k = 0; k <= i - 1; k++) {
			if (HT[k].parent == -1) {						//ֻ����δ����������в��� 
				if (HT[k].weight < min1) {					//Ȩ�ر����С 
					min2 = min1;							//��֤��ߵ���С 
					rnode = lnode;
					min1 = HT[k].weight;					//��¼Ȩ�� 
					lnode = k;								//��¼�±� 
				}
				else if (HT[k].weight < min2) {				//Ȩ�ر��ұ�С 
					min2 = HT[k].weight;
					rnode = k;
				}
			}
		}
		HT[i].weight = HT[lnode].weight + HT[rnode].weight;	//�ϲ����Ȩ�� 
		HT[i].lchild = lnode;								//HT[i]��Ϊ����� 
		HT[i].rchild = rnode;
		HT[lnode].parent = i;
		HT[rnode].parent = i;
	}
}

//����������
void createHCode(HTNode HT[], HCode HC[], int n) {
	int f;													//����� 
	int c;
	HCode hc;
	for (int i = 0; i < n; i++) {
		hc.start = n;										//��ʼλ��,������� 
		c = i;												//��ʼ
		f = HT[i].parent;									//f ����ý�㸸��� 
		while (f != -1) {									//��Ϊ������������ʱ�������޹ض��� -1�����Ը���㸸���Ϊ -1����ʾ���� 
			if (HT[f].lchild == c) {						//��߾�ѹ�� 0 
				hc.cd[hc.start] = 0;
				hc.start--;
			}
			if (HT[f].rchild == c) {						//�ұ߾�ѹ�� 1 
				hc.cd[hc.start] = 1;
				hc.start--;
			}
			c = f;											//��ʱ����㵱���ӽ�� 
			f = HT[f].parent;								//���ϱ�������������ͬ������
		}
		hc.start++;											//��¼�����������ʼ���ַ�λ�� 
		HC[i] = hc;											//һ�����������ı��� 
	}
}

int main() {
	//���ӣ�8
	//A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10
	printf("�����������Ҷ�ӽ�㣺");
	int N;													//Ҷ�ӽ����� 
	scanf("%d", &N);
	HTNode HT[MAX_SIZE];
	int n = 0;
	char data;
	int weight;
	printf("���������Ȩֵ(����A 1)��\n");				//���ɣ��ܽ�����ΪҶ�ӽ��������һ��2*N-1 
	while (n / 2 < N) {										//����е�ӣ���֪��Ϊʲô scanf ����һ��ѭ��һ�� 
		scanf("%c %d", &data, &weight);  					//��������������ѭ�����Σ����Գ��� 2 
		HT[n / 2].data = data;
		HT[n / 2].weight = weight;
		n++;
	}

	createHT(HT, N);
	printf("�����ɹ�\n");
	for (int i = 0; i < 2 * N - 1; i++) {					//�������ԣ������һ������û������ 
		printf("%2d  ", i);
		printf("%3d ", HT[i].weight);
		printf("%2d ", HT[i].parent);
		printf("%2d ", HT[i].lchild);
		printf("%2d \n", HT[i].rchild);
	}
	printf("\n");

	HCode HC[MAX_SIZE];
	createHCode(HT, HC, N);
	printf("����ɹ�\n");
	for (int i = 0; i < N; i++) {							//��ѭ�����ÿ������������ 
		printf("%c����", HT[i].data);
		for (int j = HC[i].start; j <= N; j++) {			//��ѭ��������������룬HC[i].start ������ʼλ�� 
			printf("%d", HC[i].cd[j]);
		}
		printf("\n");
	}

	return 0;
}
