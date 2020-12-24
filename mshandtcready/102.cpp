// 二叉树的层序遍历
#if 0
#include <iostream>
#include <queue>
using namespace std;

typedef struct Node_Tree
{
	int data;
	Node* left;
	Node* right;
}Node;

// 思路：借助辅助队列
void LayerTrv(Node* root)
{
	queue<Node*> q;
	if (root == nullptr)
	{
		q.push(root);
	}

	Node* proot = root;
	while (!q.empty())
	{
		cout << q.front()->data << endl;
		if (q.front()->left)
		{
			q.push(q.front()->left);
		}
		
		if (q.front()->right)
		{
			q.push(q.front()->right);
		}

		q.pop();
	}
}

int main()
{
	return 0;
}
#endif