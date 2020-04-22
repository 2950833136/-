#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define CHAR_SIZE	26				//��ĸ��С
#define KEY_SIZE	256				//�ؼ��ִ�С
#define DESC_SIZE	256				//��������С
#define BUFF_SIZE	512				//��������С	
#define FILE_NAME	"log.txt"		//�ļ�·��

typedef struct search_tree_node {				//�����������ڵ�
	struct search_tree_node* ch[CHAR_SIZE];		//����
	char desc[DESC_SIZE];						//����
}STNode;


int get_word(FILE* fp, char* key, char* desc);					//�����ı���Ϣ
STNode* new_node();												//�½��ڵ�
int insert_st_tree(STNode** st_tree, char* key, char* desc);	//������Ϣ
char* find(STNode* st_tree, char* key);							//���ҷ���


int main() {
	char key[KEY_SIZE];
	char desc[DESC_SIZE];
	STNode* st_tree = NULL;
	char* data;

	FILE* fp = fopen(FILE_NAME, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen error!\n");
		return -1;
	}

	while (1) {
		int res = get_word(fp, key, desc);
		if (res != -1) {
			printf("%s\n", key);
			printf("%s\n", desc);
		}
		else {
			break;
		}
		insert_st_tree(&st_tree, key, desc);
	}

	data = find(st_tree, (char*)"ant");
	if (data != NULL) {
		printf("%s", data);
	}
	else {
		printf("Can not find!\n");
	}

	fclose(fp);
	return 0;
}


/*****************************************************************************
* @data  : 2020/4/19
* @brief : ��ȡ�ļ�������ؼ��ֺ�������Ϣ
* @input :
*   fp	: �ļ�ָ��
*	key	: �ؼ��֣����أ�
*	desc: ������Ϣ�����أ�
* @output:
*   -1	: ʧ��
*	0	: �ɹ�
*****************************************************************************/
int get_word(FILE* fp, char* key, char* desc) {
	int i, j;
	char buff[BUFF_SIZE];
	char* res = fgets(buff, BUFF_SIZE, fp);		//���ж�ȡ���������з���
	if (res == NULL) {
		return -1;
	}
	for (i = 0; i < KEY_SIZE - 1 && buff[i] != ':'; i++) {	//Ԥ�����������ָ��־
		key[i] = buff[i];
	}
	key[i] = '\0';
	i++;
	for (j = 0; j < DESC_SIZE - 1 && buff[i] != '\0'; j++, i++) {	//Ԥ����������������־
		desc[j] = buff[i];
	}
	desc[j] = '\0';
	return 0;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : ���������������
* @input :
*   none : none
* @output:
*   node : ��ʼ�����½��
*****************************************************************************/
STNode* new_node() {
	STNode* node;
	node = (STNode*)malloc(sizeof(STNode));		//����һ���ռ�
	if (node == NULL) {
		return NULL;
	}
	for (int i = 0; i < CHAR_SIZE; i++) {		//��ʼ��
		node->ch[i] = NULL;
	}
	node->desc[0] = '\0';
	return node;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : ����������
* @input :
*   st_tree	: ����ָ�봴��������
*	key		: �ؼ���
*	desc	: ������Ϣ
* @output:
*   -1		: ʧ��
*	0		: �ɹ�
*****************************************************************************/
int insert_st_tree(STNode** st_tree, char* key, char* desc) {
	if (*st_tree == NULL) {
		*st_tree = new_node();
		if (*st_tree == NULL) {
			return -1;
		}
	}
	if (*key == '\0') {
		strcpy((*st_tree)->desc, desc);
		return 0;
	}
	//�ݹ鴴������Ϊ��СдӢ����ĸΪ����26����ASCII���ȥ'a'���õ�ָ����Ե�ַ���������±꣩
	return insert_st_tree((*st_tree)->ch + *key - 'a', key + 1, desc);
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : ʹ����������ѯ�ؼ����������з��أ��ޣ�
* @input :
*   st_tree	: ������
*	key		: �ؼ���
* @output:
*   desc	: ������Ϣ
*	NULL	: ��
*****************************************************************************/
char* find(STNode* st_tree, char* key) {
	if (st_tree == NULL) {	//Ϊ�գ����� NULL
		return NULL;
	}
	if (*key == '\0') {		//��ȫƥ�䣬����������Ϣ
		if (st_tree->desc[0] == '\0') {
			return NULL;
		}
		return st_tree->desc;
	}
	return find(st_tree->ch[*key - 'a'], key + 1);	//�ݹ����
}