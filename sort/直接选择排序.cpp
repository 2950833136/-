#include <stdio.h>

void swap(int array[],int x,int y){
	int key;
	key=array[y];
	array[y]=array[x];
	array[x]=key;
} 

void SelectSort(int array[],int size){
	//外循环为排序趟数，size个数进行size-1趟
	//内循环为每趟比较的次数
	for(int i=0;i<size-1;i++){
		//默认下标最小的为开始数据，记录下标key。
		int key=i; 
		for(int j=i+1;j<size;j++){
			//碰到比它小的，记录覆盖下标 
			if(array[j]<array[key]){
				key=j;
			}
		}
		//交换数据，把最小的交换到排序位置 
		swap(array,i,key);
		
		//打印每次排序 
		for(int i=0;i<size;i++){
			printf("%d ",array[i]);
		}
		printf("\n");
	}
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
	SelectSort(array,size);
	return 0;
}
