#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define STR_SIZE 1024

enum color_t {
    BLACK,
    RED
};

typedef struct _Red_Black_Tree_Node {
    int                          key;
    enum color_t                 color;
    struct _Red_Black_Tree_Node* parent;
    struct _Red_Black_Tree_Node* left;
    struct _Red_Black_Tree_Node* right;
} RBTNode;

/**
 * 红黑树插入函数
 */
RBTNode* GetParent(RBTNode* n);
RBTNode* GetGrandParent(RBTNode* n);
RBTNode* GetSibling(RBTNode* n);
RBTNode* GetUncle(RBTNode* n);
void     RotateLeft(RBTNode* n);
void     RotateRight(RBTNode* n);
RBTNode* Insert(RBTNode* root, RBTNode* n);
void     InsertRecurse(RBTNode* root, RBTNode* n);
void     InsertRepairTree(RBTNode* n);
void     InsertCase1(RBTNode* n);
void     InsertCase2(RBTNode* n);
void     InsertCase3(RBTNode* n);
void     InsertCase4(RBTNode* n);
void     InsertCase4Step2(RBTNode* n);

/**
 * 红黑树删除函数
 */

/**
 * 通用函数（画树）
 */
void draw(RBTNode* root);                             // 画树，根节点
void draw_level(RBTNode* root, bool left, char* str); // 画树，左右子树

int main() {
    RBTNode* root = NULL;

    for (int i = 0; i < 10; i++) {
        RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
        node->key     = i;
        root          = Insert(root, node);
        printf("插入后的树：\n");
        draw(root);
    }

    return 0;
}

RBTNode* GetParent(RBTNode* n) {
    // Note that parent is set to null for the root .
    return n == NULL ? NULL : n->parent;
}

RBTNode* GetGrandParent(RBTNode* n) {
    // Note that it will return NULL if this is root or child of root
    return GetParent(GetParent(n));
}

RBTNode* GetSibling(RBTNode* n) {
    RBTNode* p = GetParent(n);

    // No parent means no sibling.
    if (p == NULL) {
        return NULL;
    }

    if (n == p->left) {
        return p->right;
    } else {
        return p->left;
    }
}

RBTNode* GetUncle(RBTNode* n) {
    RBTNode* p = GetParent(n);

    // No parent means no uncle
    return GetSibling(p);
}

void RotateLeft(RBTNode* n) {
    RBTNode* nnew = n->right;
    RBTNode* p    = GetParent(n);
    // Since the leaves of a red-black tree are empty,
    // they cannot become internal nodes.
    assert(nnew != NULL);

    n->right   = nnew->left;
    nnew->left = n;
    n->parent  = nnew;
    // Handle other child/parent pointers.
    if (n->right != NULL) {
        n->right->parent = n;
    }

    // Initially n could be the root.
    if (p != NULL) {
        if (n == p->left) {
            p->left = nnew;
        } else if (n == p->right) {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

void RotateRight(RBTNode* n) {
    RBTNode* nnew = n->left;
    RBTNode* p    = GetParent(n);
    // Since the leaves of a red-black tree are empty,
    // they cannot become internal nodes.
    assert(nnew != NULL);

    n->left     = nnew->right;
    nnew->right = n;
    n->parent   = nnew;

    // Handle other child/parent pointers.
    if (n->left != NULL) {
        n->left->parent = n;
    }

    // Initially n could be the root.
    if (p != NULL) {
        if (n == p->left) {
            p->left = nnew;
        } else if (n == p->right) {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

RBTNode* Insert(RBTNode* root, RBTNode* n) {
    // Insert new RBTNode into the current tree.
    InsertRecurse(root, n);

    // Repair the tree in case any of the red-black properties have been violated.
    InsertRepairTree(n);

    // Find the new root to return.
    root = n;
    while (GetParent(root) != NULL) {
        root = GetParent(root);
    }
    return root;
}

void InsertRecurse(RBTNode* root, RBTNode* n) {
    // Recursively descend the tree until a leaf is found.
    if (root != NULL) {
        if (n->key < root->key) {
            if (root->left != NULL) {
                InsertRecurse(root->left, n);
                return;
            } else {
                root->left = n;
            }
        } else { // n->key >= root->key
            if (root->right != NULL) {
                InsertRecurse(root->right, n);
                return;
            } else {
                root->right = n;
            }
        }
    }

    // Insert new RBTNode n.
    n->parent = root;
    n->left   = NULL;
    n->right  = NULL;
    n->color  = RED;
}

void InsertRepairTree(RBTNode* n) {
    if (GetParent(n) == NULL) {
        InsertCase1(n);
    } else if (GetParent(n)->color == BLACK) {
        InsertCase2(n);
    } else if (GetUncle(n) != NULL && GetUncle(n)->color == RED) {
        InsertCase3(n);
    } else {
        InsertCase4(n);
    }
}

void InsertCase1(RBTNode* n) {
    n->color = BLACK;
}

void InsertCase2(RBTNode* n) {
    // Do nothing since tree is still valid.
    return;
}

void InsertCase3(RBTNode* n) {
    GetParent(n)->color      = BLACK;
    GetUncle(n)->color       = BLACK;
    GetGrandParent(n)->color = RED;
    InsertRepairTree(GetGrandParent(n));
}

void InsertCase4(RBTNode* n) {
    RBTNode* p = GetParent(n);
    RBTNode* g = GetGrandParent(n);

    if (n == p->right && p == g->left) {
        RotateLeft(p);
        n = n->left;
    } else if (n == p->left && p == g->right) {
        RotateRight(p);
        n = n->right;
    }

    InsertCase4Step2(n);
}

void InsertCase4Step2(RBTNode* n) {
    RBTNode* p = GetParent(n);
    RBTNode* g = GetGrandParent(n);

    if (n == p->left) {
        RotateRight(g);
    } else {
        RotateLeft(g);
    }
    p->color = BLACK;
    g->color = RED;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 水平画树
* @input :
*   root: 树
*	left: 判断左右
*	str : 可变字符串
*****************************************************************************/
void draw_level(RBTNode* root, bool left, char* str) {
    if (root->right) {
        draw_level(root->right, false, strcat(str, (left ? "|     " : "      ")));
    }

    printf("%s", str);
    printf("%c", (left ? '\\' : '/'));
    printf("-----");
    printf("%d ", root->key);
    printf("%s\n", (root->color == BLACK ? "B" : "R"));

    if (root->left) {
        draw_level(root->left, true, strcat(str, (left ? "      " : "|     ")));
    }
    str[strlen(str) - 6] = '\0';
}

void draw(RBTNode* root) {
    char str[STR_SIZE];
    memset(str, '\0', STR_SIZE);

    if (root == NULL) {
        return;
    }

    if (root->right) {
        draw_level(root->right, false, str);
    }
    printf("%d ", root->key);
    printf("%s\n", (root->color == BLACK ? "B" : "R"));
    if (root->left) {
        draw_level(root->left, true, str);
    }
    printf("\n");
}