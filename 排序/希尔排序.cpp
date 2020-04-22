#include <stdio.h>

void ShellSort(int array[],int size){
	//��ʼ����ʱֵ������
	int key=0;
	int increment=size;
	do { 
		//ÿ�μ�С������ֱ��increment = 1 
		increment = increment / 2; 
		printf("%d\n",increment);
		for (int i=0;i<increment;i++) { 
			//��ÿ�����ֽ���ֱ�Ӳ������� 
			for(int j=i+increment;j<size;j=j+increment){
				if (array[j] < array[j-increment]){ 
					key = array[j];
					int k=j-increment;
					do { 
						//�ƶ�Ԫ�ز�Ѱ��λ�� 
						array[k+increment] = array[k]; 
						k=k-increment;
					} while (key < array[k] && k>=0);
					//����Ԫ�� 
					array[k+increment] = key;
				}
			}
			
			//��ӡÿ�ν�� 
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
	//��ӡԭʼ���� 
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	ShellSort(array,size);
	return 0;
}
