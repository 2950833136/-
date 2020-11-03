#include <stdio.h>

void swap(int array[],int x,int y){
	int key;
	key=array[y];
	array[y]=array[x];
	array[x]=key;
} 

void SelectSort(int array[],int size){
	//��ѭ��Ϊ����������size��������size-1��
	//��ѭ��Ϊÿ�˱ȽϵĴ���
	for(int i=0;i<size-1;i++){
		//Ĭ���±���С��Ϊ��ʼ���ݣ���¼�±�key��
		int key=i; 
		for(int j=i+1;j<size;j++){
			//��������С�ģ���¼�����±� 
			if(array[j]<array[key]){
				key=j;
			}
		}
		//�������ݣ�����С�Ľ���������λ�� 
		swap(array,i,key);
		
		//��ӡÿ������ 
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
	//��ӡԭʼ���� 
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	SelectSort(array,size);
	return 0;
}
