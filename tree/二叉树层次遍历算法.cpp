#define _CRT_SECURE_NO_WARNINGS				//VS���Ծ��棬����Ӧ�ò���Ҫ

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_SIZE	1024
#define STR_SIZE	1024
#define SPACE		6

typedef struct Node {						//���������
	struct Node* lchild;					//ָ�����ӽڵ�
	char data;								//����Ԫ��
	struct Node* rchild;					//ָ���Һ��ӽڵ� 
}BTNode;									//struct Node �ı���						 

typedef struct Quene {						//����˳��� 
	int front;								//��ͷָ�� 
	BTNode* data[MAX_SIZE];					//��Ŷ���Ԫ�� 
	int rear;								//��βָ�� 
}SqQueue; 									//struct Queue �ı��� 

//��ʼ������ 
void initQueue(SqQueue*& q) {
	q = (SqQueue*)malloc(sizeof(SqQueue));	//����һ���ռ� 
	q->front = q->rear = -1;				//�� -1 
}

//�ж϶����Ƿ�Ϊ��
bool emptyQueue(SqQueue*& q) {
	if (q->front == q->rear) {				//��ָ���βָ����ȣ�˵��Ϊ�� 
		return true;						//������ 
	}
	else {
		return false;						//���ؼ� 
	}
}

//������
bool enQueue(SqQueue*& q, BTNode*& BT) {
	if (q->rear == MAX_SIZE - 1) {			//�ж϶����Ƿ����� 
		return false;						//���ؼ� 
	}
	q->rear++;								//ͷָ��� 1 
	q->data[q->rear] = BT;					//��ֵ 
	return true;							//������ 
}

//������ 
bool deQueue(SqQueue*& q, BTNode*& BT) {
	if (q->front == q->rear) {				//�ж��Ƿ���� 
		return false;						//���ؼ� 
	}
	q->front++;								//βָ��� 1 
	BT = q->data[q->front];					//ȡֵ 
	return true;							//������ 
}

//���������� 
int createBTNode(BTNode*& BT, char* str, int n) {
	char ch = str[n];								//�ѵ� n ���ַ�����ch,��������ж� 
	n = n + 1;
	if (ch != '\0') {								//��� ch �����ڽ������ͼ�������������ͽ��� 
		if (ch == '#') {							//�� # �Ŵ��� NULL������û���� 
			BT = NULL;
		}
		else {
			BT = new BTNode;						//�½�һ�������� 
			BT->data = ch;							//���ַ���������� 
			n = createBTNode(BT->lchild, str, n); 	//��ݹ鴴�� 
			n = createBTNode(BT->rchild, str, n);	//�ҵݹ鴴�� 
		}
	}
	return n;										//���� n,��¼�ַ���ʹ�õ������� 
}
//����ָ�봴��
//void createBTNode2(BTNode** BT) {
//	char ch;
//	ch = getchar();
//	if (ch == '#') {
//		*BT = NULL;
//	}
//	else {
//		if (!(*BT = (BTNode*)malloc(sizeof(BTNode)))) {
//			printf("�ڴ����ʧ�ܣ�");
//			return;
//		}
//		else {
//			(*BT)->data = ch;
//			createBTNode(&((*BT)->lchild));		//����ɹ�����Ž�����������������
//			createBTNode(&((*BT)->rchild));
//		}
//	}
//}

//�������
void preOrder(BTNode*& BT) {
	if (BT != NULL) {				//�жϲ�Ϊ�� 
		printf("%c", BT->data);		//���ʸ��ڵ�
		preOrder(BT->lchild);		//�ݹ飬������������� 
		preOrder(BT->rchild);		//�ݹ飬������������� 
	}
}

//�������
void inOrder(BTNode*& BT) {
	if (BT != NULL) {
		inOrder(BT->lchild);
		printf("%c", BT->data);
		inOrder(BT->rchild);
	}
}

//�������
void postOrder(BTNode*& BT) {
	if (BT != NULL) {
		postOrder(BT->lchild);
		postOrder(BT->rchild);
		printf("%c", BT->data);
	}
}

//��α��� 
void levelOrder(BTNode*& BT) {
	SqQueue* q;									//������� 
	initQueue(q);								//��ʼ������ 
	if (BT != NULL) {
		enQueue(q, BT);							//���ڵ�ָ������� 
	}
	while (emptyQueue(q) != true) {				//�Ӳ�Ϊ��ѭ�� 
		deQueue(q, BT);							//����ʱ�Ľڵ� 
		printf("%c", BT->data);					//����ڵ�洢��ֵ 
		if (BT->lchild != NULL) {				//������ʱ���ýڵ������ 
			enQueue(q, BT->lchild);
		}
		if (BT->rchild != NULL) {				//���Һ���ʱ���ýڵ������ 
			enQueue(q, BT->rchild);
		}										//һ��һ��İѽڵ������� 
	} 											//��û�к��ӽڵ�ʱ�Ͳ���ѭ�� 
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : ˮƽ����
* @input :
*   root: ��
*	left: �ж�����
*	str : �ɱ��ַ���
* @output:
*   none: none
*****************************************************************************/
void draw_level(BTNode* root, bool left, char* str) {
	if (root->rchild) {
		draw_level(root->rchild, false, strcat(str, (left ? "|     " : "      ")));
	}

	printf("%s", str);
	printf("%c", (left ? '\\' : '/'));
	printf("-----");
	printf("%c\n", root->data);

	if (root->lchild) {
		draw_level(root->lchild, true, strcat(str, (left ? "      " : "|     ")));
	}

	str[strlen(str) - SPACE] = '\0';
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : ���ڵ㻭��
* @input :
*   root : ��
* @output:
*   none : none
*****************************************************************************/
void draw(BTNode* root) {
	char str[STR_SIZE];
	memset(str, '\0', STR_SIZE);

	if (root->rchild) {
		draw_level(root->rchild, false, str);
	}
	printf("%c\n", root->data);
	if (root->lchild) {
		draw_level(root->lchild, true, str);
	}
}

int main() {

	//���ӣ�ABDH###E##CF##G##
	BTNode* BT;
	printf("�����ַ�����");
	char* str = (char*)malloc(sizeof(char) * STR_SIZE);
	scanf("%s", str);

	if (strlen(str) == createBTNode(BT, str, 0)) {
		printf("�����������ɹ�\n");
	}
	//createBTNode2(&BT);

	draw(BT);

	printf("������������");
	preOrder(BT);
	printf("\n");

	printf("������������");
	inOrder(BT);
	printf("\n");

	printf("������������");
	postOrder(BT);
	printf("\n");

	printf("������������");
	levelOrder(BT);
	printf("\n");

	return 0;
}
