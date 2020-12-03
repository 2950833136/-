#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>

typedef struct ListNode {
    int       data;
    ListNode* next;
} LN;

// 输出线性表
void displayL(LN* L) {
    LN* p = L;                  // p 指向首结点
    while (p != NULL) {         // 不为空，依次遍历
        printf("%d ", p->data); // 打印
        p = p->next;            // p 移向下一个节点
    }
    printf("\n");
}

// 输出数组
void displayA(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void Merge(LN* head, LN* list) {
    LN* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = list->next;
}

void insert(LN* list, int value) {
    LN* prev = list;
    LN* curr = list->next;
    LN* node = (LN*)malloc(sizeof(LN));

    node->data = value;
    node->next = NULL;
    if (curr == NULL) {
        prev->next = node;
    } else {
        while (curr != NULL && curr->data <= value) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = node;
        node->next = curr;
    }
}

void BucketSort(int array[], int size, int num) {
    LN** buckets = (LN**)malloc(sizeof(LN*) * num);
    for (int i = 0; i < num; i++) {
        *(buckets + i)         = (LN*)malloc(sizeof(LN));
        (*(buckets + i))->next = NULL;
    }

    // 1. 找到最大值和最小值求间隔（桶的大小）
    int max = array[0];
    int min = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }
    int space = ((max - min) / num) + 1;

    // 2. 挨个分桶排序
    for (int i = 0; i < size; i++) {
        int n = (array[i] - min) / space;
        insert(*(buckets + n), array[i]);
    }

    // 3. 合并链表
    LN* head   = (LN*)malloc(sizeof(LN));
    head->next = NULL;
    for (int i = 0; i < num; i++) {
        Merge(head, *(buckets + i));
    }
    head = head->next;
    // displayL(head);

    // 4. 把链表值返回数组
    for (int i = 0; i < size; i++) {
        array[i] = head->data;
        head     = head->next;
    }

    // 3+4. 当然也可以不合并链表，直接把数据返回数组
    // int index = 0;
    // for (int i = 0; i < num; i++) {
    //     if (*(buckets + i) != NULL) {
    //         LN* temp = (*(buckets + i))->next;
    //         while (temp != NULL) {
    //             array[index++] = temp->data;
    //             temp           = temp->next;
    //         }
    //     }
    // }
}

int main() {
    int array[]   = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size      = sizeof(array) / sizeof(int);
    int BUCKETNUM = 5;

    // 打印原始数据
    printf("%d \n", size);
    displayA(array, size);
    BucketSort(array, size, BUCKETNUM);
    displayA(array, size);

    return 0;
}