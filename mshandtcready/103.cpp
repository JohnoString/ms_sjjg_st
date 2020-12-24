// 二叉树的锯齿形层次遍历
#if 0
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef struct Node_Tree
{
	int data;
    TreeNode* left;
    TreeNode* right;
}TreeNode;

// 思路
/*
本题和第102题类似。通过一个队列来控制，仍然是当做一个普通的广度优先搜索来实现。唯一不同的是，
判断是否需要将当前的数组反转。在程序中定义一个标签（flag）来实现。flag代表树的深度，根节点为
零。树的深度为奇数的时候，不需要反转，树的深度为偶数的时候，需要反转。
*/
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        int flag = 0;
        while (!q.empty())
        {
            vector<int> temp;
            auto size = q.size();
            while (size--)
            {
                TreeNode* node = q.front();
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
};

int main()
{
	return 0;
}
#endif