#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define Elemtype	int			//宏定义类型，后期便于修改
#define CODE_SIZE	64			//至少是 2*N-1
#define BUFF_SIZE	1024		//输入字符串缓冲区
#define SPACE_SIZE	1024		//画树的缓冲区

typedef struct node {			//定义哈夫曼结点类型 
	char data;					//结点值 
	Elemtype weight;			//权重 
	struct node* parent;		//父结点 （最后发现好像没用到）
	struct node* lchild;		//左孩子结点 
	struct node* rchild;		//右孩子结点 
}HTNode;

typedef struct code {
	char data;					//结点值 
	char cd[CODE_SIZE];			//存放的哈夫曼码 
}HCode;

HTNode** input(int n);												//输入信息
HTNode* newNode(char data, Elemtype weight);						//创建初始化新结点
void BubbleSort(HTNode** HT, int start, int end);					//冒泡排序
void createHT(HTNode** HT, int n);									//创建哈夫曼树
void draw_level(HTNode* root, bool lchild, char* str);				//画左右子树
void draw(HTNode* root);											//画根节点
int createHC(HTNode* HT, HCode* HC, char array[], int n, int m);	//创建哈夫曼码
void showHC(HCode* HC, int n);										//显示哈夫曼码
void encode(HCode* HC, int n, char* str, char* binary);				//加密
int compare(HCode* HC, int n, char* str);							//二进制串比较
void decode(HCode* HC, int n, char* binary, char* str);				//解密

int main() {
	//例子：8
	//A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10
	HTNode** HT = (HTNode**)malloc(sizeof(HTNode*) * CODE_SIZE);
	HCode* HC = (HCode*)malloc(sizeof(HCode) * CODE_SIZE);
	char* str = (char*)malloc(sizeof(char) * BUFF_SIZE);
	char* binary = (char*)malloc(sizeof(char) * BUFF_SIZE * 4);
	char array[CODE_SIZE];
	int n = 0;
	memset(array, 0, CODE_SIZE);
	memset(binary, 0, BUFF_SIZE * 4);

	printf("请输入哈夫曼叶子结点：");
	scanf("%d", &n);
	HT = input(n);
	createHT(HT, n);
	draw(HT[2 * n - 2]);
	createHC(HT[2 * n - 2], HC, array, 0, 0);
	showHC(HC, n);
	printf("请输入编码的字符串：");
	scanf("%s", str);
	encode(HC, n, str, binary);
	printf("哈夫曼编码为：%s\n", binary);
	memset(str, 0, BUFF_SIZE);
	decode(HC, n, binary, str);
	printf("哈夫曼译码为：%s\n", str);

	return 0;
}

void decode(HCode* HC, int n, char* binary, char* str) {
	int len = strlen(binary);
	char* tmp = (char*)malloc(sizeof(char) * CODE_SIZE);
	int size = 1;		//比较长度
	int ret = 0;		//返回值
	int pos = 0;		//偏移（下标）
	int index = 0;		//下标
	while (pos < len) {
		memset(tmp, 0, CODE_SIZE);
		strncpy(tmp, binary + pos, size);
		//printf("%s\n", tmp);
		ret = compare(HC, n, tmp);
		if (ret < 0) {
			size++;
		}
		else {
			pos += size;
			size = 1;
			str[index] = HC[ret].data;
			index++;
		}
	}
	str[strlen(str)] = '\0';
}

int compare(HCode* HC, int n, char* str) {
	for (int i = 0; i < n; i++) {
		if (strcmp(HC[i].cd, str) == 0) {
			return i;
		}
	}
	return -1;
}

void encode(HCode* HC, int n, char* str, char* binary) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		/*
		* 这里可以加个判断跳过空格
		*/
		for (int j = 0; j < n; j++) {
			if (str[i] == HC[j].data) {
				strncat(binary, HC[j].cd, strlen(HC[j].cd));
			}
		}
	}
	binary[strlen(binary)] = '\0';
}

void showHC(HCode* HC, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c----", HC[i].data);
		for (int j = 0; j < strlen(HC[i].cd); j++) {
			printf("%c", HC[i].cd[j]);
		}
		printf("\n");
	}
}

