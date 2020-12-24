#if 0
// https://segmentfault.com/a/1190000002451356 ��������
// ����: ������Ŀ����, ���ڵ�ֵΪ0, �ӽڵ�ֵ�����������ۼ�, ��ʱ�����ǲ�����ģ��; �ӽڵ�������vector���ڶ��ֲ���  ������
#include <iostream>
using namespace std;

class NBraTreeNode
{
public:
	static uint32_t data_;    // ����

	NBraTreeNode* left_child_;  // �����һ���ڵ�
	NBraTreeNode* next_sibling_; // ��һ���ڵ���ٽӽڵ�
};

uint32_t NBraTreeNode::data_ = 0;

class NBraTree
{
public:
	NBraTree(uint32_t child_num) : child_num_(child_num) 
	{
		root_ = nullptr;
		node_num_ = 0;
	}

public:
	bool Init();
	NBraTreeNode* GetRoot();
	bool Insert(NBraTreeNode* root);

private:
	NBraTreeNode* root_;  // ���ĸ��ڵ�
	uint32_t node_num_;   // �ڵ�����
	uint32_t child_num_;  // �ڵ�Ķ�
};

NBraTreeNode* NBraTree::GetRoot()
{
	return root_;
}

bool NBraTree::Init()
{
	if (child_num_ <= 0)
	{
		return false;
	}

	if (nullptr == root_)
	{
		root_ = new(std::nothrow) NBraTreeNode;
		if (nullptr == root_)
		{
			return false;
		}

		root_->data_ = 0;
		root_->left_child_ = nullptr;
		root_->next_sibling_ = nullptr;
		return true;
	}
}

bool NBraTree::Insert(NBraTreeNode* root)
{
	NBraTreeNode* ptmp = new(std::nothrow) NBraTreeNode;
	if (nullptr == ptmp)
	{
		return false;
	}

	ptmp->data_++;
	ptmp->left_child_ = nullptr;
	ptmp->next_sibling_ = nullptr;

	NBraTreeNode* proot = root;
	if (nullptr == proot)
	{
		proot = ptmp;
		root_ = proot;
		return true;
	}

	if (nullptr == proot->left_child_)
	{
		if (!Insert(proot->left_child_))
		{
			return false;
		}

		return true;
	}
	else
	{
		uint32_t i = 1;
		NBraTreeNode* pchild = proot->left_child_;
		while (nullptr != pchild->next_sibling_)
		{
			pchild = pchild->next_sibling_;
			i++;
		}

		if (i >= child_num_)
		{
			if (!Insert(proot->next_sibling_))
			{
				return false;
			}
		}
		else
		{
			pchild->next_sibling_ = ptmp;
		}
	}

	return true;
}

int main()
{
	NBraTree t(3);
	t.Init();
	for (uint32_t i = 0; i < 100; ++i)
	{
		t.Insert(t.GetRoot());
	}

	return 0;
}
#endif

#if 0
#ifndef _TREE_H_
#define _TREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CNode
{
public:
	CNode() {
		data = NULL;
		first_child = NULL;
		next_sibling = NULL;
	}
	~CNode() {

	}
	void* data;
	CNode* first_child, * next_sibling;//first_child�ǵ�һ���ӽڵ�,next_sibling��fc���ٽڵ�
};

/* ����������ڴ����������ݣ��������������Զ��� */
class CTreeData
{
public:
	CTreeData(char* ch) {
		data = _strdup(ch);
	}
	~CTreeData() {
		free(data);
	}
	int cmpNode(CNode* node) {
		//������������Լ���ʱ������Զ���
		if (0 == ((CTreeData*)node->data)->cmpData(data)) {
			return 0;//����ƥ��
		}
		else {
			return -1;//���ݲ�ƥ��
		}
	}
	int cmpData(char* indata) {
		//������������Լ���ʱ������Զ���
		if (0 == strcmp(data, indata)) {
			return 0;//����ƥ��
		}
		else {
			return -1;//���ݲ�ƥ��
		}
	}
	void print() {
		printf("%s ", data);//�����ӡ����
	}
private:
	char* data;
};

