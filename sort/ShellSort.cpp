#include <stdio.h>

void ShellSort(int array[],int size){
	//初始化临时值，增量
	int key=0;
	int increment=size;
	do { 
		//每次减小增量，直到increment = 1 
		increment = increment / 2; 
		printf("%d\n",increment);
		for (int i=0;i<increment;i++) { 
			//对每个划分进行直接插入排序 
			for(int j=i+increment;j<size;j=j+increment){
				if (array[j] < array[j-increment]){ 
					key = array[j];
					int k=j-increment;
					do { 
						//移动元素并寻找位置 
						array[k+increment] = array[k]; 
						k=k-increment;
					} while (key < array[k] && k>=0);
					//插入元素 
					array[k+increment] = key;
				}
			}
			
			//打印每次结果 
			for(int i=0;i<size;i++){
				printf("%d ",array[i]);
			} 
			printf("\n");
		}	
	} while (increment!=1);
}

int main(){
	int array[]={49,38,65,97,76,13,27,49,10};
	int size= sizeof(array) / sizeof(int);
	printf("%d \n",size);
	//打印原始数据 
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	ShellSort(array,size);
	return 0;
}
