#include<iostream>
#include<malloc.h> 

#define maxsize 100							//���ռ� 
using namespace std;

typedef struct Stack {
	int data[maxsize];
	int top;
}SqStack;									//ջ������

//��ʼ��
void InitStack(SqStack*& s) {
	s = (SqStack*)malloc(sizeof(SqStack));	//����һ��˳��ջ�ռ䣬�׵�ַ����� s �� 
	s->top = -1;							//ջ��ָ����Ϊ -1
}

//����ջ 
void DestroyStack(SqStack*& s) {
	free(s);
}

//�ж��Ƿ��
bool StackEmpty(SqStack* s) {
	return (s->top == -1) ? true : false;
}

//��ջ
bool Push(SqStack*& s, int x) {
	if (s->top == maxsize - 1) {			//ջ�����
		return false;
	}
	else {
		s->top++;							//ջ��ָ���һ
		s->data[s->top] = x;				//Ԫ�� x ����ջ��ָ�봦
		return true;
	}
}

//��ջ 
bool Pop(SqStack*& s, int& x) {
	if (s->top == -1) {						//ջ�����
		return false;
	}
	else {
		x = s->data[s->top];				//ȡջ��Ԫ��
		s->top--;							//ջ��ָ���һ
		return true;
	}
}

//ȡջ��Ԫ��
bool GetTop(SqStack* s, int& x) {
	if (s->top == -1) {						//ջ�����
		return false;
	}
	else {
		x = s->data[s->top];				//ȡջ��Ԫ��
		return true;
	}
}

int main() {
	int i, n;
	int x, y;
	int a[maxsize];
	SqStack* s;
	InitStack(s);
	cout << "�������: ";
	cin >> n;
	cout << "����ֵ: ";
	for (i = 0; i < n; i++) {
		cin >> a[i];
		Push(s, a[i]);
	}
	cout << "ջ��Ԫ��: ";
	GetTop(s, x);
	cout << x << endl;
	cout << "ջ�����: ";
	while (!StackEmpty(s)) {
		Pop(s, y);
		cout << y << " ";
	}
	cout << endl;
	return 0;
}
