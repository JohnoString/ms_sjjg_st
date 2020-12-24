// ���ÿ���ڵ����һ���Ҳ�ڵ��ָ��
#if 0  // TODO:shu�������˲���
#include <iostream>
using namespace std;

typedef struct Node_Tree
{
    int data;
    Node* left;
    Node* right;
    Node* next;
}Node;

// ʱ�䣺O(n) �ռ䣺O(1)
class Solution {
public:
    Node* connect(Node* root) {
        Node* result = root;
        Node* start = root;//��һ���ʼ���ʼ���õ�һ��
        while (start != NULL && start->left != NULL) {//�˲����Ѿ����Ӻõ�
            root = start;//root������һ��
            while (root != NULL) {
                root->left->next = root->right;//�ֽ�root�������ӽڵ����Ӻ�
                if (root->next != NULL) {//rootͬ����滹�нڵ�
                    root->right->next = root->next->left;//����Ҫ��root��������next��root��һ���ڵ������������
                }
                root = root->next;//root��ͬһ�����
            }
            start = start->left;//��һ���Ѿ����Ӻ��ˣ����Ե��ƶ�����һ��
        }
        return result;
    }
};

// ʱ�䣺O(n) �ռ䣺O(1)
class Solution_Res {
public:
    Node* connect(Node* root) {
        if (root == NULL || root->left == NULL) {
            return root;
        }
        Node* result = root;
        root->left->next = root->right;//���ӵ�ǰ���ڵ�������ӽڵ�
        if (root->next != NULL) {//���root����ͬ��������
            root->right->next = root->next->left;
        }
        connect(root->left);//��������������
        connect(root->right);//��������������
        return result;
    }
};

int main()
{
	return 0;
}
#endif