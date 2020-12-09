#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3
#define MIN 2

struct BTreeNode {
    int               count;
    int               key[MAX + 1];
    struct BTreeNode* linker[MAX + 1];
};

struct BTreeNode* root;

// Node creation
struct BTreeNode* createNode(int key, struct BTreeNode* child) {
    struct BTreeNode* newNode;
    newNode            = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->key[1]    = key;
    newNode->count     = 1;
    newNode->linker[0] = root;
    newNode->linker[1] = child;
    return newNode;
}

// Add value to the node
void addValToNode(int key, int pos, struct BTreeNode* node, struct BTreeNode* child) {
    int j = node->count;
    while (j > pos) {
        node->key[j + 1]    = node->key[j];
        node->linker[j + 1] = node->linker[j];
        j--;
    }
    node->key[j + 1]    = key;
    node->linker[j + 1] = child;
    node->count++;
}

// Split the node
void splitNode(int key, int* pval, int pos, struct BTreeNode* node, struct BTreeNode* child, struct BTreeNode** newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    j        = median + 1;
    while (j <= MAX) {
        (*newNode)->key[j - median]    = node->key[j];
        (*newNode)->linker[j - median] = node->linker[j];
        j++;
    }
    node->count       = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        addValToNode(key, pos, node, child);
    } else {
        addValToNode(key, pos - median, *newNode, child);
    }
    *pval                 = node->key[node->count];
    (*newNode)->linker[0] = node->linker[node->count];
    node->count--;
}

