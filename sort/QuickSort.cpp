#include <stdio.h>
#include <stdlib.h>

void display(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int getStandard(int array[], int i, int j) {
    //基准数据
    int key = array[i];
    while (i < j) {
        //因为默认基准是从左边开始，所以从右边开始比较
        //当队尾的元素大于等于基准数据 时,就一直向前挪动 j 指针
        while (i < j && array[j] >= key) {
            j--;
        }
        //当找到比 array[i] 小的时，就把后面的值 array[j] 赋给它
        if (i < j) {
            array[i] = array[j];
        }
        //当队首元素小于等于基准数据 时,就一直向后挪动 i 指针
        while (i < j && array[i] <= key) {
            i++;
        }
        //当找到比 array[j] 大的时，就把前面的值 array[i] 赋给它
        if (i < j) {
            array[j] = array[i];
        }
    }
    //跳出循环时 i 和 j 相等,此时的 i 或 j 就是 key 的正确索引位置
    //把基准数据赋给正确位置
    array[i] = key;
    return i;
}

void QuickSort(int array[], int low, int high) {
    //开始默认基准为 low
    if (low < high) {
        //分段位置下标
        int standard = getStandard(array, low, high);
        //递归调用排序
        //左边排序
        QuickSort(array, low, standard - 1);
        //右边排序
        QuickSort(array, standard + 1, high);
    }
}

// 合并到一起快速排序
// void QuickSort(int array[], int low, int high) {
//     int i   = low;
//     int j   = high;
//     int key = array[i];
//     if (low < high) {
//         while (i < j) {
//             while (i < j && array[j] >= key) {
//                 j--;
//             }
//             if (i < j) {
//                 array[i] = array[j];
//             }
//             while (i < j && array[i] <= key) {
//                 i++;
//             }
//             if (i < j) {
//                 array[j] = array[i];
//             }
//         }
//         array[i]     = key;
//         int standard = i;
//         QuickSort(array, low, standard - 1);
//         QuickSort(array, standard + 1, high);
//     }
// }

int main() {
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size    = sizeof(array) / sizeof(int);
    printf("%d \n", size);
    QuickSort(array, 0, size - 1);
    display(array, size);

    // int size      = 20;
    // int array[20] = {0};                 //数组初始化
    // for (int i = 0; i < 10; i++) {       //数组个数
    //     for (int j = 0; j < size; j++) { //数组大小
    //         array[j] = rand() % 1000;    //随机生成数大小 0~99
    //     }
    //     printf("原来的数组：");
    //     display(array, size);
    //     QuickSort(array, 0, size - 1);
    //     printf("排序后数组：");
    //     display(array, size);
    //     printf("\n");
    // }

    return 0;
}