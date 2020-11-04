#define _CRT_SECURE_NO_WARNINGS // VS 忽略安全警告

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1024

typedef struct _Adelson_Velsky_Landis_Node {    // 树结构体节点
    int                                 key;    // 键值
    int                                 value;  // 信息
    int                                 height; // 高度（平衡因子）
    struct _Adelson_Velsky_Landis_Node* parent; // 父节点
    struct _Adelson_Velsky_Landis_Node* left;   // 左节点
    struct _Adelson_Velsky_Landis_Node* right;  // 右节点
} AVLNode;

/*
*	相关树函数
*/
int      max(int a, int b);                         // 最大值
int      height(AVLNode* root);                     // 通过结构体，直接返回树高度
int      height_update(AVLNode* root);              // 更新树的高度
AVLNode* new_node(int key, int value);              // 新建节点，赋初值
AVLNode* insert(AVLNode* root, int key, int value); // 插入节点
AVLNode* find_min(AVLNode* root);                   // 查找子结点中最小的节点
AVLNode* find_max(AVLNode* root);                   // 查找子结点中最大的节点
AVLNode* delete_node(AVLNode* root, int key);       // 删除节点
void     delete_tree(AVLNode* root);                // 删除树

/*
*	AVL函数
*/
int      get_balance(AVLNode* root);  // 得到平衡因子
AVLNode* rotate_left(AVLNode* root);  // 左旋
AVLNode* rotate_right(AVLNode* root); // 右旋
AVLNode* balance_node(AVLNode* root); // 判断节点该怎么平衡调整

/*
*	通用函数（画树）
*/
void draw(AVLNode* root);                             // 画树，根节点
void draw_level(AVLNode* root, bool left, char* str); // 画树，左右子树