// Set the value in the node
int setValueInNode(int key, int* pval, struct BTreeNode* node, struct BTreeNode** child) {
    int pos;
    if (!node) {
        *pval  = key;
        *child = NULL;
        return 1;
    }

    if (key < node->key[1]) {
        pos = 0;
    } else {
        for (pos = node->count;
             (key < node->key[pos] && pos > 1); pos--)
            ;
        if (key == node->key[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValueInNode(key, pval, node->linker[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insertion operation
void insertion(int key) {
    int               flag, i;
    struct BTreeNode* child;

    flag = setValueInNode(key, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

// Copy the successor
void copySuccessor(struct BTreeNode* myNode, int pos) {
    struct BTreeNode* dummy;
    dummy = myNode->linker[pos];

    for (; dummy->linker[0] != NULL;)
        dummy = dummy->linker[0];
    myNode->key[pos] = dummy->key[1];
}

// Remove the value
void removeVal(struct BTreeNode* myNode, int pos) {
    int i = pos + 1;
    while (i <= myNode->count) {
        myNode->key[i - 1]    = myNode->key[i];
        myNode->linker[i - 1] = myNode->linker[i];
        i++;
    }
    myNode->count--;
}

// Do right shift
void rightShift(struct BTreeNode* myNode, int pos) {
    struct BTreeNode* x = myNode->linker[pos];
    int               j = x->count;

    while (j > 0) {
        x->key[j + 1]    = x->key[j];
        x->linker[j + 1] = x->linker[j];
    }
    x->key[1]    = myNode->key[pos];
    x->linker[1] = x->linker[0];
    x->count++;

    x                   = myNode->linker[pos - 1];
    myNode->key[pos]    = x->key[x->count];
    myNode->linker[pos] = x->linker[x->count];
    x->count--;
    return;
}

// Do left shift
void leftShift(struct BTreeNode* myNode, int pos) {
    int               j = 1;
    struct BTreeNode* x = myNode->linker[pos - 1];

    x->count++;
    x->key[x->count]    = myNode->key[pos];
    x->linker[x->count] = myNode->linker[pos]->linker[0];

    x                = myNode->linker[pos];
    myNode->key[pos] = x->key[1];
    x->linker[0]     = x->linker[1];
    x->count--;

    while (j <= x->count) {
        x->key[j]    = x->key[j + 1];
        x->linker[j] = x->linker[j + 1];
        j++;
    }
    return;
}

// Merge the nodes
void mergeNodes(struct BTreeNode* myNode, int pos) {
    int               j  = 1;
    struct BTreeNode *x1 = myNode->linker[pos], *x2 = myNode->linker[pos - 1];

    x2->count++;
    x2->key[x2->count]    = myNode->key[pos];
    x2->linker[x2->count] = myNode->linker[0];

    while (j <= x1->count) {
        x2->count++;
        x2->key[x2->count]    = x1->key[j];
        x2->linker[x2->count] = x1->linker[j];
        j++;
    }

    j = pos;
    while (j < myNode->count) {
        myNode->key[j]    = myNode->key[j + 1];
        myNode->linker[j] = myNode->linker[j + 1];
        j++;
    }
    myNode->count--;
    free(x1);
}

// Adjust the node
void adjustNode(struct BTreeNode* myNode, int pos) {
    if (!pos) {
        if (myNode->linker[1]->count > MIN) {
            leftShift(myNode, 1);
        } else {
            mergeNodes(myNode, 1);
        }
    } else {
        if (myNode->count != pos) {
            if (myNode->linker[pos - 1]->count > MIN) {
                rightShift(myNode, pos);
            } else {
                if (myNode->linker[pos + 1]->count > MIN) {
                    leftShift(myNode, pos + 1);
                } else {
                    mergeNodes(myNode, pos);
                }
            }
        } else {
            if (myNode->linker[pos - 1]->count > MIN)
                rightShift(myNode, pos);
            else
                mergeNodes(myNode, pos);
        }
    }
}

// Delete a value from the node
int delValFromNode(int key, struct BTreeNode* myNode) {
    int pos, flag = 0;
    if (myNode) {
        if (key < myNode->key[1]) {
            pos  = 0;
            flag = 0;
        } else {
            for (pos = myNode->count; (key < myNode->key[pos] && pos > 1); pos--)
                ;
            if (key == myNode->key[pos]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
        if (flag) {
            if (myNode->linker[pos - 1]) {
                copySuccessor(myNode, pos);
                flag = delValFromNode(myNode->key[pos], myNode->linker[pos]);
                if (flag == 0) {
                    printf("Given data is not present in B-Tree\n");
                }
            } else {
                removeVal(myNode, pos);
            }
        } else {
            flag = delValFromNode(key, myNode->linker[pos]);
        }
        if (myNode->linker[pos]) {
            if (myNode->linker[pos]->count < MIN)
                adjustNode(myNode, pos);
        }
    }
    return flag;
}

// Delete operaiton
void deleteNode(int key, struct BTreeNode* myNode) {
    struct BTreeNode* tmp;
    if (!delValFromNode(key, myNode)) {
        printf("Not present\n");
        return;
    } else {
        if (myNode->count == 0) {
            tmp    = myNode;
            myNode = myNode->linker[0];
            free(tmp);
        }
    }
    root = myNode;
    return;
}

void searching(int key, int* pos, struct BTreeNode* myNode) {
    if (!myNode) {
        return;
    }

    if (key < myNode->key[1]) {
        *pos = 0;
    } else {
        for (*pos = myNode->count;
             (key < myNode->key[*pos] && *pos > 1); (*pos)--)
            ;
        if (key == myNode->key[*pos]) {
            printf("%d present in B-tree", key);
            return;
        }
    }
    searching(key, pos, myNode->linker[*pos]);
    return;
}

void traversal(struct BTreeNode* myNode) {
    int i;
    if (myNode) {
        for (i = 0; i < myNode->count; i++) {
            traversal(myNode->linker[i]);
            printf("%d ", myNode->key[i + 1]);
        }
        traversal(myNode->linker[i]);
    }
}

int main() {

    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int size    = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++) {
        insertion(array[i]);
    }

    traversal(root);
    printf("\n");

    // deleteNode(20, root);
    // printf("\n");
    // traversal(root);
}