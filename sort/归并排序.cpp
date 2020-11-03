#include <stdio.h>

//��һ��������ǰ�����飬�ڶ�����ÿ����������� 
void Merge(int array5[],int array6[],int low,int mid,int high){
	int i=low;												//��һ���ʼ�±� 
	int j=mid+1;											//�ڶ����ʼ�±� 
	int k=low;		
	while((i<=mid)&&(j<=high)){								//�жϱ��������ֿ���� 
		if(array5[i]<=array5[j]){							//��һ��� 1 ��ֵ�ȵڶ���� 1 ֵС 
			array6[k]=array5[i];							//��С��ֵ����ڶ������飬����һ��� 1 ��ֵ 
			k++;	i++;									//�ڶ��������±���ƣ���һ�������һ���±���� 
		}
		else{
			array6[k]=array5[j];							//С��ֵ����ڶ������飬���ڶ���� 1 ��ֵ 
			k++;	j++;
		}
	}
	while(i<=mid){											//��һ��û�����꣬���ڶ������������˵����һ��ʣ��ֵ�����ڵڶ��� 
		array6[k]=array5[i];								//ֱ�Ӱ�ʣ���һ�����ݶ�����ڶ������� 
		k++;	i++;	
	} 
	while(j<=high){											//�ڶ���û�����꣬����һ�����������˵���ڶ���ʣ��ֵ�����ڵ�һ�� 
		array6[k]=array5[j];								//ֱ�Ӱ�ʣ��ڶ������ݶ�����ڶ������� 
		k++;	j++;
	} 
}

//��һ��������ǰ�����飬�ڶ�����ÿ����������� 
void MergePass(int array3[],int array4[],int length,int size){
	int i=0;												//iָ���һ���ֿ�鲢����ʼ�� 
	while(i+2*length-1<size){								//�ֿ� 
		Merge(array3,array4,i,i+length-1,i+2*length-1);		//�鲢�ֿ����� 
		i=i+2*length;										//�鲢�����ָ����һ���ֿ����ʼ�� 
	}
	
	if((i+length-1)<size-1){								//ʣ�������飬����һ��С��length 
		Merge(array3,array4,i,i+length-1,size-1);
	}
	else{													//ʣ�·ֿ�Ϊ���� 
		for(int j=i;j<size;j++){
			array4[j]=array3[j];							//��ʣ�����ݸ��Ƶ�array4�� 
		}
	}
}

void MergeSort(int array1[],int size){
	int array2[size]={0};
	int length=1;
	while(length<size){
		
		MergePass(array1,array2,length,size);				//�鲢�������array2�� 
		printf("array2���飺");								//��ӡÿ������ 
		for(int i=0;i<size;i++){
			printf("%d ",array2[i]);
		}
		printf("\n");
		
		length=2*length;									//�ı�鲢���ȣ�һ���Ƕ�·�鲢 
		MergePass(array2,array1,length,size);				//�鲢�������array1�� 
		printf("array1���飺");								//��ӡÿ������ 
		for(int i=0;i<size;i++){
			printf("%d ",array1[i]); 
		}
		printf("\n");
		
		length=2*length;									//�ı�鲢����
	} 
}

int main(){
	int array[]={49,38,65,97,76,13,27,49,10};
	int size= sizeof(array) / sizeof(int);
	printf("%d \n",size);
	printf("ԭ�������飺");
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	MergeSort(array,size);
	return 0;
}
