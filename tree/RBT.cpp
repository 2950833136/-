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
 * 基础函数
 */
RBTNode* GetParent(RBTNode* n);      // 得到父节点
RBTNode* GetGrandParent(RBTNode* n); // 得到祖父节点
RBTNode* GetSibling(RBTNode* n);     // 得到兄弟节点
RBTNode* GetUncle(RBTNode* n);       // 得到叔父节点
void     RotateLeft(RBTNode* n);     // 左旋
void     RotateRight(RBTNode* n);    // 右旋

/**
 * 红黑树插入函数
 */
RBTNode* NewNode(int key, enum color_t color, RBTNode* parent, RBTNode* left, RBTNode* right); // 新建节点
RBTNode* Insert(RBTNode* root, RBTNode* n);                                                    // 插入，返回根节点
void     InsertRecurse(RBTNode* root, RBTNode* n);                                             // 递归插入到合适位置，
void     InsertRepairTree(RBTNode* n);                                                         // 插入后修复树
void     InsertCase1(RBTNode* n);                                                              // 各种情形
void     InsertCase2(RBTNode* n);
void     InsertCase3(RBTNode* n);
void     InsertCase4(RBTNode* n);
void     InsertCase4Step2(RBTNode* n);

/**
 * 红黑树删除函数
 */
bool DeleteNode(RBTNode* root, int key);      // 根据值找到节点
void ReplaceNode(RBTNode* n, RBTNode* child); // 仅替换节点值
void DeleteOneChild(RBTNode* n);              // 删除一个节点
void DeleteCase1(RBTNode* n);                 // 各种情形
void DeleteCase2(RBTNode* n);
void DeleteCase3(RBTNode* n);
void DeleteCase4(RBTNode* n);
void DeleteCase5(RBTNode* n);
void DeleteCase6(RBTNode* n);

/**
 * 通用函数（画树）
 */
void draw(RBTNode* root);                             // 画树，根节点
void draw_level(RBTNode* root, bool left, char* str); // 画树，左右子树

// RBTNode* NIL = (RBTNode*)malloc(sizeof(RBTNode));
RBTNode* NIL = NewNode(0, BLACK, NULL, NULL, NULL);

int main() {
    RBTNode* root = NULL;

    // 插入
    int in[]   = {9, 5, 1, 3, 7, 8, 6, 2, 4};
    int inSize = sizeof(in) / sizeof(in[0]);

    for (int i = 0; i < inSize; i++) {
        RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
        node->key     = in[i];
        root          = Insert(root, node);
        printf("插入 %d 后的树：\n", node->key);
        draw(root);
    }

    // 删除
    int del[]   = {5, 9, 6, 2, 3};
    int delSize = sizeof(del) / sizeof(del[0]);

    for (int i = 0; i < delSize; i++) {
        DeleteNode(root, del[i]);
        printf("删除 %d 后的树：\n", del[i]);
        draw(root);
    }

    return 0;
}

RBTNode* getSmallestChild(RBTNode* n) {
    if (n->right == NIL) {
        return n;
    }
    return getSmallestChild(n->right);
}

bool DeleteNode(RBTNode* root, int key) {
    if (key < root->key) {
        if (root->left == NIL) {
            return false;
        }
        return DeleteNode(root->left, key);
    } else if (key > root->key) {
        if (root->right == NIL) {
            return false;
        }
        return DeleteNode(root->right, key);
    } else if (key == root->key) {
        if (root->right == NIL) {
            DeleteOneChild(root);
            return true;
        }
        RBTNode* smallest = getSmallestChild(root->left);
        root->key         = smallest->key;
        DeleteOneChild(smallest);
        return true;
    } else {
        return false;
    }
}

void ReplaceNode(RBTNode* n, RBTNode* child) {
    child->parent = n->parent;
    if (n == n->parent->left) {
        n->parent->left = child;
    } else {
        n->parent->right = child;
    }
}