template <class T>
class TTree
{
public:
	TTree(T* ch);
	~TTree();
	CNode* getRoot();
	int searchNode(CNode* node, char* name);
	int insertNode(CNode* node, char* parent, T* ch);
	void preOrder(CNode* node);

private:
	CNode root;
};
template <class T>
TTree<T>::TTree(T* ch)
{
	root.data = ch;
}
template <class T>
TTree<T>::~TTree()
{
	CNode* node = &root;
	/*�������нڵ㣬�ͷ��ڴ�*/
	if (node->first_child != NULL) {
		preOrder(node->first_child);
	}
	if (node->next_sibling != NULL) {
		preOrder(node->next_sibling);
		/* ������ݣ��ͷŽڵ� */
		delete(node->data);
		delete(node);
	}
	delete root.data;
	root.data = NULL;
	root.first_child = NULL;
	root.next_sibling = NULL;
}
template <class T>
CNode* TTree<T>::getRoot() {
	return &root;
}
/* ����ĳһ���ڵ�  */
/* node:��ʼ�ڵ�   */
/* data:�ڵ���֤����*/
/* 0:�ɹ�  1:ʧ��  */
template <class T>
int TTree<T>::searchNode(CNode* node, char* name) {
	/*�����жϵ�ǰ�ڵ��ǲ���Ҫ���ҵĽڵ�*/
	if (0 == ((T*)node->data)->cmpData(name)) {
		/* �ҵ��ڵ� */
		return 0;
	}
	/* �Ȳ����ӽڵ� */
	if (node->first_child != NULL) {
		searchNode(node, name);
	}
	/* �Ȳ����ٽڵ� */
	if (node->next_sibling != NULL) {
		searchNode(node, name);
	}
	return -1;
}
/* ����ĳһ���ڵ�  */
/* node:��ʼ�ڵ�   */
/* parent:���ڵ��� */
/* 0:�ɹ� -1:ʧ��  */
template <class T>
int TTree<T>::insertNode(CNode* node, char* parent, T* indata) {
	/*�����жϵ�ǰ�ڵ��ǲ���Ҫ���ҵĸ��ڵ�*/

	if (0 == ((T*)node->data)->cmpData(parent)) {
		CNode* new_node = new CNode;
		new_node->data = indata;
		/* ���ж��ӽڵ��Ƿ�Ϊ�� */
		if (NULL == node->first_child) {
			node->first_child = new_node;
			return 0;
		}
		CNode* child = node->first_child;
		if (0 == (indata->cmpNode(child))) {//�жϽڵ��Ƿ��Ѿ�����
			return -1;
		}
		/* �ж��Ƿ��Ѵ��ڸýڵ� */
		/* ���ǵ�ǰ�ڵ�,�ҵ��ӽڵ�����һ������λ�� */
		while (child->next_sibling != NULL) {
			child = child->next_sibling;
			if (0 == (indata->cmpNode(child))) {//�жϽڵ��Ƿ��Ѿ�����
				return -1;
			}
		};
		/* ���� */
		child->next_sibling = new_node;
		return 0;
	}
	else if (node->first_child != NULL) {
		/* �����ӽڵ� */
		if (0 == insertNode(node->first_child, parent, indata)) {
			return 0;
		}
	}
	else {
		/* û�ҵ� �˳�*/
	}
	/* �����ٽڵ� */
	if (node->next_sibling != NULL) {
		if (0 == insertNode(node->next_sibling, parent, indata)) {
			return 0;
		}
	}
	return -1;
}
template <class T>
void TTree<T>::preOrder(CNode* node) {
	((T*)node->data)->print();//�����ӡ����
	if (node->first_child != NULL) {
		printf("\r\n");
		preOrder(node->first_child);
		printf("\r\n");
	}
	//((T*)node->data)->print();//�����ӡ����
	if (node->next_sibling != NULL) {
		preOrder(node->next_sibling);
	}
}

int main()
{
	int ret;
	CTreeData* data = new CTreeData((char*)"root");
	TTree<CTreeData>* pt = new TTree<CTreeData>(data);
#if 0
	data = new CTreeData("first1");
	ret = test.insertNode(test.getRoot(), "root", data);

	data = new CTreeData("second1-1");
	ret = test.insertNode(test.getRoot(), "first11", data);//�޸��ڵ㣬����ʧ��
	data = new CTreeData("second1-2");
	ret = test.insertNode(test.getRoot(), "first1", data);
	data = new CTreeData("second1-2");
	ret = test.insertNode(test.getRoot(), "first1", data);//���ڽڵ㣬����ʧ��
	if (-1 == ret) {
		delete data;
		data = NULL;
	}
	data = new CTreeData("first2");
	ret = test.insertNode(test.getRoot(), "root", data);
	data = new CTreeData("senond2-1");
	ret = test.insertNode(test.getRoot(), "first2", data);

	test.preOrder(test.getRoot());
#else
	data = new CTreeData((char*)"first1");
	ret = pt->insertNode(pt->getRoot(), (char*)"root", data);

	data = new CTreeData((char*)"second1-1");
	ret = pt->insertNode(pt->getRoot(), (char*)"first11", data);//�޸��ڵ㣬����ʧ��
	data = new CTreeData((char*)"second1-2");
	ret = pt->insertNode(pt->getRoot(), (char*)"first1", data);
	data = new CTreeData((char*)"second1-2");
	ret = pt->insertNode(pt->getRoot(), (char*)"first1", data);//���ڽڵ㣬����ʧ��
	if (-1 == ret) {
		delete data;
		data = NULL;
	}
	data = new CTreeData((char*)"first2");
	ret = pt->insertNode(pt->getRoot(), (char*)"root", data);
	data = new CTreeData((char*)"senond2-1");
	ret = pt->insertNode(pt->getRoot(), (char*)"first2", data);

	pt->preOrder(pt->getRoot());
	delete pt;
	pt = NULL;
#endif    
	while (1);
}

#endif
#endif