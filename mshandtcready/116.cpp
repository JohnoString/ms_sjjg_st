// 填充每个节点的下一个右侧节点的指针
#if 0  // TODO:shu中新增此操作
#include <iostream>
using namespace std;

typedef struct Node_Tree
{
    int data;
    Node* left;
    Node* right;
    Node* next;
}Node;

// 时间：O(n) 空间：O(1)
class Solution {
public:
    Node* connect(Node* root) {
        Node* result = root;
        Node* start = root;//第一层初始化最开始填充好的一层
        while (start != NULL && start->left != NULL) {//此层是已经连接好的
            root = start;//root遍历这一层
            while (root != NULL) {
                root->left->next = root->right;//现将root的左右子节点连接号
                if (root->next != NULL) {//root同层后面还有节点
                    root->right->next = root->next->left;//则需要将root右子树的next与root下一个节点的左子树连接
                }
                root = root->next;//root在同一层后移
            }
            start = start->left;//下一层已经连接好了，所以得移动到下一层
        }
        return result;
    }
};

// 时间：O(n) 空间：O(1)
class Solution_Res {
public:
    Node* connect(Node* root) {
        if (root == NULL || root->left == NULL) {
            return root;
        }
        Node* result = root;
        root->left->next = root->right;//连接当前根节点的左右子节点
        if (root->next != NULL) {//如果root还有同层相连的
            root->right->next = root->next->left;
        }
        connect(root->left);//连接它的左子树
        connect(root->right);//连接它的右子树
        return result;
    }
};

int main()
{
	return 0;
}
#endif