#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1024

typedef struct tree_node {   //树结构体节点
    int               data;  //信息
    struct tree_node* left;  //左节点
    struct tree_node* right; //右节点
} TNode;

static TNode* tree = NULL;

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 创建普通树
* @input :
*   root: 二级指针
*	data: 存储数据
* @output:
*   -1	: 失败
*	0	: 成功
*****************************************************************************/
int insert(TNode** root, int data) {
    TNode* node;

    if ((*root) == NULL) {
        node = (TNode*)malloc(sizeof(TNode));
        if (node == NULL) {
            return -1;
        }
        node->data  = data;
        node->left  = NULL;
        node->right = NULL;

        (*root) = node;
        return 0;
    }

    if (data <= (*root)->data) {
        return insert(&(*root)->left, data);
    } else {
        return insert(&(*root)->right, data);
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
    printf("%d\n", root->data);

    if (root->left) {
        draw_level(root->left, true, strcat(str, (left ? "      " : "|     ")));
    }

    str[strlen(str) - 6] = '\0';
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 根节点画树
* @input :
*   root : 树
* @output:
*   none : none
*****************************************************************************/
void draw(TNode* root) {
    char str[STR_SIZE];
    memset(str, '\0', STR_SIZE);

    if (root->right) {
        draw_level(root->right, false, str);
    }
    printf("%d\n", root->data);
    if (root->left) {
        draw_level(root->left, true, str);
    }

    printf("\n\n");
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 得到子节点数
* @input :
*   root: 树 
* @output:
*   num	: 子节点数
*****************************************************************************/
static int get_num(TNode* root) {
    if (root == NULL) {
        return 0;
    }
    return get_num(root->left) + 1 + get_num(root->right);
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 得到子结点为空的最左边节点
* @input :
*   root	: 树
* @output:
*   TNode	: 右子节点为空的节点
*****************************************************************************/
static TNode* find_min(TNode* root) {
    if (root->left == NULL) {
        return root;
    }
    return find_min(root->left);
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 树左转
* @input :
*   root: 树
* @output:
*   none: none
*****************************************************************************/
static void turn_left(TNode** root) {
    TNode* cur            = *root;
    *root                 = cur->right;
    cur->right            = NULL;
    find_min(*root)->left = cur;

    draw(tree);
    //getchar();
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 得到子结点为空的最右边节点
* @input :
*   root	: 树
* @output:
*   TNode	: 右子节点为空的节点
*****************************************************************************/
static TNode* find_max(TNode* root) {
    if (root->right == NULL) {
        return root;
    }
    return find_max(root->right);
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 树右转
* @input :
*   root: 二级指针树
* @output:
*   none: none
*****************************************************************************/
static void turn_right(TNode** root) {
    TNode* cur             = *root;
    *root                  = cur->left;
    cur->left              = NULL;
    find_max(*root)->right = cur;

    draw(tree);
    //getchar();
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 平衡二叉树
* @input :
*   root: 二级指针树
* @output:
*   none: none
*****************************************************************************/
void balance(TNode** root) {
    if (*root == NULL) {
        return;
    }

    while (1) {
        int sub = get_num((*root)->left) - get_num((*root)->right);
        if (sub >= -1 && sub <= 1) {
            break;
        }
        if (sub < -1) {
            turn_left(root);
        } else {
            turn_right(root);
        }
    }
    balance(&(*root)->left);
    balance(&(*root)->right);
}

//中序遍历
void inOrder(TNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    int array[] = {6, 5, 7, 2, 3, 8, 4, 1, 2, 9, 10, 0, 15, 13};
    //int array[] = { 1,2,3,4,5,6,7,8,9 };
    //int array[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

    //循环创建树
    for (int i = 0; i < sizeof(array) / sizeof(*array); i++) {
        insert(&tree, array[i]);
    }

    draw(tree);
    balance(&tree);
    draw(tree);
    inOrder(tree);

    return 0;
}