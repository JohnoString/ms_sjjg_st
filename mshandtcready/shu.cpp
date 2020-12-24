// LSM-tree
// Red-Black-tree

// erchashu
#if 0
#include <iostream>
#include <stack>
#include <string>
using namespace std;

typedef char ElemType;

//定义树的节点
typedef struct BiNode
{
	ElemType data;			//节点的数据类型
	BiNode* left;			//左子树
	BiNode* right;			//右子树
	BiNode()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}
}BiNode, * BiTree;


//二叉树类
class BinaryTree
{
public:
	BinaryTree()
	{
		m_root = nullptr;
		size = 0;
	}

	BiTree CreateBiTree();                  // 创建二叉树
	
	void InOrderWithoutRecursion2(BiTree root);

private:
	BiTree m_root;      //根节点
	uint32_t size;		//节点总数
};


// 创建二叉树非递归
BiTree CreateBiTree()
{
	
}

// 创建二叉树、递归

//删除二叉树

//递归得到树的高度

//前序遍历

//中序遍历

//后序遍历

// 层次遍历非递归
// 先序遍历非递归
// 中序遍历非递归
void BinaryTree::InOrderWithoutRecursion2(BiTree root)
{
	//空树
	if (root == NULL)
		return;
	//树非空
	BiTree p = root;
	stack<BiTree> s;
	while (!s.empty() || p)
	{
		if (p)
		{
			s.push(p);
			p = p->left;
		}
		else
		{
			p = s.top();
			s.pop();
			cout << p->data;
			p = p->right;
		}
	}
}

// 后续遍历非递归

int main()
{
	return 0;
}
#endif

#if 0
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

// BST的结点
typedef struct node
{
	int key;
	struct node* lChild, * rChild;
}Node, * BST;

// 在给定的BST中插入结点，其数据域为element, 使之称为新的BST
bool BSTInsert(Node*& p, int element)
{
	if (NULL == p) // 空树
	{
		p = new Node;
		p->key = element;
		p->lChild = p->rChild = NULL;
		return true;
	}

	if (element == p->key) // BST中不能有相等的值(指的是跟节点不能跟left、right相等)
		return false;

	if (element < p->key)  // 递归
		return BSTInsert(p->lChild, element);
	return BSTInsert(p->rChild, element); // 递归
}

// 建立BST
bool createBST(Node*& T, int a[], int n)
{
	T = NULL;
	int i;
	bool ret = false;
	for (i = 0; i < n; i++)
	{
		ret = BSTInsert(T, a[i]);
	}

	return ret;
}

// 先序遍历
void preOrderTraverse(BST T)
{
	if (T)
	{
		cout << T->key << " ";
		preOrderTraverse(T->lChild);
		preOrderTraverse(T->rChild);
	}
}

// 中序遍历
void inOrderTraverse(BST T)
{
	if (T)
	{
		inOrderTraverse(T->lChild);
		cout << T->key << " ";
		inOrderTraverse(T->rChild);
	}
}

// 后序遍历
void afterOrderTraverse(BST T)
{
	if (T)
	{
		afterOrderTraverse(T->lChild);
		afterOrderTraverse(T->rChild);
		cout << T->key << " ";
	}
}

// 中序遍历非递归
void InOrderWithoutRecursion2(BST root)
{
	//空树
	if (root == NULL)
		return;
	//树非空
	BST p = root;
	stack<BST> s;
	while (!s.empty() || p)
	{
		if (p)
		{
			s.push(p);
			p = p->lChild;
		}
		else
		{
			p = s.top();
			s.pop();
			cout << p->key << " ";
			p = p->rChild;
		}
	}
}

// 先序遍历非递归
void PreOrderWithoutRecursion2(BST root)
{
	//空树
	if (root == NULL)
		return;
	//树非空
	BST p = root;
	stack<BST> s;
	while (!s.empty() || p)
	{
		if (p)
		{
			cout << p->key << " ";
			s.push(p);
			p = p->lChild;
		}
		else
		{
			p = s.top();
			s.pop();
			p = p->rChild;
		}
	}
}

