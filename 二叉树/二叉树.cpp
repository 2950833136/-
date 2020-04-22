#include<iostream>
using namespace std;

typedef struct Node{
	struct Node *lchild;			//指向左孩子节点
	char data;						//数据元素
	struct Node *rchild;			//指向右孩子节点 
}BTNode;

void createBTNode(BTNode * &BT){	
	char ch;
	cin>>ch;
	
	if(ch=='#'){
		BT = NULL;
	}
	else{
		BT = new BTNode;
		BT->data=ch;
		createBTNode(BT->lchild); 
		createBTNode(BT->rchild);
	}
}

//先序遍历
void preOrder(BTNode * &BT)
{
    if(BT!=NULL)
    {
        cout<<BT->data;
        preOrder(BT->lchild);
        preOrder(BT->rchild);
    }
} 


int main(){
	
	BTNode *BT;
	cout<<"输入字符串：";
    createBTNode(BT);
    cout<<"二叉树建立成功"<<endl;
    
    cout<<"先序遍历结果：";
    preOrder(BT);
	
	return 0;
} 
