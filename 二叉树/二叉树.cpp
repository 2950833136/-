#include<iostream>
using namespace std;

typedef struct Node{
	struct Node *lchild;			//ָ�����ӽڵ�
	char data;						//����Ԫ��
	struct Node *rchild;			//ָ���Һ��ӽڵ� 
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

//�������
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
	cout<<"�����ַ�����";
    createBTNode(BT);
    cout<<"�����������ɹ�"<<endl;
    
    cout<<"������������";
    preOrder(BT);
	
	return 0;
} 
