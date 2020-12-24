// 非平衡二叉树的中序遍历 模拟二叉树根节点
#if 0
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef struct Node_Tree
{
	int data;
	Node* left;
	Node* right;
}Node;

void midTrv(Node* root)
{
	if (root == nullptr)
	{
		return;
	}

	// 用stack实现迭代方式
	stack<Node*> s;
	Node* proot = root;
	while (proot || !s.empty())
	{
		if (proot)
		{
			s.push(proot);
			proot = proot->left;

		}
		else
		{
			proot = s.top();
			cout << proot->data << endl;
			s.pop();
			proot = proot->right;
		}
	}
}

int main()
{
	//vector<int> v = { 1, -1, 2, 3 }; // -1代表空指针 顺序：根左右
	return 0;
}
#endif