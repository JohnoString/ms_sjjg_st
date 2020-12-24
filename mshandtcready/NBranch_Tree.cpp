#if 0
// https://segmentfault.com/a/1190000002451356 二叉链表
// 需求: 子树数目可配, 根节点值为0, 子节点值从左到右依次累加, 暂时不考虑参数化模板; 子节点数组用vector便于二分查找  有问题
#include <iostream>
using namespace std;

class NBraTreeNode
{
public:
	static uint32_t data_;    // 数据

	NBraTreeNode* left_child_;  // 左起第一个节点
	NBraTreeNode* next_sibling_; // 第一个节点的临接节点
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
	NBraTreeNode* root_;  // 树的根节点
	uint32_t node_num_;   // 节点总数
	uint32_t child_num_;  // 节点的度
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
	CNode* first_child, * next_sibling;//first_child是第一个子节点,next_sibling是fc的临节点
};

/* 这个函数用于处理多叉树数据，各种数据类型自定义 */
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
		//这个函数根据自己的时间情况自定义
		if (0 == ((CTreeData*)node->data)->cmpData(data)) {
			return 0;//数据匹配
		}
		else {
			return -1;//数据不匹配
		}
	}
	int cmpData(char* indata) {
		//这个函数根据自己的时间情况自定义
		if (0 == strcmp(data, indata)) {
			return 0;//数据匹配
		}
		else {
			return -1;//数据不匹配
		}
	}
	void print() {
		printf("%s ", data);//先序打印遍历
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
	/*遍历所有节点，释放内存*/
	if (node->first_child != NULL) {
		preOrder(node->first_child);
	}
	if (node->next_sibling != NULL) {
		preOrder(node->next_sibling);
		/* 清除数据，释放节点 */
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
/* 查找某一个节点  */
/* node:起始节点   */
/* data:节点验证数据*/
/* 0:成功  1:失败  */
template <class T>
int TTree<T>::searchNode(CNode* node, char* name) {
	/*首先判断当前节点是不是要查找的节点*/
	if (0 == ((T*)node->data)->cmpData(name)) {
		/* 找到节点 */
		return 0;
	}
	/* 先查找子节点 */
	if (node->first_child != NULL) {
		searchNode(node, name);
	}
	/* 先查找临节点 */
	if (node->next_sibling != NULL) {
		searchNode(node, name);
	}
	return -1;
}
/* 插入某一个节点  */
/* node:起始节点   */
/* parent:父节点名 */
/* 0:成功 -1:失败  */
template <class T>
int TTree<T>::insertNode(CNode* node, char* parent, T* indata) {
	/*首先判断当前节点是不是要查找的父节点*/

	if (0 == ((T*)node->data)->cmpData(parent)) {
		CNode* new_node = new CNode;
		new_node->data = indata;
		/* 先判断子节点是否为空 */
		if (NULL == node->first_child) {
			node->first_child = new_node;
			return 0;
		}
		CNode* child = node->first_child;
		if (0 == (indata->cmpNode(child))) {//判断节点是否已经存在
			return -1;
		}
		/* 判断是否已存在该节点 */
		/* 就是当前节点,找到子节点的最后一个插入位置 */
		while (child->next_sibling != NULL) {
			child = child->next_sibling;
			if (0 == (indata->cmpNode(child))) {//判断节点是否已经存在
				return -1;
			}
		};
		/* 插入 */
		child->next_sibling = new_node;
		return 0;
	}
	else if (node->first_child != NULL) {
		/* 查找子节点 */
		if (0 == insertNode(node->first_child, parent, indata)) {
			return 0;
		}
	}
	else {
		/* 没找到 退出*/
	}
	/* 查找临节点 */
	if (node->next_sibling != NULL) {
		if (0 == insertNode(node->next_sibling, parent, indata)) {
			return 0;
		}
	}
	return -1;
}
template <class T>
void TTree<T>::preOrder(CNode* node) {
	((T*)node->data)->print();//先序打印遍历
	if (node->first_child != NULL) {
		printf("\r\n");
		preOrder(node->first_child);
		printf("\r\n");
	}
	//((T*)node->data)->print();//倒序打印遍历
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
	ret = test.insertNode(test.getRoot(), "first11", data);//无父节点，插入失败
	data = new CTreeData("second1-2");
	ret = test.insertNode(test.getRoot(), "first1", data);
	data = new CTreeData("second1-2");
	ret = test.insertNode(test.getRoot(), "first1", data);//存在节点，插入失败
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
	ret = pt->insertNode(pt->getRoot(), (char*)"first11", data);//无父节点，插入失败
	data = new CTreeData((char*)"second1-2");
	ret = pt->insertNode(pt->getRoot(), (char*)"first1", data);
	data = new CTreeData((char*)"second1-2");
	ret = pt->insertNode(pt->getRoot(), (char*)"first1", data);//存在节点，插入失败
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