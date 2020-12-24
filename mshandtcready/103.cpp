// �������ľ���β�α���
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

// ˼·
/*
����͵�102�����ơ�ͨ��һ�����������ƣ���Ȼ�ǵ���һ����ͨ�Ĺ������������ʵ�֡�Ψһ��ͬ���ǣ�
�ж��Ƿ���Ҫ����ǰ�����鷴ת���ڳ����ж���һ����ǩ��flag����ʵ�֡�flag����������ȣ����ڵ�Ϊ
�㡣�������Ϊ������ʱ�򣬲���Ҫ��ת���������Ϊż����ʱ����Ҫ��ת��
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