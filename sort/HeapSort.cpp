#include <stdio.h>

void swap(int array[],int x,int y){
	int key;
	key=array[x];
	array[x]=array[y];
	array[y]=key;
}

//从大到小排序 
//void Down(int array[],int i,int n){
//	int child=2*i+1;
//	int key=array[i];
//	while (child<n){
//		if (array[child]>array[child+1] && child+1<n) {
//			child++;
//		}
//		if (key>array[child]){
//			swap(array, i, child);
//			i=child;
//		}
//		else{
//			break;
//		}
//		child=child*2+1;
//	}
//}

//从小到大排序
void Down(int array[],int i,int n){						//最后结果就是大顶堆 
	int parent=i;										//父节点下标
	int child=2*i+1;									//子节点下标  
	while (child<n){
		if (array[child]<array[child+1] && child+1<n) {	//判断子节点那个大，大的与父节点比较 
			child++;
		}
		
		if (array[parent]<array[child]){				//判断父节点是否小于子节点 
			swap(array, parent, child);					//交换父节点和子节点 
			parent=child;								//子节点下标 赋给 父节点下标 
		}

		child=child*2+1;								//换行，比较下面的父节点和子节点 
	}
}

void BuildHeap(int array[],int size)
{
   int i=0;												//倒数第二排开始 
   for(i=size/2-1;i>=0;i--){							//创建大顶堆，必须从下往上比较 
      Down(array,i,size);								//否则有的不符合大顶堆定义 
  	}
}

void HeapSort(int array[],int size){
    BuildHeap(array,size);								//初始化堆 
    printf("初始化数组：");
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	
    for(int i=size-1;i>0;i--)
    {	
    	swap(array,0,i);								//交换顶点和第 i 个数据 
    	//因为只有array[0]改变，其它都符合大顶堆的定义，所以可以从上往下重新建立 
    	Down(array,0,i);								//重新建立大顶堆 
    	
    	printf("排序的数组：");
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
	printf("排序前数组：");
		for(int i=0;i<size;i++){
			printf("%d ",array[i]);
		}
	printf("\n");
	HeapSort(array,size);
	
	return 0;
}