/*****************************************************************************
* @data  : 2020/5/22
* @brief : 创建哈夫曼码
* @param :
*   HT : 哈夫曼树根节点
*   HC : 存放哈夫曼码指针
*   array : 通用暂时存放哈夫曼码（截断）
*   n : 传递下标
*   m : 回溯树高（层次）
* @return:
*   n : 第 n 个字母
*****************************************************************************/
int createHC(HTNode* HT, HCode* HC, char array[], int n, int m) {
	if (HT->data != '#') {
		HC[n].data = HT->data;
		array[m] = '\0';
		memcpy(HC[n].cd, array, CODE_SIZE);
		n++;
	}
	if (HT->lchild != NULL) {
		array[m] = '0';
		n = createHC(HT->lchild, HC, array, n, m + 1);
	}
	if (HT->rchild != NULL) {
		array[m] = '1';
		n = createHC(HT->rchild, HC, array, n, m + 1);
	}
	return n;
}

void draw_level(HTNode* root, bool lchild, char* str) {
	if (root->rchild) {
		draw_level(root->rchild, false, strcat(str, (lchild ? "|     " : "      ")));
	}
	printf("%s", str);
	printf("%c", (lchild ? '\\' : '/'));
	printf("-----");

	printf("%c ", root->data);
	printf("%d\n", root->weight);
	if (root->lchild) {
		draw_level(root->lchild, true, strcat(str, (lchild ? "      " : "|     ")));
	}
	//"|     " 的长度
	str[strlen(str) - 6] = '\0';
}

void draw(HTNode* root) {
	char str[SPACE_SIZE];
	memset(str, '\0', SPACE_SIZE);
	if (root == NULL) {
		return;
	}
	if (root->rchild) {
		draw_level(root->rchild, false, str);
	}
	printf("%c ", root->data);
	printf("%d\n", root->weight);
	if (root->lchild) {
		draw_level(root->lchild, true, str);
	}
	printf("\n");
}

/*****************************************************************************
* @data  : 2020/5/22
* @brief : 创建哈夫曼树（二级指针）
* @param :
*   HT : 哈夫曼树
*   n  : 字母个数
*****************************************************************************/
void createHT(HTNode** HT, int n) {
	int start = 0;		//记录未创建（未排序）的下标
	int end = n;		//记录生成的新数据
	char data;			//字母
	Elemtype weight;	//保存合并后的权重

	while (end - start > 1) {
		BubbleSort(HT, start, end);
		data = '#';
		weight = HT[start]->weight + HT[start + 1]->weight;
		HT[end] = newNode(data, weight);
		HT[end]->lchild = HT[start];
		HT[end]->rchild = HT[start + 1];
		HT[start]->parent = HT[end];
		HT[start + 1]->parent = HT[end];

		start += 2;
		end++;
	}
	//printf("index\tdata\tweight\n");
	//for (int i = 0; i < 2 * n - 1; i++) {		//各种属性，输出看一看，有没有问题 
	//	printf("%5d\t", i);
	//	printf("%4c\t", HT[i]->data);
	//	printf("%6d\n", HT[i]->weight);
	//}
}

void BubbleSort(HTNode** HT, int start, int end) {
	for (int i = start; i < end - 1; i++) {
		for (int j = end - 1; j > i; j--) {
			if (HT[j]->weight < HT[j - 1]->weight) {
				HTNode* node;
				node = HT[j - 1];
				HT[j - 1] = HT[j];
				HT[j] = node;
			}
		}
	}
}

HTNode* newNode(char data, Elemtype weight) {
	HTNode* node = (HTNode*)malloc(sizeof(HTNode));
	node->data = data;
	node->weight = weight;
	node->parent = NULL;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}

HTNode** input(int n) {
	int i = 0;
	char data;
	Elemtype weight;
	char dataArray[CODE_SIZE];
	Elemtype weightArray[CODE_SIZE];
	HTNode** node = (HTNode**)malloc(sizeof(HTNode*) * CODE_SIZE);

	printf("请输入结点和权值(例如A 1)：\n");     //规律，总结点个数为叶子结点两倍减一，2*N-1 
	while (i / 2 < n) {							//scanf 读取空格截止
		scanf("%c %d", &data, &weight);  		//所以输入两个，循环两次，所以除以 2
		dataArray[i / 2] = data;
		weightArray[i / 2] = weight;
		i++;
	}
	for (int j = 0; j < n; j++) {
		node[j] = newNode(dataArray[j], weightArray[j]);
	}
	return node;
}
