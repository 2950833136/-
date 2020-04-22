#define _CRT_SECURE_NO_WARNINGS	//VS 忽略安全警告

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE		6
#define STR_SIZE	1024

typedef struct tree_node {		//树结构体节点
	int key;					//键值
	int value;					//信息
	int height;					//高度（平衡因子）
	struct tree_node* parent;	//父节点
	struct tree_node* left;		//左节点
	struct tree_node* right;	//右节点
}TNode;

static TNode* tree = NULL;		//定义 树 全局变量

/*
*	相关树函数
*/
TNode* new_node(int key, int value);			//新建节点，赋初值
int insert(TNode** root, int key, int value);	//插入节点
int get_height(TNode* root);					//递归得到树的高度
void set_tree(TNode* root);						//更新树的高度、父节点
TNode* find_node(TNode* root, int key);			//查找节点
TNode* find_min(TNode* root);					//查找子结点中最小的节点
TNode* find_max(TNode* root);					//查找子结点中最大的节点
void delete_node(TNode* root, int key);			//删除节点
void delete_tree(TNode* root);					//删除树

/*
*	AVL函数
*/
int max(int a, int b);							//最大值
int height(TNode* root);						//通过结构体，直接返回树高度
int get_balance(TNode* root);					//得到平衡因子
TNode* is_head(TNode* pre, TNode* now);			//得到树的头节点
TNode* rotate_left(TNode* root);				//左旋
TNode* rotate_right(TNode* root);				//右旋
TNode* node_balance(TNode* root);				//判断节点该怎么平衡调整
void balance(TNode* root);						//递归平衡整棵树

/*
*	通用函数（中序遍历，画树）
*/
void inOrder(TNode* root);						//中序遍历
void draw_level(TNode* root, bool left, char* str);	//画树，左右子树
void draw(TNode* root);							//画树，根节点

int main() {
	int array[] = { 6,5,7,3,8,4,1,9,10,3,7 };
	//int array[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	//int array[] = { 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };

	//循环创建树
	for (int i = 0; i < sizeof(array) / sizeof(*array); i++) {
		insert(&tree, array[i], array[i] + 10);
	}

	set_tree(tree);
	draw(tree);
	inOrder(tree);
	printf("\n");

	balance(tree);
	draw(tree);
	inOrder(tree);
	printf("\n");

	printf("添加节点：%d\n", 2);
	insert(&tree, 2, 12);
	set_tree(tree);
	balance(tree);
	draw(tree);
	inOrder(tree);
	printf("\n");

	//find_node(tree, 6);
	for (int i = 0; i < sizeof(array) / sizeof(*array); i++) {
		printf("删除节点：%d", array[i]);
		delete_node(tree, array[i]);
		balance(tree);
		draw(tree);
	}
	return 0;
}