// 后序遍历非递归
stack<int> AfterOrderWithoutRecursion2(BST root)
{
	//stack<BST> s;
	//stack<int> res; // 保存节点序列的栈
	//stack<int> ans;
	//BST cur = root;
	//while (cur != nullptr || !s.empty()) {
	//	while (cur != nullptr) {
	//		res.push(cur->key);
	//		s.push(cur);
	//		cur = cur->rChild; // 修改处
	//	}
	//	if (!s.empty()) {
	//		cur = s.top();
	//		cur = cur->lChild; // 修改处
	//	}

	//}

	//while (!res.empty())
	//{
	//	ans.push(res.top()); // 获取倒序的根右左序列
	//}

	//return ans;

	stack<BST> s;
	stack<int> ans;
	BST cur = root;
	BST pre = nullptr;  // 用于记录上一次访问的节点
	while (cur != nullptr || !s.empty()) {
		while (cur != nullptr) {
			s.push(cur);
			cur = cur->lChild;
		}
		if (!s.empty()) {
			cur = s.top();
			s.pop();
			if (cur->rChild == nullptr || pre == cur->rChild) { // 访问节点的条件
				ans.push(cur->key); // 访问
				pre = cur; // 这一步是记录上一次访问的节点
				cur = nullptr; // 此处为了跳过下一次循环的访问左子节点的过程，直接进入栈的弹出阶段，因为但凡在栈中的节点，它们的左子节点都肯定被经过且已放入栈中。
			}
			else { // 不访问节点的条件
				s.push(cur); // 将已弹出的根节点放回栈中
				cur = cur->rChild; // 经过右子节点
			}
		}
	}

	return ans;
}

// 层次遍历
vector<int> bfs(BST root)
{
	vector<int>res;
	queue<BST>q;//辅助队列

	if (root == NULL)return res;
	q.push(root);

	while (!q.empty())
	{
		res.push_back(q.front()->key);
		if (q.front()->lChild != NULL)
		{
			q.push(q.front()->lChild);
		}
		if (q.front()->rChild != NULL)
		{
			q.push(q.front()->rChild);
		}

		q.pop();
	}
	return res;
}

BST BST_Search(BST root, int key)
{
	while (root != NULL && root->key != key)
	{
		if (key < root->key)
			root = root->lChild;
		else
			root = root->rChild;
	}
	return root;
}

#include <sstream>

int main()
{
	int a[9] = {10,8,12,6,9,11,13,5,7};
	int n = 9;
	BST T;
	stack<int> s;
	// 并非所有的a[]都能构造出BST,所以，最好对createBST的返回值进行判断
	if (!createBST(T, a, n))
	{
		cout << "创建失败" << endl;
		return -1;
	}

	preOrderTraverse(T);
	cout << endl;

	inOrderTraverse(T);
	cout << endl;

	afterOrderTraverse(T);
	cout << endl;

	//InOrderWithoutRecursion2(T);
	//cout << endl;

	//PreOrderWithoutRecursion2(T);
	//cout << endl;

	s = AfterOrderWithoutRecursion2(T);
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	vector<int> v = bfs(T);
	int i = 0;
	while (i < v.size())
	{
		cout << v[i] << " ";
		++i;
	}
	cout << endl;
	//string tmp = "asdas";
	//stringstream sstr(tmp);
	//uint64_t flags;
	//sstr >> flags;  // 将数据流提取到flags中

	//cout << flags << endl;
	return 0;
}
#endif

// 平衡二叉树基本操作
#if 0
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

template<class DataType>
struct BinTreeNode
{
	BinTreeNode* left;
	BinTreeNode* right;
	DataType data;
};

template<class DataType>
class BinTree
{
public:
	BinTree()
	{
		root_ = nullptr;
		size_ = 0;
	}

	BinTreeNode<DataType>* GetRoot();
	bool Init(vector<DataType> vecdata);
	bool InsertNode(BinTreeNode<DataType>*& root, DataType data);

	void beforeOrderTrv(BinTreeNode<DataType>* root);
	void midOrderTrv(BinTreeNode<DataType>* root);
	void afterOrderTrv(BinTreeNode<DataType>* root);
	void layerOrderTrv();
	void layerOrderTrv_queue();  //层序遍历_队列实现
	void beforeOrderTrv_stack();
	void midOrderTrv_stack();
	void afterOrderTrv_stack_from_before();
	void Destory(BinTreeNode<DataType>* root);
	
	// 翻转--递归/非递归(栈/队列)
	BinTreeNode<DataType>* RevBinTree(BinTreeNode<DataType>* root);
	BinTreeNode<DataType>* RevBinTree();

	// 高度--递归/非递归(先续/层序)
	uint32_t GetTreeHeight(BinTreeNode<DataType>* root);
	uint32_t GetTreeHeight();

	BinTreeNode<DataType>* FindNode(DataType data);

	vector<vector<DataType> > zigzagLevelOrder(BinTreeNode<DataType>* root);
private:
	BinTreeNode<DataType>* root_;
	uint32_t size_;
};

template<class DataType>
BinTreeNode<DataType>* BinTree<DataType>::FindNode(DataType data)
{
	if (!root_)
	{
		return nullptr;
	}

	BinTreeNode<DataType>* proot = root_;
	while (proot)
	{
		if (proot->data > data)
			proot = proot->left;
		else if (proot->data < data)
			proot = proot->right;
		else
			return proot;
	}

	return nullptr;
}

