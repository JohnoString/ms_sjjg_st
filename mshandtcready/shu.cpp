// LSM-tree
// Red-Black-tree

// erchashu
#if 0
#include <iostream>
#include <stack>
#include <string>
using namespace std;

typedef char ElemType;

//�������Ľڵ�
typedef struct BiNode
{
	ElemType data;			//�ڵ����������
	BiNode* left;			//������
	BiNode* right;			//������
	BiNode()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}
}BiNode, * BiTree;


//��������
class BinaryTree
{
public:
	BinaryTree()
	{
		m_root = nullptr;
		size = 0;
	}

	BiTree CreateBiTree();                  // ����������
	
	void InOrderWithoutRecursion2(BiTree root);

private:
	BiTree m_root;      //���ڵ�
	uint32_t size;		//�ڵ�����
};


// �����������ǵݹ�
BiTree CreateBiTree()
{
	
}

// �������������ݹ�

//ɾ��������

//�ݹ�õ����ĸ߶�

//ǰ�����

//�������

//�������

// ��α����ǵݹ�
// ��������ǵݹ�
// ��������ǵݹ�
void BinaryTree::InOrderWithoutRecursion2(BiTree root)
{
	//����
	if (root == NULL)
		return;
	//���ǿ�
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

// ���������ǵݹ�

int main()
{
	return 0;
}
#endif

#if 1
#include <iostream>
#include <stack>
using namespace std;

// BST�Ľ��
typedef struct node
{
	int key;
	struct node* lChild, * rChild;
}Node, * BST;

// �ڸ�����BST�в����㣬��������Ϊelement, ʹ֮��Ϊ�µ�BST
bool BSTInsert(Node*& p, int element)
{
	if (NULL == p) // ����
	{
		p = new Node;
		p->key = element;
		p->lChild = p->rChild = NULL;
		return true;
	}

	if (element == p->key) // BST�в�������ȵ�ֵ(ָ���Ǹ��ڵ㲻�ܸ�left��right���)
		return false;

	if (element < p->key)  // �ݹ�
		return BSTInsert(p->lChild, element);

	return BSTInsert(p->rChild, element); // �ݹ�
}

// ����BST
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

// �������
void preOrderTraverse(BST T)
{
	if (T)
	{
		cout << T->key << " ";
		preOrderTraverse(T->lChild);
		preOrderTraverse(T->rChild);
	}
}

// �������
void inOrderTraverse(BST T)
{
	if (T)
	{
		inOrderTraverse(T->lChild);
		cout << T->key << " ";
		inOrderTraverse(T->rChild);
	}
}

// �������
void afterOrderTraverse(BST T)
{
	if (T)
	{
		inOrderTraverse(T->lChild);
		inOrderTraverse(T->rChild);
		cout << T->key << " ";
	}
}

// ��������ǵݹ�
void InOrderWithoutRecursion2(BST root)
{
	//����
	if (root == NULL)
		return;
	//���ǿ�
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

// ��������ǵݹ�
void PreOrderWithoutRecursion2(BST root)
{
	//����
	if (root == NULL)
		return;
	//���ǿ�
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

// ��������ǵݹ�
void AfterOrderWithoutRecursion2(BST root)
{
	//����
	if (root == NULL)
		return;
	//���ǿ�
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

// ��α���

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

	// �������е�a[]���ܹ����BST,���ԣ���ö�createBST�ķ���ֵ�����ж�
	if (!createBST(T, a, n))
	{
		cout << "����ʧ��" << endl;
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