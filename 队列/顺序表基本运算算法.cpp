#include<stdio.h>
#include<malloc.h>

#define MaxSize 1024

typedef struct Quene {				//����˳��� 
	int front;						//��ͷָ�� 
	char data[MaxSize];				//��Ŷ���Ԫ�� 
	int rear;						//��βָ�� 
}SqQueue; 							//struct Queue �ı���

//��ʼ������ 
void initQueue(SqQueue*& q) {
	q = (SqQueue*)malloc(sizeof(SqQueue));	//����һ���ռ� 
	q->front = q->rear = -1;				//�� -1 
}

//���ٶ���
void destroyQueue(SqQueue*& q) {
	free(q);								//�ͷ��ڴ� 
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
bool enQueue(SqQueue*& q, char c) {
	if (q->rear == MaxSize - 1) {			//�ж϶����Ƿ����� 
		return false;						//���ؼ� 
	}
	q->rear++;								//ͷָ��� 1 
	q->data[q->rear] = c;					//��ֵ 
	return true;							//������ 
}

//������ 
bool deQueue(SqQueue*& q, char ch) {
	if (q->front == q->rear) {				//�ж��Ƿ���� 
		return false;						//���ؼ� 
	}
	q->front++;								//βָ��� 1 
	ch = q->data[q->front];					//ȡֵ 
	printf("%c", ch);						//���ֵ 
	return true;							//������ 
}

int main() {
	SqQueue* Q;
	initQueue(Q);
	printf("��ʼ���ɹ�\n");

	//���ٶ��� 
//	destroyQueue(Q);

	int n = 0;
	char* str = (char*)malloc(sizeof(char) * MaxSize);
	printf("������Ҫ����Ԫ�أ�");
	scanf("%s", str);
	while (n < MaxSize) {
		char c = str[n];
		n++;
		if (c != '\0') {
			enQueue(Q, c);
		}
		else {
			break;
		}
	}
	printf("����ɹ�");
	printf("\n");

	char ch;
	printf("����Ԫ�أ�");
	while (emptyQueue(Q) != true) {			//�ж��Ƿ�Ϊ�� 
		deQueue(Q, ch);
	}

	return 0;
}