template<class DataType>
BinTreeNode<DataType>* BinTree<DataType>::GetRoot()
{
	return root_;
}

template<class DataType>
bool BinTree<DataType>::Init(vector<DataType> vecdata)
{
	if (root_ != nullptr)
		return true;      

	for (uint32_t i = 0; i < vecdata.size(); ++i)
	{
		if (!InsertNode(root_, vecdata[i]))
		{
			return false;
		}
	}
}

template<class DataType>
bool BinTree<DataType>::InsertNode(BinTreeNode<DataType>*& root, DataType data)
{
	if (root == nullptr)
	{
		root = new(std::nothrow) BinTreeNode<DataType>();
		if (root == nullptr)
		{
			return false;
		}

		root->data = data;
		root->left = root->right = nullptr;

		size_++;
		return true;
	}
	
	if (data == root->data)
	{
		return false;
	}
	else if (data > root->data)
	{
		return InsertNode(root->right, data);
	}
	else
	{
		return InsertNode(root->left, data);
	}
}

template<class DataType>
void BinTree<DataType>::beforeOrderTrv(BinTreeNode<DataType>* root)
{
	if (root)
	{
		cout << root->data << " ";
		beforeOrderTrv(root->left);
		beforeOrderTrv(root->right);
	}
}

template<class DataType>
void BinTree<DataType>::midOrderTrv(BinTreeNode<DataType>* root)
{
	if (root)
	{
		midOrderTrv(root->left);
		cout << root->data << " ";
		midOrderTrv(root->right);
	}
}

template<class DataType>
void BinTree<DataType>::afterOrderTrv(BinTreeNode<DataType>* root)
{
	if (root)
	{
		afterOrderTrv(root->left);
		afterOrderTrv(root->right);
		cout << root->data << " ";
	}
}

// 层序遍历_数组
template<class DataType>
void BinTree<DataType>::layerOrderTrv()
{
	BinTreeNode<DataType>** temp = new(std::nothrow) BinTreeNode<DataType>*[size_ * 10];
	if (temp == nullptr)
	{
		return;
	}

	uint32_t in = 0;
	uint32_t out = 0;

	temp[in++] = root_;  //保存根节点
	while (in > out)
	{
		if (temp[out])
		{
			cout << temp[out]->data << "→";
			temp[in++] = temp[out]->left;
			temp[in++] = temp[out]->right;
		}
		out++;
	}

	if (temp)
	{
		delete[] temp;
		temp = nullptr;
	}
}

// 层序遍历_队列
template<class DataType>
void BinTree<DataType>::layerOrderTrv_queue()
{
	queue<BinTreeNode<DataType>*> q;
	if (root_ != nullptr)
	{
		q.push(root_);   
	}

	while (q.empty() == false) 
	{
		cout << q.front()->data << "→";

		if (q.front()->left != nullptr)  
		{
			q.push(q.front()->left);
		}

		if (q.front()->right != nullptr)   
		{
			q.push(q.front()->right);
		}
		q.pop();  
	}
}

template<class DataType>
void BinTree<DataType>::beforeOrderTrv_stack()
{
	if (root_ == nullptr)
	{
		return;
	}

	BinTreeNode<DataType>* proot = root_;
	stack<BinTreeNode<DataType>*> s;
	while (!s.empty() || proot)
	{
		if (proot)
		{
			cout << proot->data << " ";
			s.push(proot);
			proot = proot->left;
		}
		else
		{
			proot = s.top();
			s.pop();
			proot = proot->right;
		}
	}
}

template<class DataType>
void BinTree<DataType>::midOrderTrv_stack()
{
	if (root_ == nullptr)
	{
		return;
	}

	BinTreeNode<DataType>* proot = root_;
	stack<BinTreeNode<DataType>*> s;
	while (!s.empty() || proot)
	{
		if (proot)
		{
			s.push(proot);
			proot = proot->left;
		}
		else
		{
			proot = s.top();
			cout << proot->data << " ";
			s.pop();
			proot = proot->right;
		}
	}
}
 
// 思路:先根特殊处理再倒序
template<class DataType>
void BinTree<DataType>::afterOrderTrv_stack_from_before()
{
	if (root_ == nullptr)
	{
		return;
	}

	stack<DataType> res;
	BinTreeNode<DataType>* proot = root_;
	stack<BinTreeNode<DataType>*> s;
	while (!s.empty() || proot)
	{
		if (proot)
		{
			res.push(proot->data);
			s.push(proot);
			proot = proot->right;
		}
		else
		{
			proot = s.top();
			s.pop();
			proot = proot->left;
		}
	}

	while (!res.empty())
	{
		cout << res.top() << " ";
		res.pop();
	}
	cout << endl;
}

