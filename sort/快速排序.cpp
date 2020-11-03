#include <stdio.h>
#include <stdlib.h>

int getStandard(int array[], int low, int high) {
	//基准数据 
	int key = array[low];
	while (low < high) {
		//因为默认基准是从左边开始，所以从右边开始比较 
		//当队尾的元素大于等于 基准数据 时,就一直向前挪动high指针 
		while (low < high && array[high] >= key) {
			high--;
		}
		//当找到比 array[low] 小的时，就把后面的值 array[high] 赋给它 
		if (low < high) {
			array[low] = array[high];
		}

		//当队首元素小于等于 基准数据 时,就一直向后挪动low指针 
		while (low < high && array[low] <= key) {
			low++;
		}
		//当找到比 array[high] 大的时，就把前面的值 array[low] 赋给它
		if (low < high) {
			array[high] = array[low];
		}
	}
	//跳出循环时low和high相等,此时的low或high就是key的正确索引位置
	//把基准数据赋给正确位置 
	array[low] = key;

	return low;
}

void quickSort(int array[], int low, int high) {
	//开始默认基准为	low=0
	if (low < high) {
		//分段位置下标 
		int standard = getStandard(array, low, high);

		//递归调用排序
		//左边排序 
		quickSort(array, low, standard - 1);
		//右边排序 
		quickSort(array, standard + 1, high);
	}
}

void display(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

bool check(int array[], int size) {
	bool res = true;
	for (int i = 0; i < size - 1; i++) {
		if (array[i] > array[i + 1]) {
			res = false;
		}
	}
	return res;
}

int main() {
//	int array[] = { 49,38,65,97,76,13,27,49,10 };
//	int size = sizeof(array) / sizeof(int);
//	printf("%d \n", size);
//	quickSort(array, 0, size - 1);

	int size = 25;							//数组大小 
	int array[25] = { 0 };					//数组初始化 
	for (int i = 0; i < 100; i++) {			//100个数组测试 
		for (int j = 0; j < size; j++) {
			array[j] = rand() % 1000;		//随机生成数组 0~999
		}
		printf("原来的数组：");
		display(array, size);
		
		quickSort(array, 0, size - 1);
		
		printf("排序后数组：");
		display(array, size);
		
		if (check(array, size) == true) {
			printf("排序成功\n");
		}
		printf("\n");
	}

	return 0;
}

