// ��֤��������������<��<��
#if 0
#include <iostream>
#include <stack>
using namespace std;

// ˼·����������ж��Ƿ�������
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

	// ��stackʵ�ֵ�����ʽ
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