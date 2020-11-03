#include <stdio.h>
#include <stdlib.h>

int getStandard(int array[], int low, int high) {
	//��׼���� 
	int key = array[low];
	while (low < high) {
		//��ΪĬ�ϻ�׼�Ǵ���߿�ʼ�����Դ��ұ߿�ʼ�Ƚ� 
		//����β��Ԫ�ش��ڵ��� ��׼���� ʱ,��һֱ��ǰŲ��highָ�� 
		while (low < high && array[high] >= key) {
			high--;
		}
		//���ҵ��� array[low] С��ʱ���ͰѺ����ֵ array[high] ������ 
		if (low < high) {
			array[low] = array[high];
		}

		//������Ԫ��С�ڵ��� ��׼���� ʱ,��һֱ���Ų��lowָ�� 
		while (low < high && array[low] <= key) {
			low++;
		}
		//���ҵ��� array[high] ���ʱ���Ͱ�ǰ���ֵ array[low] ������
		if (low < high) {
			array[high] = array[low];
		}
	}
	//����ѭ��ʱlow��high���,��ʱ��low��high����key����ȷ����λ��
	//�ѻ�׼���ݸ�����ȷλ�� 
	array[low] = key;

	return low;
}

void quickSort(int array[], int low, int high) {
	//��ʼĬ�ϻ�׼Ϊ	low=0
	if (low < high) {
		//�ֶ�λ���±� 
		int standard = getStandard(array, low, high);

		//�ݹ��������
		//������� 
		quickSort(array, low, standard - 1);
		//�ұ����� 
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

	int size = 25;							//�����С 
	int array[25] = { 0 };					//�����ʼ�� 
	for (int i = 0; i < 100; i++) {			//100��������� 
		for (int j = 0; j < size; j++) {
			array[j] = rand() % 1000;		//����������� 0~999
		}
		printf("ԭ�������飺");
		display(array, size);
		
		quickSort(array, 0, size - 1);
		
		printf("��������飺");
		display(array, size);
		
		if (check(array, size) == true) {
			printf("����ɹ�\n");
		}
		printf("\n");
	}

	return 0;
}