template<class DataType>
void BinTree<DataType>::Destory(BinTreeNode<DataType>* root)  // 后根遍历
{
	if (root == nullptr)
	{
		return;
	}

	Destory(root->left);
	Destory(root->right);
	delete root;
	root = nullptr;
}

template<class DataType>
uint32_t BinTree<DataType>::GetTreeHeight(BinTreeNode<DataType>* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	uint32_t leftheight = GetTreeHeight(root->left);
	uint32_t rightheight = GetTreeHeight(root->right);

	return (leftheight > rightheight ? leftheight : rightheight) + 1;
}

template<class DataType>
BinTreeNode<DataType>* BinTree<DataType>::RevBinTree(BinTreeNode<DataType>* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	BinTreeNode<DataType>* ptmp = root->left;
	root->left = root->right;
	root->right = ptmp;

	RevBinTree(root->left);
	RevBinTree(root->right);
}

template<class DataType>
uint32_t BinTree<DataType>::GetTreeHeight()  // 层次
{
	uint32_t left_height = 0;
	uint32_t right_height = 0;
	queue<BinTreeNode<DataType>*> q;
	if (root_ != nullptr)
	{
		q.push(root_);
	}

	while (q.empty() == false)
	{
		//cout << q.front()->data << "→";

		if (q.front()->left != nullptr)
		{
			q.push(q.front()->left);
			left_height++;
		}

		if (q.front()->right != nullptr)
		{
			q.push(q.front()->right);
			right_height++;
		}
		q.pop();
	}

	return left_height > right_height ? left_height : right_height;
}

template<class DataType>
BinTreeNode<DataType>* BinTree<DataType>::RevBinTree()  //反转非递归_队列
{
	if (root_ == nullptr) return root_;

	queue<BinTreeNode<DataType>*> queue;
	queue.push(root_);
	while (!queue.empty()) {
		BinTreeNode<DataType>* cur = queue.front();
	
		if (cur->left != nullptr) queue.push(cur->left);
		if (cur->right != nullptr) queue.push(cur->right);

		auto tmp = cur->left;
		cur->left = cur->right;
		cur->right = tmp;

		queue.pop();
	}

	return root_;
}

template<class DataType>
vector<vector<DataType> > BinTree<DataType>::zigzagLevelOrder(BinTreeNode<DataType>* root)  // 锯齿遍历
{
	vector<vector<DataType>> res;
	if (!root) return res;
	queue<BinTreeNode<DataType>*> q;
	q.push(root);
	int flag = 0;
	while (!q.empty())
	{
		vector<DataType> temp;
		auto size = q.size();
		while (size--)
		{
			BinTreeNode<DataType>* node = q.front();
			q.pop();
			temp.push_back(node->data);
			if (node->left) q.push(node->left);
			if (node->right) q.push(node->right);
		}
		++flag;
		if (1 == flag % 2)
		{
			res.push_back(temp);
		}
		if (0 == flag % 2)
		{
			reverse(temp.begin(), temp.end());
			res.push_back(temp);
		}
	}
	return res;
}

int main()
{
	BinTree<int> b;
	vector<int> v = { 10, 8, 12, 6, 9, 11, 13, 5, 7 };
	b.Init(v);
	/*
	b.beforeOrderTrv(b.GetRoot());
	cout << endl;
	b.midOrderTrv(b.GetRoot());
	cout << endl;
	b.afterOrderTrv(b.GetRoot());
	cout << endl;
	BinTreeNode<int>* node = b.FindNode(11);
	if (node)
	{
		cout << "find ele, data=" << node->data << endl;
	}
	else
	{
		cout << "not find"<< endl;
	}

	b.layerOrderTrv();
	cout << endl;
	b.layerOrderTrv_queue();
	cout << endl;
	cout << b.GetTreeHeight(b.GetRoot()) << endl;
	b.RevBinTree(b.GetRoot());
	b.layerOrderTrv();
	cout << endl;
	b.RevBinTree(b.GetRoot());
	cout << endl;
	b.midOrderTrv_stack();
	cout << endl;
	b.beforeOrderTrv_stack();
	cout << endl;
	b.afterOrderTrv_stack_from_before();
	cout << b.GetTreeHeight() << endl;
	b.RevBinTree();
	b.layerOrderTrv();
	cout << endl;
	*/
	b.layerOrderTrv_queue();
	cout << endl;
	vector<vector<int> > v1 = b.zigzagLevelOrder(b.GetRoot());
	for (int i = 0; i < v1.size(); ++i)
	{
		for (auto x : v1[i])
		{
			cout << x << " ";
		}
	}
	cout << endl;
	return 0;
}
#endif