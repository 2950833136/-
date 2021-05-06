#include <stdio.h>

void display(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int array[], int x, int y) {
    int key  = array[y];
    array[y] = array[x];
    array[x] = key;
}

// //重的往下沉
// void BubbleSort(int array[], int size) {
//     // 外循环为排序趟数，size 个数进行 size-1 趟
//     // 内循环为每趟比较的次数，第 i 趟比较 size-1-i 次
//     for (int i = 0; i < size - 1; i++) {
//         for (int j = 0; j < size - 1 - i; j++) {
//             if (array[j] > array[j + 1]) {
//                 swap(array, j, j + 1);
//             }
//         }
//         // 打印每次排序
//         display(array, size);
//     }
// }

// // 轻的往上浮
// void BubbleSort2(int array[], int size) {
//     for (int i = 0; i < size - 1; i++) {
//         for (int j = size - 1; j > i; j--) {
//             if (array[j] < array[j - 1]) {
//                 swap(array, j, j - 1);
//             }
//         }
//         // 打印每次排序
//         display(array, size);
//     }
// }

void BubbleSortBetter(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // 以 flag 作为标志，如果遍历完没有改变说明有序不再遍历排序
        int flag = 1;
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
        // 打印每次排序
        display(array, size);
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 76, 13, 27, 49, 10};
    int size    = sizeof(array) / sizeof(int);

    // 打印原始数据
    printf("%d \n", size);
    display(array, size);
    BubbleSortBetter(array, size);

    return 0;
}
