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

#if 1
#include <iostream>
#include <stack>
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
		inOrderTraverse(T->lChild);
		inOrderTraverse(T->rChild);
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
void AfterOrderWithoutRecursion2(BST root)
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
			p = p->rChild;
			//s.pop();
			cout << p->key << " ";
		}
		
	}
}

// 层次遍历

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

int main()
{
	int a[10] = { 4, 5, 2, 1, 0, 9, 3, 7, 6, 8 };
	int n = 10;
	BST T;

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

	InOrderWithoutRecursion2(T);
	cout << endl;

	PreOrderWithoutRecursion2(T);
	cout << endl;

	AfterOrderWithoutRecursion2(T);
	cout << endl;
	return 0;
}
#endif