void DeleteOneChild(RBTNode* n) {
    // Precondition: n has at most one non-leaf child.
    RBTNode* child = (n->right == NIL) ? n->left : n->right;
    assert(child);

    // 儿子直接替换
    ReplaceNode(n, child);
    /**
     * 1. 红色
     *      - 替换了，直接释放删除即可
     * 2. 黑色
     *      - 儿子红色，儿子改黑色
     *      - 儿子黑色，依次讨论
     */
    if (n->color == BLACK) {
        if (child->color == RED) {
            child->color = BLACK;
        } else {
            DeleteCase1(child);
        }
    }
    free(n);
}

void DeleteCase1(RBTNode* n) {
    if (n->parent != NULL) {
        DeleteCase2(n);
    }
}

void DeleteCase2(RBTNode* n) {
    RBTNode* s = GetSibling(n);

    if (s->color == RED) {
        n->parent->color = RED;
        s->color         = BLACK;
        if (n == n->parent->left) {
            RotateLeft(n->parent);
        } else {
            RotateRight(n->parent);
        }
    }
    DeleteCase3(n);
}

void DeleteCase3(RBTNode* n) {
    RBTNode* s = GetSibling(n);

    if ((n->parent->color == BLACK) && (s->color == BLACK) &&
        (s->left->color == BLACK) && (s->right->color == BLACK)) {
        s->color = RED;
        DeleteCase1(n->parent);
    } else {
        DeleteCase4(n);
    }
}

void DeleteCase4(RBTNode* n) {
    RBTNode* s = GetSibling(n);

    if ((n->parent->color == RED) && (s->color == BLACK) &&
        (s->left->color == BLACK) && (s->right->color == BLACK)) {
        s->color         = RED;
        n->parent->color = BLACK;
    } else {
        DeleteCase5(n);
    }
}

void DeleteCase5(RBTNode* n) {
    RBTNode* s = GetSibling(n);

    // This if statement is trivial, due to case 2 (even though case 2 changed
    // the sibling to a sibling's child, the sibling's child can't be red, since
    // no red parent can have a red child).
    if (s->color == BLACK) {
        // The following statements just force the red to be on the left of the
        // left of the parent, or right of the right, so case six will rotate
        // correctly.
        if ((n == n->parent->left) && (s->right->color == BLACK) &&
            (s->left->color == RED)) {
            // This last test is trivial too due to cases 2-4.
            s->color       = RED;
            s->left->color = BLACK;
            RotateRight(s);
        } else if ((n == n->parent->right) && (s->left->color == BLACK) &&
                   (s->right->color == RED)) {
            // This last test is trivial too due to cases 2-4.
            s->color        = RED;
            s->right->color = BLACK;
            RotateLeft(s);
        }
    }
    DeleteCase6(n);
}

void DeleteCase6(RBTNode* n) {
    RBTNode* s = GetSibling(n);

    s->color         = n->parent->color;
    n->parent->color = BLACK;

    if (n == n->parent->left) {
        s->right->color = BLACK;
        RotateLeft(n->parent);
    } else {
        s->left->color = BLACK;
        RotateRight(n->parent);
    }
}

RBTNode* GetParent(RBTNode* n) {
    // Note that parent is set to NULL for the root .
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
    if (n->right != NIL) {
        n->right->parent = n;
    }

    // Initially n could be the root.
    if (p != NIL) {
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
    if (n->left != NIL) {
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

RBTNode* NewNode(int key, enum color_t color, RBTNode* parent, RBTNode* left, RBTNode* right) {
    RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
    node->key     = key;
    node->color   = color;
    node->parent  = parent;
    node->left    = left;
    node->right   = right;
    return node;
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
            if (root->left != NIL) {
                InsertRecurse(root->left, n);
                return;
            } else {
                root->left = n;
            }
        } else { // n->key >= root->key
            if (root->right != NIL) {
                InsertRecurse(root->right, n);
                return;
            } else {
                root->right = n;
            }
        }
    }

    // Insert new RBTNode n.
    n->parent = root;
    n->left   = NIL;
    n->right  = NIL;
    n->color  = RED;
}

void InsertRepairTree(RBTNode* n) {
    if (GetParent(n) == NULL) {
        InsertCase1(n);
    } else if (GetParent(n)->color == BLACK) {
        InsertCase2(n);
    } else if (GetUncle(n) != NIL && GetUncle(n)->color == RED) {
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