int main() {
    AVLNode* root = NULL;
    /*
    *	大数据测试
    */
    int nums[]   = {6, 8, 2, 3, 5, 4, 7, 1, 9, 6};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    // 添加
    for (int i = 0; i < numsSize; i++) {
        root = insert(root, nums[i], nums[i] + 10);
        printf("insert %d tree:\n", nums[i]);
        draw(root);
    }

    // 删除
    // for (int i = 0; i < numsSize; i++) {
    //     root = delete_node(root, nums[i]);
    //     printf("delete %d tree:\n", nums[i]);
    //     draw(root);
    // }

    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

// 更新节点高度
int height_update(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    int height_left  = height(root->left) + 1;
    int height_right = height(root->right) + 1;
    root->height     = max(height_left, height_right);
    return root->height;
}

/*****************************************************************************
* @data  : 2020/4/20
* @brief : 新建节点
* @input :
*   key		: 键值
*	value	: 信息
* @output:
*   node	: 新节点
*****************************************************************************/
AVLNode* new_node(int key, int value) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key     = key;
    node->value   = value;
    node->height  = 1;
    node->parent  = NULL;
    node->left    = NULL;
    node->right   = NULL;
    return node;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 插入数据，创建平衡树
* @input :
*   root	: 树
*	key		: 键值
*	value	: 信息
* @output:
*   node    : 树根节点
*****************************************************************************/
AVLNode* insert(AVLNode* node, int key, int value) {
    if (node == NULL) {
        node = new_node(key, value);
        return node;
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else {
        node->right = insert(node->right, key, value);
    }
    node = balance_node(node);
    height_update(node);
    return node;
}

// 得到平衡因子
int get_balance(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return height_update(root->left) - height_update(root->right);
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
// 右旋，LL型
AVLNode* rotate_right(AVLNode* root) {
    AVLNode* node = root->left;
    if (node->right != NULL) { //更新父结点
        node->right->parent = root;
    }
    if (root->parent != NULL) { //上上级节点重新指向旋转后的节点
        if (root->parent->right == root) {
            root->parent->right = node;
        } else {
            root->parent->left = node;
        }
    }
    root->left  = node->right; //右旋（这里是关键）
    node->right = root;

    node->parent = root->parent; //更新父结点
    root->parent = node;
    root->height = height_update(root); //更新高度
    node->height = height_update(node);
    return node;
}

// 左旋，RR型
AVLNode* rotate_left(AVLNode* root) {
    AVLNode* node = root->right;
    if (node->left != NULL) { //更新父结点
        node->left->parent = root;
    }
    if (root->parent != NULL) { //上上级节点重新指向旋转后的节点
        if (root->parent->right == root) {
            root->parent->right = node;
        } else {
            root->parent->left = node;
        }
    }
    root->right = node->left; //左旋（这里是关键）
    node->left  = root;

    node->parent = root->parent; //更新父结点
    root->parent = node;
    root->height = height_update(root); //更新高度
    node->height = height_update(node);
    return node;
}

// 判断平衡类型
AVLNode* balance_node(AVLNode* root) {
    if (get_balance(root) > 1 && get_balance(root->left) > 0) {
        // LL型，单右
        return rotate_right(root);
    }
    if (get_balance(root) > 1 && get_balance(root->left) <= 0) {
        // LR型，先左后右
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (get_balance(root) < -1 && get_balance(root->right) <= 0) {
        // RR型，单左
        return rotate_left(root);
    }
    if (get_balance(root) < -1 && get_balance(root->right) > 0) {
        // RL型，先右后左
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 水平画树
* @input :
*   root: 树
*	left: 判断左右
*	str : 可变字符串
*****************************************************************************/
void draw_level(AVLNode* root, bool left, char* str) {
    if (root->right) {
        draw_level(root->right, false, strcat(str, (left ? "|     " : "      ")));
    }

    printf("%s", str);
    printf("%c", (left ? '\\' : '/'));
    printf("-----");
    printf("%d ", root->key);
    printf("%d\n", root->height);

    if (root->left) {
        draw_level(root->left, true, strcat(str, (left ? "      " : "|     ")));
    }
    str[strlen(str) - 6] = '\0';
}

void draw(AVLNode* root) {
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

// 查找最小节点
AVLNode* find_min(AVLNode* node) {
    if (node->left == NULL) {
        return node;
    }
    return find_min(node->left);
}

// 查找最大节点
AVLNode* find_max(AVLNode* node) {
    if (node->right == NULL) {
        return node;
    }
    return find_max(node->right);
}

/*****************************************************************************
* @data  : 2020/4/21
* @brief : 删除平衡树节点
* @input :
*   root: 树
*	key	: 键值
* @output:
*   root: 树根节点
*****************************************************************************/
AVLNode* delete_node(AVLNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (key < root->key) {
        root->left = delete_node(root->left, key);
        balance_node(root->left);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
        balance_node(root->right);
    } else {
        if (root->left != NULL && root->right != NULL) {
            if (height(root->left) < height(root->right)) {
                /**
                 * 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                 *  - 找出tree的右子树中的最小节点
                 *  - 将该最小节点的值赋值给tree
                 *  - 删除该最小节点
                 * 这类似于用"tree的左子树中最大节点"做"tree"的替身
                 * 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的
                 */
                AVLNode* minNode = find_min(root->right);
                root->key        = minNode->key;
                root->right      = delete_node(root->right, minNode->key);
            } else {
                /**
                 * 如果tree的左子树比右子树高
                 *  - 找出tree的左子树中的最大节点
                 *  - 将该最大节点的值赋值给tree
                 *  - 删除该最大节点
                 */
                AVLNode* maxNode = find_max(root->left);
                root->key        = maxNode->key;
                root->left       = delete_node(root->left, maxNode->key);
            }
        } else {
            AVLNode* tmp = root;
            root         = (root->left != NULL) ? root->left : root->right;
            delete tmp;
        }
    }
    height_update(root);
    return root;
}

// 释放树
void delete_tree(AVLNode* root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}