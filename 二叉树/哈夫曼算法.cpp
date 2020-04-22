#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX_SIZE	64

typedef struct node {			//定义哈夫曼结点类型 
	char data;					//结点值 
	int weight;					//权重 
	int parent;					//父结点 
	int lchild;					//左孩子结点 
	int rchild;					//右孩子结点 
}HTNode;

typedef struct code {
	char cd[MAX_SIZE];			//存放的哈夫曼码 
	int start;					//记录cd[]编译哈夫曼码的起始位置 
}HCode;

//创建哈夫曼树 
void createHT(HTNode HT[], int n) {
	int i, k;
	int lnode, rnode;
	double min1, min2;
	for (i = 0; i < 2 * n - 1; i++) {						//所有结点的相关域值初值 -1 
		HT[i].parent = HT[i].lchild = HT[i].rchild = -1;
	}
	for (i = n; i <= 2 * n - 2; i++) {
		min1 = min2 = 32767;
		lnode = rnode = -1;
		for (k = 0; k <= i - 1; k++) {
			if (HT[k].parent == -1) {						//只在尚未构造二叉树中查找 
				if (HT[k].weight < min1) {					//权重比左边小 
					min2 = min1;							//保证左边的最小 
					rnode = lnode;
					min1 = HT[k].weight;					//记录权重 
					lnode = k;								//记录下标 
				}
				else if (HT[k].weight < min2) {				//权重比右边小 
					min2 = HT[k].weight;
					rnode = k;
				}
			}
		}
		HT[i].weight = HT[lnode].weight + HT[rnode].weight;	//合并后的权重 
		HT[i].lchild = lnode;								//HT[i]作为父结点 
		HT[i].rchild = rnode;
		HT[lnode].parent = i;
		HT[rnode].parent = i;
	}
}

//哈夫曼编码
void createHCode(HTNode HT[], HCode HC[], int n) {
	int f;													//父结点 
	int c;
	HCode hc;
	for (int i = 0; i < n; i++) {
		hc.start = n;										//开始位置,倒叙插入 
		c = i;												//初始
		f = HT[i].parent;									//f 保存该结点父结点 
		while (f != -1) {									//因为创建哈夫曼树时，所有无关都置 -1，所以根结点父结点为 -1，表示结束 
			if (HT[f].lchild == c) {						//左边就压入 0 
				hc.cd[hc.start] = 0;
				hc.start--;
			}
			if (HT[f].rchild == c) {						//右边就压入 1 
				hc.cd[hc.start] = 1;
				hc.start--;
			}
			c = f;											//此时父结点当作子结点 
			f = HT[f].parent;								//向上遍历，父结点进行同样操作
		}
		hc.start++;											//记录哈夫曼编码最开始的字符位置 
		HC[i] = hc;											//一个哈夫曼结点的编码 
	}
}

int main() {
	//例子：8
	//A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10
	printf("请输入哈夫曼叶子结点：");
	int N;													//叶子结点个数 
	scanf("%d", &N);
	HTNode HT[MAX_SIZE];
	int n = 0;
	char data;
	int weight;
	printf("请输入结点和权值(例如A 1)：\n");				//规律，总结点个数为叶子结点两倍减一，2*N-1 
	while (n / 2 < N) {										//这儿有点坑，不知道为什么 scanf 输入一个循环一次 
		scanf("%c %d", &data, &weight);  					//所以输入两个，循环两次，所以除以 2 
		HT[n / 2].data = data;
		HT[n / 2].weight = weight;
		n++;
	}

	createHT(HT, N);
	printf("创建成功\n");
	for (int i = 0; i < 2 * N - 1; i++) {					//各种属性，输出看一看，有没有问题 
		printf("%2d  ", i);
		printf("%3d ", HT[i].weight);
		printf("%2d ", HT[i].parent);
		printf("%2d ", HT[i].lchild);
		printf("%2d \n", HT[i].rchild);
	}
	printf("\n");

	HCode HC[MAX_SIZE];
	createHCode(HT, HC, N);
	printf("编码成功\n");
	for (int i = 0; i < N; i++) {							//外循环输出每个哈夫曼编码 
		printf("%c——", HT[i].data);
		for (int j = HC[i].start; j <= N; j++) {			//内循环输出哈夫曼编码，HC[i].start 编码起始位置 
			printf("%d", HC[i].cd[j]);
		}
		printf("\n");
	}

	return 0;
}
