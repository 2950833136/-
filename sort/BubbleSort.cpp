#include <stdio.h>

void swap(int array[], int x, int y) {
    int key;
    key = array[y];
    array[y] = array[x];
    array[x] = key;
}

void BubbleSort(int array[], int size) {
    //重的往下沉
    //外循环为排序趟数，size个数进行size-1趟
    //内循环为每趟比较的次数，第i趟比较size-1-i次
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
            }
        }

        //打印每次排序
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    //轻的往上浮
    //	for(int i=0;i<size-1;i++){
    //		for(int j=size-1;j>i;j--){
    //			if(array[j]<array[j-1]){
    //				swap(array,j,j-1);
    //			}
    //		}
    //
    //		//打印每次排序
    //		for(int i=0;i<size;i++){
    //			printf("%d ",array[i]);
    //		}
    //		printf("\n");
    //	}
}

int main() {
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size = sizeof(array) / sizeof(int);
    printf("%d \n", size);
    //打印原始数据
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    BubbleSort(array, size);
    return 0;
}
