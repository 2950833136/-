# 哈夫曼

## 1、简介

#### 1.1 哈夫曼树定义

​	哈夫曼树又称最优二叉树，是一种带权路径长度最短的二叉树。所谓树的带权路径长度，就是树中所有的叶结点的权值乘上其到根结点的路径长度（若根结点为0层，叶结点到根结点的路径长度为叶结点的层数）。

#### 1.2 树的带权路径长度

树的带权路径长度记为：
$$
WPL=(W_{1}*L_{1}+W_{2}*L_{2}+W_{3}*L_{3}+...+W_{n}*L_{n})
$$

其中：W 是权重，L  是路径长度（叶子结点到根节点距离）。

N 个权值 Wi(i=1,2,...n) 构成一棵有 N 个叶结点的二叉树，相应的叶结点的路径长度为 Li(i=1,2,...n)。



## 2、哈夫曼树

#### 2.1 例子

下图是编辑好的哈夫曼树：
例子：**A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10**
代表数据和权值，哈夫曼树就是要使WPL最小。
$$
WPL=2*4+3*4+6*3+7*3+10*3+19*2+21*2+32*2
$$

1. **圆圈是初始数据和初始权值，正方形是计算合并后的权值**
2. **根节点为0，每层依次加一**

![在这里插入图片描述](https://img-blog.csdnimg.cn/2019061711213267.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEwOTAxMg==,size_16,color_FFFFFF,t_70)

#### 2.2 哈夫曼算法原理

那么又是怎么计算出来的呢？

**其实很简单，就是在节点数组中查找到最小的两个节点，以此为左、右节点生成父节点，在节点数组中排除这两个节点，将新生成的父节点加入节点数组，依次循环，直到节点数组中只剩一个节点。**

```c
1. 为每个字符建立一个叶子节点，并加上其相应的发生频率
2. 当有一个以上的节点存在时，进行下列循环
   2.1. 把这些节点作为带权值的二叉树的根节点，左右子树为空
   2.2. 选择两棵根结点权值最小的树作为左右子树构造一棵新的二叉树，且至新的二叉树的根结点的权值为其左右子树上根结点的权值之和
   2.3. 把权值最小的两个根节点移除
   2.4. 将新的节点加入队列中
3. 最后剩下的节点即为根节点，此时二叉树已经完成
```



## 3、哈夫曼编码

哈夫曼编码可用于构造最短代码长度方案。在数据通信中，经常需要将传送的的文字转换为二进制字符0、1，组成的二进制字符串，该过程称为编码。

**哈夫曼编码就是使用哈夫曼二叉树，左节点为0，右节点为1，最后得到该位置的01路径。
哈夫曼编码的实质就是使用次数越多的字符采用的编码越短。**
例如：上图

```c
A——1010
B——00
C——10000
D——1001
E——11
F——10001
G——01
H——1011
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190617112151756.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEwOTAxMg==,size_16,color_FFFFFF,t_70)



## 4、代码实现

#### 4.1 基本函数

```c
// 创建哈夫曼树 
void createHT(HTNode HT[],int n)
// 哈夫曼编码
void createHCode(HTNode HT[],HCode HC[],int n)
// 主函数
int main()
```

#### 4.2 结构体
**（1）哈夫曼树结构体**
权重可以改类型，一般统计频率用float、double，统计次数用int。

```c
typedef struct node{			// 定义哈夫曼结点类型 
	char data;					// 结点值 
	int weight;					// 权重 
	int parent;					// 父结点 
	int lchild;					// 左孩子结点 
	int rchild;					// 右孩子结点 
}HTNode;
```

**（2）哈夫曼编码结构体**

```c
typedef struct code{
	char cd[256];				// 存放的哈夫曼码 
	int start;					// 记录cd[]编译哈夫曼码的起始位置 
}HCode;
```

#### 4.3 全部代码

```c
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX_SIZE	64

typedef struct node {			// 定义哈夫曼结点类型 
	char data;					// 结点值 
	int weight;					// 权重 
	int parent;					// 父结点 
	int lchild;					// 左孩子结点 
	int rchild;					// 右孩子结点 
}HTNode;

typedef struct code {
	char cd[MAX_SIZE];			// 存放的哈夫曼码 
	int start;					// 记录cd[]编译哈夫曼码的起始位置 
}HCode;

// 创建哈夫曼树 
void createHT(HTNode HT[], int n) {
	int i, k;
	int lnode, rnode;
	double min1, min2;
	for (i = 0; i < 2 * n - 1; i++) {						// 所有结点的相关域值初值 -1 
		HT[i].parent = HT[i].lchild = HT[i].rchild = -1;
	}
	for (i = n; i <= 2 * n - 2; i++) {
		min1 = min2 = 32767;
		lnode = rnode = -1;
		for (k = 0; k <= i - 1; k++) {
			if (HT[k].parent == -1) {						// 只在尚未构造二叉树中查找 
				if (HT[k].weight < min1) {					// 权重比左边小 
					min2 = min1;							// 保证左边的最小 
					rnode = lnode;
					min1 = HT[k].weight;					// 记录权重 
					lnode = k;								// 记录下标 
				}
				else if (HT[k].weight < min2) {				// 权重比右边小 
					min2 = HT[k].weight;
					rnode = k;
				}
			}
		}
		HT[i].weight = HT[lnode].weight + HT[rnode].weight;	// 合并后的权重 
		HT[i].lchild = lnode;								// HT[i]作为父结点 
		HT[i].rchild = rnode;
		HT[lnode].parent = i;
		HT[rnode].parent = i;
	}
}

// 哈夫曼编码
void createHCode(HTNode HT[], HCode HC[], int n) {
	int f;													// 父结点 
	int c;
	HCode hc;
	for (int i = 0; i < n; i++) {
		hc.start = n;										// 开始位置,倒叙插入 
		c = i;												// 初始
		f = HT[i].parent;									// f 保存该结点父结点 
		while (f != -1) {									// 因为创建哈夫曼树时，所有无关都置 -1，所以根结点父结点为 -1，表示结束 
			if (HT[f].lchild == c) {						// 左边就压入 0 
				hc.cd[hc.start] = 0;
				hc.start--;
			}
			if (HT[f].rchild == c) {						// 右边就压入 1 
				hc.cd[hc.start] = 1;
				hc.start--;
			}
			c = f;											// 此时父结点当作子结点 
			f = HT[f].parent;								// 向上遍历，父结点进行同样操作
		}
		hc.start++;											// 记录哈夫曼编码最开始的字符位置 
		HC[i] = hc;											// 一个哈夫曼结点的编码 
	}
}

int main() {
	// 例子：8
	// A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10
	printf("请输入哈夫曼叶子结点：");
	int N;													// 叶子结点个数 
	scanf("%d", &N);
	HTNode HT[MAX_SIZE];
	int n = 0;
	char data;
	int weight;
	printf("请输入结点和权值(例如A 1)：\n");					 // 规律，总结点个数为叶子结点两倍减一，2*N-1 
	while (n / 2 < N) {										// scanf 空格截至 
		scanf("%c %d", &data, &weight);  					// 所以输入两个，循环两次，所以除以 2 
		HT[n / 2].data = data;
		HT[n / 2].weight = weight;
		n++;
	}

	createHT(HT, N);
	printf("创建成功\n");
	for (int i = 0; i < 2 * N - 1; i++) {					//  各种属性，输出看一看，有没有问题 
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
	for (int i = 0; i < N; i++) {							// 外循环输出每个哈夫曼编码 
		printf("%c——", HT[i].data);
		for (int j = HC[i].start; j <= N; j++) {			// 内循环输出哈夫曼编码，HC[i].start 编码起始位置 
			printf("%d", HC[i].cd[j]);
		}
		printf("\n");
	}

	return 0;
}
```



## 5、运行结果

例子：8
A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10
（可以一对一对的输入，也可以一次全部输入）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190616225521895.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEwOTAxMg==,size_16,color_FFFFFF,t_70)



## 6、更新（2020/5/22）

上述仅仅实现哈夫曼编码构造，然而大部分都需要加密解密，所以重新编写了哈夫曼算法。

1. 实现哈夫曼编码解码
2. 实现将哈夫曼数画出来
3. 哈夫曼编码记录，然后排序，能够更快进行比较
4. 实现手打输入字符和权重；实现默认字符和权重，输入字符串编码解码；实现读取文件将文件编码解码

#### 6.1 手动输入

使用的 scanf() 输入，空格为分隔符。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200615211035837.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEwOTAxMg==,size_16,color_FFFFFF,t_70)



#### 6.2 默认字符和权重

```c
char     dataArray[CODE_SIZE]   = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ',', ' '};
Elemtype weightArray[CODE_SIZE] = {819, 147, 383, 391, 1225, 225, 171, 457, 710, 14, 41, 377, 334, 706, 726, 289, 9, 685, 636, 941, 258, 109, 159, 21, 158, 8, 50, 50};
*n                              = 28;
```



![](https://img-blog.csdnimg.cn/20201031222739527.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEwOTAxMg==,size_16,color_FFFFFF,t_70#pic_center)



#### 6.3  文件读取

直接读取文件将文件编码解码，读取文件得到每个字符出现次数，hash 表计算。



![](https://img-blog.csdnimg.cn/20201031222806854.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEwOTAxMg==,size_16,color_FFFFFF,t_70#pic_center)



#### 6.4 全部代码


```cpp
#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define Elemtype   int    // 定义类型，后期便于修改
#define CODE_SIZE  256    // 至少是 2*N-1
#define BUFF_SIZE  102400 // 输入字符串缓冲区
#define SPACE_SIZE 1024   // 画树的缓冲区

// 定义哈夫曼结点类型
typedef struct _Huffman_Tree_Node {
    char                       data;   // 结点值
    Elemtype                   weight; // 权重
    struct _Huffman_Tree_Node* lchild; // 左孩子结点
    struct _Huffman_Tree_Node* rchild; // 右孩子结点
} HTNode;

// 定义哈夫曼编码类型
typedef struct _Huffman_Code {
    char data;          // 结点值
    char cd[CODE_SIZE]; // 存放的哈夫曼码
} HCode;

void    inputHand(HTNode** HT, int* n);                             // 手动输入信息
void    inputDefault(HTNode** HT, int* n);                          // 默认输入信息，英文数组
void    inputFile(HTNode** HT, int* n, char* str);                  // 读取文件获得信息
HTNode* newNode(char data, Elemtype weight);                        // 创建初始化新结点
void    nodeSort(HTNode** HT, int start, int end);                  // 排序节点，找到最小的两个节点
void    createHT(HTNode** HT, int n);                               // 创建哈夫曼树
void    draw_level(HTNode* root, bool lchild, char* str);           // 画左右子树
void    draw(HTNode* root);                                         // 画根节点
int     createHC(HTNode* HT, HCode* HC, char* array, int n, int m); // 创建哈夫曼码
void    codeSort(HCode* HC, int n);                                 // 排序哈夫曼码，便于加密、解密
void    showHC(HCode* HC, int n);                                   // 显示哈夫曼码
void    encode(HCode* HC, int n, char* str, char* binary);          // 加密
int     compare(HCode* HC, int n, char* str);                       // 二进制串比较
void    decode(HCode* HC, int n, char* binary, char* str);          // 解密

int main() {
    // 例子：8
    // A 7 B 19 C 2 D 6 E 32 F 3 G 21 H 10
    HTNode** HT     = (HTNode**)malloc(sizeof(HTNode*) * CODE_SIZE);
    HCode*   HC     = (HCode*)malloc(sizeof(HCode) * CODE_SIZE);
    char*    str    = (char*)malloc(sizeof(char) * BUFF_SIZE);
    char*    binary = (char*)malloc(sizeof(char) * BUFF_SIZE * CODE_SIZE);
    char     array[CODE_SIZE];
    int      n = 0;
    memset(str, 0, sizeof(char) * CODE_SIZE);
    memset(array, 0, sizeof(char) * CODE_SIZE);
    memset(binary, 0, sizeof(char) * BUFF_SIZE * CODE_SIZE);

    int type = 0;
    printf("请输入录入信息方式（0-Hand; 1-Default; 2-File）：");
    scanf("%d", &type);
    switch (type) {
    case 0:
        inputHand(HT, &n);
        break;
    case 1:
        inputDefault(HT, &n);
        break;
    case 2:
        inputFile(HT, &n, str);
        break;
    default:
        break;
    }
    createHT(HT, n);
    draw(HT[2 * n - 2]);
    createHC(HT[2 * n - 2], HC, array, 0, 0);
    codeSort(HC, n);
    showHC(HC, n);
    // 如果是 手打 或者 默认，需要手动输入字符串编码解码，而读取文件直接将文件编码解码
    if (type == 0 || type == 1) {
        printf("请输入编码的字符串：");
        scanf("\n%[^\n]", str); // 输入带空格字符串
    }
    encode(HC, n, str, binary);
    printf("哈夫曼编码为：%s\n", binary);
    memset(str, 0, sizeof(char) * BUFF_SIZE);
    decode(HC, n, binary, str);
    printf("哈夫曼译码为：%s\n", str);

    return 0;
}

void decode(HCode* HC, int n, char* binary, char* str) {
    int   len   = strlen(binary);
    char* tmp   = (char*)malloc(sizeof(char) * CODE_SIZE);
    int   size  = 1; // 比较长度
    int   ret   = 0; // 返回值
    int   pos   = 0; // 偏移（下标）
    int   index = 0; // 下标
    while (pos < len) {
        memset(tmp, 0, sizeof(char) * CODE_SIZE);
        strncpy(tmp, binary + pos, size);
        // printf("%s\n", tmp);
        ret = compare(HC, n, tmp);
        if (ret < 0) {
            size++;
        } else {
            pos += size;
            size       = 1;
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

void codeSort(HCode* HC, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (strlen(HC[j].cd) <= strlen(HC[j - 1].cd)) {
                HCode code;
                code      = HC[j];
                HC[j]     = HC[j - 1];
                HC[j - 1] = code;
            }
        }
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
int createHC(HTNode* HT, HCode* HC, char* array, int n, int m) {
    if (HT->data != '#') {
        HC[n].data = HT->data;
        array[m]   = '\0';
        memcpy(HC[n].cd, array, CODE_SIZE);
        n++;
    }
    if (HT->lchild != NULL) {
        array[m] = '0';
        n        = createHC(HT->lchild, HC, array, n, m + 1);
    }
    if (HT->rchild != NULL) {
        array[m] = '1';
        n        = createHC(HT->rchild, HC, array, n, m + 1);
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
    memset(str, '\0', sizeof(char) * SPACE_SIZE);
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
    int      start = 0; // 记录未创建（未排序）的下标
    int      end   = n; // 记录生成的新数据
    char     data;      // 字母
    Elemtype weight;    // 保存合并后的权重

    while (end - start > 1) {
        nodeSort(HT, start, end);
        data            = '#';
        weight          = HT[start]->weight + HT[start + 1]->weight;
        HT[end]         = newNode(data, weight);
        HT[end]->lchild = HT[start];
        HT[end]->rchild = HT[start + 1];

        start += 2;
        end++;
    }
    // printf("index\tdata\tweight\n");
    // for (int i = 0; i < 2 * n - 1; i++) {		// 各种属性，输出看一看，有没有问题
    // 	printf("%5d\t", i);
    // 	printf("%4c\t", HT[i]->data);
    // 	printf("%6d\n", HT[i]->weight);
    // }
}

void nodeSort(HTNode** HT, int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = end - 1; j > i; j--) {
            if (HT[j]->weight < HT[j - 1]->weight) {
                HTNode* node;
                node      = HT[j - 1];
                HT[j - 1] = HT[j];
                HT[j]     = node;
            }
        }
    }
}

HTNode* newNode(char data, Elemtype weight) {
    HTNode* node = (HTNode*)malloc(sizeof(HTNode));
    node->data   = data;
    node->weight = weight;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

/**
 * 1、手动输入，不能输入空格
 * 2、创建数组，自动遍历
 * 3、读取文件，变成数组
 */
void inputHand(HTNode** HT, int* n) {
    int      i = 0;
    char     data;
    Elemtype weight;
    char     dataArray[CODE_SIZE];
    Elemtype weightArray[CODE_SIZE];

    printf("请输入哈夫曼叶子结点：");
    scanf("%d", n);
    printf("请输入结点和权值(例如A 1)：\n"); // 规律，总结点个数为叶子结点两倍减一，2*N-1
    while (i / 2 < *n) {                     // scanf 读取空格截止
        scanf("%c %d", &data, &weight);      // 所以输入两个，循环两次，所以除以 2
        dataArray[i / 2]   = data;
        weightArray[i / 2] = weight;
        i++;
    }
    for (int j = 0; j < *n; j++) {
        HT[j] = newNode(dataArray[j], weightArray[j]);
    }
}

void inputDefault(HTNode** HT, int* n) {
    char     dataArray[CODE_SIZE]   = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ',', ' '};
    Elemtype weightArray[CODE_SIZE] = {819, 147, 383, 391, 1225, 225, 171, 457, 710, 14, 41, 377, 334, 706, 726, 289, 9, 685, 636, 941, 258, 109, 159, 21, 158, 8, 50, 50};
    *n                              = 28;

    for (int j = 0; j < *n; j++) {
        HT[j] = newNode(dataArray[j], weightArray[j]);
    }
}

void inputFile(HTNode** HT, int* n, char* str) {
    int*     hash = (int*)malloc(sizeof(int) * CODE_SIZE);
    char     dataArray[CODE_SIZE];
    Elemtype weightArray[CODE_SIZE];
    memset(hash, 0, sizeof(int) * CODE_SIZE);
    *n = 0;

    FILE* fp = fopen("D:\\VScode\\C_C++\\algorithm\\tree\\file.txt", "r+");
    for (int i = 0; !feof(fp); i++) {
        int ch = fgetc(fp);
        hash[ch]++;
        *str++ = (char)ch;
    }

    for (int i = 0; i < 256; i++) {
        if (hash[i] != 0) {
            dataArray[(*n)]     = i;
            weightArray[(*n)++] = hash[i];
        }
    }

    for (int j = 0; j < *n; j++) {
        HT[j] = newNode(dataArray[j], weightArray[j]);
    }
}
```