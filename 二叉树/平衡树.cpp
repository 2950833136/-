#define _CRT_SECURE_NO_WARNINGS	//VS ���԰�ȫ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE		6
#define STR_SIZE	1024

typedef struct tree_node {		//���ṹ��ڵ�
	int key;					//��ֵ
	int value;					//��Ϣ
	int height;					//�߶ȣ�ƽ�����ӣ�
	struct tree_node* parent;	//���ڵ�
	struct tree_node* left;		//��ڵ�
	struct tree_node* right;	//�ҽڵ�
}TNode;

static TNode* tree = NULL;		//���� �� ȫ�ֱ���

/*
*	���������
*/
TNode* new_node(int key, int value);			//�½��ڵ㣬����ֵ
int insert(TNode** root, int key, int value);	//����ڵ�
int get_height(TNode* root);					//�ݹ�õ����ĸ߶�
void set_tree(TNode* root);						//�������ĸ߶ȡ����ڵ�
TNode* find_node(TNode* root, int key);			//���ҽڵ�
TNode* find_min(TNode* root);					//�����ӽ������С�Ľڵ�
TNode* find_max(TNode* root);					//�����ӽ�������Ľڵ�
void delete_node(TNode* root, int key);			//ɾ���ڵ�
void delete_tree(TNode* root);					//ɾ����

/*
*	AVL����
*/
int max(int a, int b);							//���ֵ
int height(TNode* root);						//ͨ���ṹ�壬ֱ�ӷ������߶�
int get_balance(TNode* root);					//�õ�ƽ������
TNode* is_head(TNode* pre, TNode* now);			//�õ�����ͷ�ڵ�
TNode* rotate_left(TNode* root);				//����
TNode* rotate_right(TNode* root);				//����
TNode* node_balance(TNode* root);				//�жϽڵ����ôƽ�����
void balance(TNode* root);						//�ݹ�ƽ��������

/*
*	ͨ�ú��������������������
*/
void inOrder(TNode* root);						//�������
void draw_level(TNode* root, bool left, char* str);	//��������������
void draw(TNode* root);							//���������ڵ�

int main() {
	int array[] = { 6,5,7,3,8,4,1,9,10,3,7 };
	//int array[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	//int array[] = { 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };

	//ѭ��������
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

	printf("��ӽڵ㣺%d\n", 2);
	insert(&tree, 2, 12);
	set_tree(tree);
	balance(tree);
	draw(tree);
	inOrder(tree);
	printf("\n");

	//find_node(tree, 6);
	for (int i = 0; i < sizeof(array) / sizeof(*array); i++) {
		printf("ɾ���ڵ㣺%d", array[i]);
		delete_node(tree, array[i]);
		balance(tree);
		draw(tree);
	}
	return 0;
}

/*****************************************************************************
* @data  : 2020/4/20
* @brief : �½��ڵ�
* @input :
*   key		: ��ֵ
*	value	: ��Ϣ
* @output:
*   TNode	: �½ڵ�
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
* @brief : �������ݣ�����˳����
* @input :
*   root	: ����ָ��
*	key		: ��ֵ
*	value	: ��Ϣ
* @output:
*   -1		: ʧ��
*	0		: �ɹ�
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

//�ݹ�õ��ڵ�߶�
int get_height(TNode* root) {
	if (root == NULL) {
		return 0;
	}
	int left_heigth = get_height(root->left) + 1;
	int right_heigth = get_height(root->right) + 1;
	return left_heigth >= right_heigth ? left_heigth : right_heigth;
}

//�������ĸ���㣬�߶�
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

//���ҽڵ�
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
			printf("�ڵ��ֵ %d���߶� %d\n", node->key, node->height);
			return node;
		}
	}
}

//������С�ڵ�
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

//�������ڵ�
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
* @brief : ɾ��ƽ�����ڵ�
* @input :
*   root: ��
*	key	: ��ֵ
* @output:
*   none: none
*****************************************************************************/
void delete_node(TNode* root, int key) {
	TNode* node;
	TNode* tmp;
	node = find_node(root, key);
	if (node->parent == NULL) {			//���ڵ�
		tmp = find_max(node->left);
		tmp->right = node->right;
		node->left->parent = NULL;
		node->right->parent = tmp;
		tree = node->left;
		set_tree(tree);
	}
	else if (node->left == NULL && node->right != NULL) {		//û�����ӽڵ�
		if (node->parent->left == node) {
			node->parent->left = node->right;
		}
		else {
			node->parent->right = node->right;
		}
		node->right->parent = node->parent;
	}
	else if (node->left != NULL && node->right == NULL) {		//û�����ӽڵ�
		if (node->parent->left == node) {
			node->parent->left = node->left;
		}
		else {
			node->parent->right = node->left;
		}
		node->left->parent = node->parent;
	}
	else if ((node->left == NULL) && (node->right == NULL)) {	//û���ӽڵ�
		if (node->parent->left == node) {
			node->parent->left = NULL;
		}
		else {
			node->parent->right = NULL;
		}
	}
	else {											//˫�ڵ㶼��
		tmp = find_max(node->left);
		if (node->parent->left == node) {			//�ڸ��ڵ�ĸ��ڵ����
			node->parent->left = node->left;
			node->left->parent = node->parent;
			tmp->right = node->right;
			node->right->parent = tmp;
		}
		else {										//�ڸ��ڵ�ĸ��ڵ��ұ�
			node->parent->right = node->left;
			node->left->parent = node->parent;
			tmp->right = node->right;
			node->right->parent = tmp;
		}
	}
}

