#include <stdio.h>

void display(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void InsertSort(int array[], int size)
{
    // 第 1 个数肯定是有序的，从第 2 个数开始遍历，依次插入有序序列
    for (int i = 1; i < size; i++)
    {
        // 取出第 i 个数，和前 i-1 个数比较后，插入合适位置
        int temp = array[i];
        // 因为前 i-1 个数都是从小到大的有序序列，所以只要当前比较的数 (array[j]) 比 temp 大，就把这个数后移一位
        int j = i - 1;
        // 当 j < 0 或 array[j] < temp(array[i]) 时终止
        while (j >= 0 && array[j] > temp)
        {
            array[j + 1] = array[j]; // 将大于 temp(array[i]) 的数据后移
            j--;                     // 向前比较
        }
        // array[i]插入到正确的位置上
        array[j + 1] = temp;

        // 打印每次排序结果
        display(array, size);
    }
}

int main()
{
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size    = sizeof(array) / sizeof(int);

    // 打印原始数据
    printf("%d \n", size);
    display(array, size);
    InsertSort(array, size);
    return 0;
}
