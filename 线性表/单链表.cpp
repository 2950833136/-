#include<stdio.h>
#include<malloc.h>

typedef struct node {
	int data;									//�������
	struct node* next;							//��һ���ڵ�
}ListNode;										//���ڵ�����

//��ʼ�����Ա�
void InitList(ListNode*& L) {
	L = (ListNode*)malloc(sizeof(ListNode));
	L->next = NULL;								//����ͷ��㣬�� next ����Ϊ NULL 
}

//����������
//ͷ�巨
void CreateListF(ListNode*& L, int array[], int n) {
	ListNode* s;
	L = (ListNode*)malloc(sizeof(ListNode));
	L->next = NULL;								//����ͷ��㣬�� next ����Ϊ NULL
	for (int i = 0; i < n; i++) {				//ѭ���������ݽڵ� s 
		s = (ListNode*)malloc(sizeof(ListNode));
		s->data = array[i];						//��ֵ 
		s->next = L->next;						//����� s ���뵽ԭ�׽��֮ǰ��ͷ���֮�� 
		L->next = s;
	}
}
//β�巨
void CreateListR(ListNode*& L, int array[], int n) {
	ListNode* s, * r;
	L = (ListNode*)malloc(sizeof(ListNode));	//����ͷ���
	r = L;										//r ʼ��ָ��β��㣬��ʼʱָ��ͷ��� ��ͷ������Ϊ 0�� 
	for (int i = 0; i < n; i++) {				//ѭ���������ݽڵ� s
		s = (ListNode*)malloc(sizeof(ListNode));
		s->data = array[i];						//��ֵ 
		r->next = s;							//����� s ���뵽��� r ֮�� 
		r = s;
	}
	r->next = NULL;								//β����� next ����Ϊ NULL 
}

//�������Ա�
void DestroyList(ListNode*& L) {
	ListNode* pre = L, * p = L->next;			//pre ָ���� p ��ǰ���ڵ� 
	while (p != NULL) {							//ɨ�赥���� L 
		free(pre);								//�ͷ� pre ��� 
		pre = p;								//pre��p ͬ������һ����� 
		p = pre->next;
	}
	free(pre);									//ѭ������ʱ p Ϊ NULL��preָ��β����ͷ��� 
}

//�ж��Ƿ�Ϊ��
bool ListEmpty(ListNode* L) {
	return L->next == NULL;
}

//�����Ա�ĳ���
int ListLength(ListNode* L) {
	int n = 0;
	ListNode* p = L;							//p ָ��ͷ��㣬n��Ϊ0 
	while (p->next != NULL) {					//��Ϊ�գ����α��� 
		n++;
		p = p->next;
	}
	return n;									//���س��� 
}

//������Ա�
void Display(ListNode* L) {
	ListNode* p = L->next;						//p ָ���׽�� ���׽�����Ϊ 1�� 
	while (p != NULL) {							//��Ϊ�գ����α��� 
		printf("%d ", p->data);
		p = p->next;							//p ������һ���ڵ� 
	}
	printf("\n");
}

//����ĳ������Ԫ��ֵ
bool GetData(ListNode* L, int i, int& data) {
	ListNode* p = L->next;						//p ָ���׽�� ���׽�����Ϊ 1�� 
	if (i <= 0) {								//i ���󷵻ؼ� 
		return false;
	}
	int j = 0;
	while (j < i - 1 && p != NULL) {			//�ҵ� i ����� p 
		j++;
		p = p->next;
	}
	if (p == NULL) {							//������ 
		return 0;
	}
	else {										//���ڷ��� true 
		data = p->data;
		return true;
	}
}

//��Ԫ��ֵ���� 
int LocateData(ListNode* L, int data) {
	int i = 1;
	ListNode* p = L->next;						//p ָ��ͷ��� ��i ��Ϊ 1���׽�����Ϊ 1�� 
	while (p != NULL && p->data != data) {		//���� data ֵ�������Ϊ i 
		p = p->next;
		i++;
	}
	if (p == NULL) {							//������ 
		return false;
	}
	else {										//���ڲ�������� i 
		return i;
	}
}

//��������Ԫ��
bool ListInsert(ListNode*& L, int i, int data) {
	ListNode* p = L, * s;						//p ָ��ͷ��� ��ͷ������Ϊ 0�� 
	if (i <= 0) {								//i ���󷵻ؼ� 
		return false;
	}
	int j = 0;									//j ��Ϊ 0 
	while (j < i - 1 && p != NULL) {			//���ҵ� i-1 ����� p 
		j++;
		p = p->next;
	}
	if (p == NULL) {							//δ�ҵ� 
		return false;
	}
	else {										//�ҵ��� i-1 ����� p ,�����½�㲢���� true 
		s = (ListNode*)malloc(sizeof(ListNode));
		s->data = data;							//�����½�� s,��ֵΪ data 
		s->next = p->next;						//ͷ�巨 
		p->next = s;
		return true;
	}
}

//ɾ������Ԫ�� 
bool ListDelete(ListNode*& L, int i, int& data) {
	ListNode* p = L, * q;						//p ָ��ͷ��� ��ͷ������Ϊ 0�� 
	if (i <= 0) {								//i ���󷵻ؼ� 
		return false;
	}
	int j = 0;									//j ��Ϊ 0 
	while (j < i - 1 && p != NULL) {			//���ҵ� i ����� p 
		j++;
		p = p->next;
	}
	if (p == NULL) {							//δ�ҵ� 
		return false;
	}
	else {										//�ҵ��� i-1 ����� p 
		q = p->next;							//q ָ��� i ����� 
		if (q == NULL) {						//�������ڵ� i ����� 
			return false;
		}
		data = q->data;
		p->next = q->next;						//ɾ�� q ��㣬�� i-1 ����� ָ��� i+1 ����� 
		free(q);								//�ͷ� q ��� 
		return true;
	}
}

int main() {
	int array[] = { 1,3,5,7,9 };
	int n = sizeof(array) / sizeof(int);
	ListNode* L = (ListNode*)malloc(sizeof(ListNode));
	CreateListR(L, array, n);
	printf("����������ɹ�!\n");
	printf("���������Ϊ��");
	Display(L);
	//	DestroyList(L);
	int i = 5, j = 0;
	GetData(L, i, j);
	printf("���ҵ�%d��Ԫ��ֵΪ%d\n", i, j);
	int x = 9;
	int num = LocateData(L, x);
	printf("����Ԫ��ֵ%d�ǵ�%d��Ԫ��\n", x, num);
	ListInsert(L, 6, 11);
	printf("����ɹ�!\n");
	Display(L);
	int y = 0;
	ListDelete(L, 6, y);
	printf("ɾ���ɹ�!\n");
	printf("%d\n", y);
	Display(L);
	return 0;
}
