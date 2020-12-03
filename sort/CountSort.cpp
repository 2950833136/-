#include <malloc.h>
#include <stdio.h>
#include <string.h>

void display(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

/**
 * 1、得到数列的最大值与最小值，并算出差值d
 * 2、创建统计数组并计算统计对应元素个数
 * 3、统计数组变形，后面的元素等于前面的元素之和
 * 4、倒序遍历原始数组，从统计数组找到正确位置，输出到结果数组
 */
void CountSort(int* nums, int numsSize) {
    int min = nums[0], max = nums[0];
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
        if (nums[i] > max) {
            max = nums[i];
        }
    }

    int  space    = max - min + 1;
    int* arrCount = (int*)malloc(sizeof(int) * space);
    for (int i = 0; i < space; i++) {
        arrCount[i] = 0;
    }
    for (int i = 0; i < numsSize; i++) {
        arrCount[nums[i] - min]++;
    }
    display(arrCount, space);

    for (int i = 1; i < space; i++) {
        arrCount[i] += arrCount[i - 1];
    }
    display(arrCount, space);

    int* arrSort = (int*)malloc(sizeof(int) * numsSize);
    for (int i = numsSize - 1; i >= 0; i--) {
        arrSort[arrCount[nums[i] - min] - 1] = nums[i];
        arrCount[nums[i] - min]--;
    }
    display(arrSort, numsSize);
}

int main() {
    int array[] = {1, 1, 5, 5, 2};
    int size    = sizeof(array) / sizeof(array[0]);

    display(array, size);
    CountSort(array, size);

    return 0;
}