#include <stdio.h>

void InsertSort(int array[],int size){
	int i,j;
	int key=array[0];
    for(i=1;i<size;i++){				//���β���array[1]������array[n]
    	if(array[i]<array[i-1]){		//��array[i]���ڵ��������������е�array����array[i],Ӧ��ԭ��λ����
			key=array[i];				//array[0]���ڱ�������array[i]�ĸ��� 
			j=i-1; 						
		    do{ 						//����������������array[1����i-1]�в���array[i]�Ĳ���λ�� 
		        array[j+1]=array[j]; 	//���ؼ��ִ���array[i]�ļ�¼���� 
		        j--;
	        }while(key<array[j]);  		//��array[i]��array[j]ʱ��ֹ 
	    	array[j+1]=key; 			//array[i]���뵽��ȷ��λ���� 
		}
		
		//��ӡÿ�������� 
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
	
	InsertSort(array,size);
	return 0;
}