/*****************************************************************************
* @data  : 2020/4/20
* @brief : 新建节点
* @input :
*   key		: 键值
*	value	: 信息
* @output:
*   TNode	: 新节点
*****************************************************************************/
TNode* new_node(int key, int value) {
	TNode* node = (TNode*)malloc(sizeof(TNode));
	node->key = key;
	node->value = value;
	node->height = 1;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 插入数据，创建顺序树
* @input :
*   root	: 二级指针
*	key		: 键值
*	value	: 信息
* @output:
*   -1		: 失败
*	0		: 成功
*****************************************************************************/
int insert(TNode** root, int key, int value) {
	if ((*root) == NULL) {
		(*root) = new_node(key, value);
		return 0;
	}
	if (key <= (*root)->key) {
		return insert(&(*root)->left, key, value);
	}
	else {
		return insert(&(*root)->right, key, value);
	}
}

//递归得到节点高度
int get_height(TNode* root) {
	if (root == NULL) {
		return 0;
	}
	int left_heigth = get_height(root->left) + 1;
	int right_heigth = get_height(root->right) + 1;
	return left_heigth >= right_heigth ? left_heigth : right_heigth;
}

//设置树的父结点，高度
void set_tree(TNode* root) {
	if (root == NULL) {
		return;
	}
	root->height = get_height(root);
	if (root->left != NULL) {
		root->left->parent = root;
	}
	if (root->right != NULL) {
		root->right->parent = root;
	}
	set_tree(root->left);
	set_tree(root->right);
}

//查找节点
TNode* find_node(TNode* root, int key) {
	TNode* node = root;
	while (node) {
		if (key < node->key) {
			node = node->left;
		}
		else if (key > node->key) {
			node = node->right;
		}
		else {
			printf("节点键值 %d，高度 %d\n", node->key, node->height);
			return node;
		}
	}
}

//查找最小节点
TNode* find_min(TNode* root) {
	TNode* node = root;
	if (node == NULL) {
		return NULL;
	}
	while (node->left) {
		node = node->left;
	}
	return node;
}

//查找最大节点
TNode* find_max(TNode* root) {
	TNode* node = root;
	if (node == NULL) {
		return NULL;
	}
	while (node->right) {
		node = node->right;
	}
	return node;
}

/*****************************************************************************
* @data  : 2020/4/21
* @brief : 删除平衡树节点
* @input :
*   root: 树
*	key	: 键值
* @output:
*   none: none
*****************************************************************************/
void delete_node(TNode* root, int key) {
	TNode* node;
	TNode* tmp;
	node = find_node(root, key);
	if (node->parent == NULL) {			//根节点
		tmp = find_max(node->left);
		tmp->right = node->right;
		node->left->parent = NULL;
		node->right->parent = tmp;
		tree = node->left;
		set_tree(tree);
	}
	else if (node->left == NULL && node->right != NULL) {		//没有左子节点
		if (node->parent->left == node) {
			node->parent->left = node->right;
		}
		else {
			node->parent->right = node->right;
		}
		node->right->parent = node->parent;
	}
	else if (node->left != NULL && node->right == NULL) {		//没有右子节点
		if (node->parent->left == node) {
			node->parent->left = node->left;
		}
		else {
			node->parent->right = node->left;
		}
		node->left->parent = node->parent;
	}
	else if ((node->left == NULL) && (node->right == NULL)) {	//没有子节点
		if (node->parent->left == node) {
			node->parent->left = NULL;
		}
		else {
			node->parent->right = NULL;
		}
	}
	else {											//双节点都有
		tmp = find_max(node->left);
		if (node->parent->left == node) {			//在父节点的父节点左边
			node->parent->left = node->left;
			node->left->parent = node->parent;
			tmp->right = node->right;
			node->right->parent = tmp;
		}
		else {										//在父节点的父节点右边
			node->parent->right = node->left;
			node->left->parent = node->parent;
			tmp->right = node->right;
			node->right->parent = tmp;
		}
	}
}

//释放树
void delete_tree(TNode* root) {
	if (root != NULL) {
		delete_tree(root->left);
		delete_tree(root->right);
		free(root);
	}
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(TNode* root) {
	if (root == NULL) {
		return 0;
	}
	return root->height;
}

TNode* is_head(TNode* pre, TNode* now) {
	return get_height(pre) >= get_height(now) ? pre : now;
}

//得到平衡因子
int get_balance(TNode* root) {
	if (root == NULL)
		return 0;
	return height(root->left) - height(root->right);
}

/*****************************************************************************
1. LL型：单右旋
以（5）为轴，将（7）右旋
		 7
		/ \
	   5   8                 5
	  / \      ------>     /    \
	 3   6                3      7
	/ \                  / \    / \
   2   4                2   4  6   8
2. LR型：先左旋后右旋
（89）不变，先以（6）为轴，将（4）左旋，然后把（6）拼接到（8）下面；再以（6）为轴，将（8）右旋
ps：因为旋转指针指向没变，导致指向有问题，需要重新拼接。
		 8                    8
		/ \                  / \
	   4   9                6   9                    6
	  / \      ------>     / \         ------>    /    \
	 3   6                4   7                  4      8
		/ \              / \                    / \    / \
	   5   7            3   5                  3   5  7   9
3. RR型：单左旋
以（5）为轴，将（3）左旋
	 3
	/ \
   2   5                     5
	  / \      ------>    /    \
	 4   7               3      7
		/ \             / \    / \
	   6   9           2   4  6   9
4. RL型：先右旋后左旋
（34）不变，先以（6）为轴，将（8）右旋，然后把（6）拼接到（4）下面；再以（6）为轴，将（4）左旋
ps：因为旋转指针指向没变，导致指向有问题，需要重新拼接。
		 4                   4
		/ \                 / \
	   3   8               3   6                       6
		  / \   ------>       / \       ------>     /    \
		 6   9               5   8                 4      8
		/ \                     / \               / \    / \
	   5   7                   7   9             3   5  7   9
*****************************************************************************/
//右旋，LL型
TNode* rotate_right(TNode* root) {
	TNode* node = root->left;
	if (node->right != NULL) {			//更新父结点
		node->right->parent = root;
	}
	if (root->parent != NULL) {			//上上级节点重新指向旋转后的节点
		if (root->parent->right == root) {	
			root->parent->right = node;
		}
		else {
			root->parent->left = node;
		}
	}
	root->left = node->right;			//右旋（这里是关键）
	node->right = root;

	node->parent = root->parent;		//更新父结点
	root->parent = node;
	root->height = get_height(root);	//更新高度
	node->height = get_height(node);
	return node;
}

//左旋，RR型
TNode* rotate_left(TNode* root) {
	TNode* node = root->right;
	if (node->left != NULL) {			//更新父结点
		node->left->parent = root;
	}
	if (root->parent != NULL) {			//上上级节点重新指向旋转后的节点
		if (root->parent->right == root) {
			root->parent->right = node;
		}
		else {
			root->parent->left = node;
		}
	}
	root->right = node->left;			//左旋（这里是关键）
	node->left = root;

	node->parent = root->parent;		//更新父结点
	root->parent = node;
	root->height = get_height(root);	//更新高度
	node->height = get_height(node);
	return node;
}

//判断平衡类型
TNode* node_balance(TNode* root) {
	if (get_balance(root) > 1 && get_balance(root->left) > 0) {
		//LL型，单右
		return rotate_right(root);
	}
	if (get_balance(root) > 1 && get_balance(root->left) <= 0) {
		//LR型，先左后右
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}
	if (get_balance(root) < -1 && get_balance(root->right) <= 0) {
		//RR型，单左
		return rotate_left(root);
	}
	if (get_balance(root) < -1 && get_balance(root->right) > 0) {
		//RL型，先右后左
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
}

//递归平衡树
void balance(TNode* root) {
	TNode* node = root;
	if (node == NULL) {
		return;
	}
	while (1) {
		int sub = get_balance(node);
		if (sub >= -1 && sub <= 1) {
			break;
		}
		node = node_balance(node);
	}
	tree = is_head(tree, node);				//取得高度最高的为根节点
	balance(node->left);
	balance(node->right);
}

//中序遍历
void inOrder(TNode* root) {
	if (root != NULL) {
		inOrder(root->left);
		printf("%d ", root->key);
		inOrder(root->right);
	}
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 水平画树
* @input :
*   root: 树
*	left: 判断左右
*	str : 可变字符串
* @output:
*   none: none
*****************************************************************************/
void draw_level(TNode* root, bool left, char* str) {
	if (root->right) {
		draw_level(root->right, false, strcat(str, (left ? "|     " : "      ")));
	}

	printf("%s", str);
	printf("%c", (left ? '\\' : '/'));
	printf("-----");
	printf("%d ", root->key);
	printf("%d ", root->height);
	printf("%d\n", root->parent->key);

	if (root->left) {
		draw_level(root->left, true, strcat(str, (left ? "      " : "|     ")));
	}
	str[strlen(str) - SPACE] = '\0';
}

void draw(TNode* root) {
	char str[STR_SIZE];
	memset(str, '\0', STR_SIZE);

	if (root == NULL) {
		return;
	}

	if (root->right) {
		draw_level(root->right, false, str);
	}
	printf("%d ", root->key);
	printf("%d\n", root->height);
	if (root->left) {
		draw_level(root->left, true, str);
	}
	printf("\n");
}