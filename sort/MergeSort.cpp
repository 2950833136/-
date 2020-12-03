#include <stdio.h>

void display(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 第一个是排序前的数组，第二个是每次排序后数组
void Merge(int array5[], int array6[], int low, int mid, int high) {
    int i = low;                        // 第一块初始下标
    int j = mid + 1;                    // 第二块初始下标
    int k = low;                        // 充当合并块的下标
    while ((i <= mid) && (j <= high)) { // 判断遍历两个分块结束
        if (array5[i] <= array5[j]) {   // 第一块第 1 个值比第二块第 1 值小
            array6[k++] = array5[i++];  // 把小的值存入第二个数组，即第一块第 1 个值
        } else {
            array6[k++] = array5[j++]; // 小的值存入第二个数组，即第二块第 1 个值
        }
    }
    while (i <= mid) {             // 第一块没遍历完，而第二块遍历结束，说明第一块剩余值都大于第二块
        array6[k++] = array5[i++]; // 直接把剩余第一块数据都存入第二个数组
    }
    while (j <= high) {            // 第二块没遍历完，而第一块遍历结束，说明第二块剩余值都大于第一块
        array6[k++] = array5[j++]; // 直接把剩余第二块数据都存入第二个数组
    }
}

// 第一个是排序前的数组，第二个是每次排序后数组
void MergePass(int array3[], int array4[], int length, int size) {
    int i = 0;                                                        // i 指向第一个分块归并的起始点
    while (i + 2 * length - 1 < size) {                               // 分块
        Merge(array3, array4, i, i + length - 1, i + 2 * length - 1); // 归并分块排序
        i = i + 2 * length;                                           // 归并间隔，指向下一个分块的起始点
    }

    if ((i + length - 1) < size - 1) { //剩下两个块，其中一个小于length
        Merge(array3, array4, i, i + length - 1, size - 1);
    } else { //剩下分块为奇数
        for (int j = i; j < size; j++) {
            array4[j] = array3[j]; //将剩余数据复制到array4中
        }
    }
}

void MergeSort(int array1[], int size) {
    int array2[size] = {0};
    int length       = 1;
    while (length < size) {
        MergePass(array1, array2, length, size); // 归并，结果在 array2 中
        length = 2 * length;                     // 改变归并长度，一般是二路归并
        display(array2, size);                   // 打印 array2
        MergePass(array2, array1, length, size); // 归并，结果在 array1 中
        length = 2 * length;                     // 改变归并长度
        display(array1, size);                   // 打印 array1
    }
}

int main() {
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size    = sizeof(array) / sizeof(int);

    // 打印原始数据
    printf("%d \n", size);
    display(array, size);
    MergeSort(array, size);
    return 0;
}