//�ͷ���
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

//�õ�ƽ������
int get_balance(TNode* root) {
	if (root == NULL)
		return 0;
	return height(root->left) - height(root->right);
}

/*****************************************************************************
1. LL�ͣ�������
�ԣ�5��Ϊ�ᣬ����7������
		 7
		/ \
	   5   8                 5
	  / \      ------>     /    \
	 3   6                3      7
	/ \                  / \    / \
   2   4                2   4  6   8
2. LR�ͣ�������������
��89�����䣬���ԣ�6��Ϊ�ᣬ����4��������Ȼ��ѣ�6��ƴ�ӵ���8�����棻���ԣ�6��Ϊ�ᣬ����8������
ps����Ϊ��תָ��ָ��û�䣬����ָ�������⣬��Ҫ����ƴ�ӡ�
		 8                    8
		/ \                  / \
	   4   9                6   9                    6
	  / \      ------>     / \         ------>    /    \
	 3   6                4   7                  4      8
		/ \              / \                    / \    / \
	   5   7            3   5                  3   5  7   9
3. RR�ͣ�������
�ԣ�5��Ϊ�ᣬ����3������
	 3
	/ \
   2   5                     5
	  / \      ------>    /    \
	 4   7               3      7
		/ \             / \    / \
	   6   9           2   4  6   9
4. RL�ͣ�������������
��34�����䣬���ԣ�6��Ϊ�ᣬ����8��������Ȼ��ѣ�6��ƴ�ӵ���4�����棻���ԣ�6��Ϊ�ᣬ����4������
ps����Ϊ��תָ��ָ��û�䣬����ָ�������⣬��Ҫ����ƴ�ӡ�
		 4                   4
		/ \                 / \
	   3   8               3   6                       6
		  / \   ------>       / \       ------>     /    \
		 6   9               5   8                 4      8
		/ \                     / \               / \    / \
	   5   7                   7   9             3   5  7   9
*****************************************************************************/
//������LL��
TNode* rotate_right(TNode* root) {
	TNode* node = root->left;
	if (node->right != NULL) {			//���¸����
		node->right->parent = root;
	}
	if (root->parent != NULL) {			//���ϼ��ڵ�����ָ����ת��Ľڵ�
		if (root->parent->right == root) {	
			root->parent->right = node;
		}
		else {
			root->parent->left = node;
		}
	}
	root->left = node->right;			//�����������ǹؼ���
	node->right = root;

	node->parent = root->parent;		//���¸����
	root->parent = node;
	root->height = get_height(root);	//���¸߶�
	node->height = get_height(node);
	return node;
}

//������RR��
TNode* rotate_left(TNode* root) {
	TNode* node = root->right;
	if (node->left != NULL) {			//���¸����
		node->left->parent = root;
	}
	if (root->parent != NULL) {			//���ϼ��ڵ�����ָ����ת��Ľڵ�
		if (root->parent->right == root) {
			root->parent->right = node;
		}
		else {
			root->parent->left = node;
		}
	}
	root->right = node->left;			//�����������ǹؼ���
	node->left = root;

	node->parent = root->parent;		//���¸����
	root->parent = node;
	root->height = get_height(root);	//���¸߶�
	node->height = get_height(node);
	return node;
}

//�ж�ƽ������
TNode* node_balance(TNode* root) {
	if (get_balance(root) > 1 && get_balance(root->left) > 0) {
		//LL�ͣ�����
		return rotate_right(root);
	}
	if (get_balance(root) > 1 && get_balance(root->left) <= 0) {
		//LR�ͣ��������
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}
	if (get_balance(root) < -1 && get_balance(root->right) <= 0) {
		//RR�ͣ�����
		return rotate_left(root);
	}
	if (get_balance(root) < -1 && get_balance(root->right) > 0) {
		//RL�ͣ����Һ���
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
}

//�ݹ�ƽ����
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
	tree = is_head(tree, node);				//ȡ�ø߶���ߵ�Ϊ���ڵ�
	balance(node->left);
	balance(node->right);
}

//�������
void inOrder(TNode* root) {
	if (root != NULL) {
		inOrder(root->left);
		printf("%d ", root->key);
		inOrder(root->right);
	}
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : ˮƽ����
* @input :
*   root: ��
*	left: �ж�����
*	str : �ɱ��ַ���
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