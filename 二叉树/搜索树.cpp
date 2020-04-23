#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define CHAR_SIZE	26				//字母大小
#define KEY_SIZE	256				//关键字大小
#define DESC_SIZE	256				//描述区大小
#define BUFF_SIZE	512				//缓冲区大小	
#define FILE_NAME	"test.txt"		//文件路径

typedef struct search_tree_node {				//定义搜索树节点
	struct search_tree_node* ch[CHAR_SIZE];		//分类
	char desc[DESC_SIZE];						//描述
}STNode;


int get_word(FILE* fp, char* key, char* desc);					//分离文本信息
STNode* new_node();												//新建节点
int insert_st_tree(STNode** st_tree, char* key, char* desc);	//插入信息
char* find(STNode* st_tree, char* key);							//查找分类


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
		printf("\nFind description: %s", data);
	}
	else {
		printf("\nCan not find!\n");
	}

	fclose(fp);
	return 0;
}


/*****************************************************************************
* @data  : 2020/4/19
* @brief : 读取文件，分离关键字和描述信息
* @input :
*   fp	: 文件指针
*	key	: 关键字（返回）
*	desc: 描述信息（返回）
* @output:
*   -1	: 失败
*	0	: 成功
*****************************************************************************/
int get_word(FILE* fp, char* key, char* desc) {
	int i, j;
	char buff[BUFF_SIZE];
	char* res = fgets(buff, BUFF_SIZE, fp);		//逐行读取（包括换行符）
	if (res == NULL) {
		return -1;
	}
	for (i = 0; i < KEY_SIZE - 1 && buff[i] != ':'; i++) {	//预留结束符，分割标志
		key[i] = buff[i];
	}
	key[i] = '\0';
	i++;
	for (j = 0; j < DESC_SIZE - 1 && buff[i] != '\0'; j++, i++) {	//预留结束符，结束标志
		desc[j] = buff[i];
	}
	desc[j] = '\0';
	return 0;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 创建新搜索树结点
* @input :
*   none : none
* @output:
*   node : 初始化的新结点
*****************************************************************************/
STNode* new_node() {
	STNode* node;
	node = (STNode*)malloc(sizeof(STNode));		//分配一个空间
	if (node == NULL) {
		return NULL;
	}
	for (int i = 0; i < CHAR_SIZE; i++) {		//初始化
		node->ch[i] = NULL;
	}
	node->desc[0] = '\0';
	return node;
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 创建搜索树
* @input :
*   st_tree	: 二级指针创建搜索树
*	key		: 关键字
*	desc	: 描述信息
* @output:
*   -1		: 失败
*	0		: 成功
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
	//递归创建，因为以小写英文字母为例（26），ASCII码减去'a'，得到指针相对地址（或数组下标）
	return insert_st_tree((*st_tree)->ch + *key - 'a', key + 1, desc);
}

/*****************************************************************************
* @data  : 2020/4/19
* @brief : 使用搜索树查询关键字描述（有返回，无）
* @input :
*   st_tree	: 搜索树
*	key		: 关键字
* @output:
*   desc	: 描述信息
*	NULL	: 空
*****************************************************************************/
char* find(STNode* st_tree, char* key) {
	if (st_tree == NULL) {	//为空，返回 NULL
		return NULL;
	}
	if (*key == '\0') {		//完全匹配，返回描述信息
		if (st_tree->desc[0] == '\0') {
			return NULL;
		}
		return st_tree->desc;
	}
	return find(st_tree->ch[*key - 'a'], key + 1);	//递归查找
}
