#include <stdio.h>

void swap(int array[],int x,int y){
	int key;
	key=array[y];
	array[y]=array[x];
	array[x]=key;
} 

void BubbleSort(int array[],int size){
	//�ص����³�
	//��ѭ��Ϊ����������size��������size-1��
	//��ѭ��Ϊÿ�˱ȽϵĴ�������i�˱Ƚ�size-1-i��
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-1-i;j++){
			if(array[j]>array[j+1]){
				swap(array,j,j+1);
			}
		}
		
		//��ӡÿ������
		for(int i=0;i<size;i++){
			printf("%d ",array[i]);
		}
		printf("\n");
	}
	
	//������ϸ� 
//	for(int i=0;i<size-1;i++){
//		for(int j=size-1;j>i;j--){
//			if(array[j]<array[j-1]){
//				swap(array,j,j-1);
//			}
//		}
//		
//		//��ӡÿ������
//		for(int i=0;i<size;i++){
//			printf("%d ",array[i]);
//		}
//		printf("\n");
//	}
}

int main(){
	int array[]={49,38,65,97,76,13,27,49,10};
	int size= sizeof(array) / sizeof(int);
	printf("%d \n",size);
	//��ӡԭʼ���� 
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	BubbleSort(array,size);
	return 0;
}
