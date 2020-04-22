#include <stdio.h>

void InsertSort(int array[],int size){
	int i,j;
	int key=array[0];
    for(i=1;i<size;i++){				//依次插入array[1]，…，array[n]
    	if(array[i]<array[i-1]){		//若array[i]大于等于有序区中所有的array，则array[i],应在原有位置上
			key=array[i];				//array[0]是哨兵，且是array[i]的副本 
			j=i-1; 						
		    do{ 						//从右向左在有序区array[1．．i-1]中查找array[i]的插入位置 
		        array[j+1]=array[j]; 	//将关键字大于array[i]的记录后移 
		        j--;
	        }while(key<array[j]);  		//当array[i]≥array[j]时终止 
	    	array[j+1]=key; 			//array[i]插入到正确的位置上 
		}
		
		//打印每次排序结果 
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
	
	InsertSort(array,size);
	return 0;
}
