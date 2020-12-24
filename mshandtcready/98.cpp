// 验证二叉搜索树：左<根<右
#if 0
#include <iostream>
#include <stack>
using namespace std;

// 思路：中序遍历判断是否有例外
typedef struct Node_Tree
{
	int data;
	Node* left;
	Node* right;
}Node;

bool midTrv(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	
	int inorder = root->data;

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
			if (proot->data <= inorder)
			{
				return false;
			}

			inorder = proot->data;
			proot = proot->right;
		}
	}
}

int main()
{
	return 0;
}
#endif