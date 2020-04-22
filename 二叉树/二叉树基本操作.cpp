#include<stdio.h>
#include<malloc.h>

typedef struct node{
	struct node *lchild;			//ָ�����ӽڵ�
	char data;						//����Ԫ��
	struct node *rchild;			//ָ���Һ��ӽڵ� 
}BTNode;

//���������� 
int createBTNode(BTNode * &BT,char *str,int n){	
	printf("%d ",n);
	char ch=str[n];								//�ѵ� n ���ַ�����ch,��������ж� 
	printf("%c \n",ch);
	n=n+1;
	if(ch!='\0'){								//��� ch �����ڽ������ͼ�������������ͽ��� 
		if( ch=='#'){							//�� # �Ŵ��� NULL������û���� 
			BT = NULL;
		}
		else{
			BT = new BTNode;					//�½�һ�������� 
			BT->data=ch;						//���ַ���������� 
			n=createBTNode(BT->lchild,str,n); 	//��ݹ鴴�� 
			n=createBTNode(BT->rchild,str,n);	//�ҵݹ鴴�� 
		}
	}
	return n;									//���� n,��¼�ַ���ʹ�õ������� 
}

//���ٶ�����
void destroyBTNode(BTNode * &BT){
	if(BT!=NULL){
		destroyBTNode(BT->lchild);				//��ݹ��ͷ��ڴ� 
		destroyBTNode(BT->rchild);				//�ҵݹ��ͷ��ڴ� 
		
		/*
			free()�ͷŵ���ָ��ָ����ڴ棡ע�⣡�ͷŵ����ڴ棬����ָ�룡���ǳ��ǳ���Ҫ��
			ָ����һ��������ֻ�г������ʱ�ű����١��ͷ��ڴ�ռ䡣 
			ԭ��ָ�����ռ��ָ�뻹�Ǵ��ڣ�ֻ��������ָ��ָ���������δ����ġ�
			��ˣ��ͷ��ڴ���ָ��ָ��NULL����ָֹ���ں��治С���ֱ������ˡ��ǳ���Ҫ����һ�㣡
		*/
		free(BT);
		BT=NULL; 
	}
}

//���ҽ�� 
BTNode *findBTNode(BTNode * &BT,char ch){
	if(BT==NULL){								//�գ�����Ϊ�ա�NULL 
		return NULL;
	}
	else if(BT->data==ch){						//���ڣ���ʾ���ڲ��������� 
		printf("���ڸýڵ㣺%c",ch); 
		return BT;
	}
	else{
		BTNode *p;								//����һ������ָ�� 
		p=findBTNode(BT->lchild,ch);			//�ݹ��ѯ������ 
		if(p!=NULL){
			return p;							//�������Ѿ��ҵ� 
		}
		else{
			return findBTNode(BT->rchild,ch);	//�ݹ��ѯ������ 
		}
	}
} 

//��߶�
int BTHeight(BTNode * &BT){
	int lchildh;
	int rchildh;
	int h;
	if(BT==NULL){
		return 0;										//�����߶�Ϊ0 
	}
	else{
		lchildh=BTHeight(BT->lchild);					//���������ĸ߶� 
		rchildh=BTHeight(BT->rchild);					//���������ĸ߶� 
		h=(lchildh>rchildh)?(lchildh+1):(rchildh+1);	//�����ĸ߶� 
		return h;
	}
}

//���������
void displayBTNode(BTNode * &BT){
	if(BT!=NULL){
		printf("%c",BT->data);
		if(BT->lchild!=NULL || BT->rchild!=NULL){
			printf("(");
			displayBTNode(BT->lchild);
			printf(",");
			displayBTNode(BT->rchild);
			printf(")");
		}
	}
}
void displayBTNode1(BTNode * &BT){
	if(BT!=NULL){
		printf("%c",BT->data);
		displayBTNode1(BT->lchild);
		displayBTNode1(BT->rchild);
	}
	else{
		printf("#");
	}
}

//�������
void preOrder(BTNode * &BT){
    if(BT!=NULL){					//�жϲ�Ϊ�� 
        printf("%c",BT->data);		//���ʸ��ڵ�
        preOrder(BT->lchild);		//�ݹ飬������������� 
        preOrder(BT->rchild);		//�ݹ飬������������� 
    }
}

//�������
void inOrder(BTNode * &BT){
    if(BT!=NULL){
        inOrder(BT->lchild);
        printf("%c",BT->data);
        inOrder(BT->rchild);
    }
}

//�������
void postOrder(BTNode * &BT){
    if(BT!=NULL){
        postOrder(BT->lchild);
        postOrder(BT->rchild);
        printf("%c",BT->data);
    }
}

int main(){
	
	//���ӣ�ABC###D##
	BTNode *BT;
	printf("�����ַ�����");
	char *str=(char *)malloc(sizeof(char) * 1024);
	scanf("%s",str); 
    createBTNode(BT,str,0);
    printf("�����������ɹ�\n");
    
	destroyBTNode(BT);
	if(BT==NULL){
		printf("���ٳɹ�\n");
	}
    
//	printf("������Ҫ���ҵĽڵ㣺");
//	char c='E';
//	printf("%c\n",c); 
//	if(findBTNode(BT,c)==NULL){
//		printf("û�д˽ڵ�");
//	}
//	printf("\n");
//    
//	int h=BTHeight(BT); 
//	printf("���ĸ߶�Ϊ��%d",h);
//	printf("\n");
//	
//	printf("������Ϊ��"); 
//	displayBTNode(BT);
//	printf("\n");
//	printf("������Ϊ��"); 
//	displayBTNode1(BT);
//	printf("\n");
//	
//	printf("������������");
//	preOrder(BT);
//	printf("\n");
//    
//	printf("������������");
//	inOrder(BT);
//	printf("\n");
//    
//	printf("������������");
//	postOrder(BT);
//	printf("\n");
	
	return 0;
} 
