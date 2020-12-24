// ��ͬ·��
#if 0
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int uniquePaths(int m, int n) {
		if (m <= 0 || n <= 0)
			return 0;
		else if (m == 1 || n == 1)//ֻ��һֱ�����߻���һֱ�����ߣ�����·����Ϊ 1
			return 1;
		else if (m == 2 && n == 2)
			return 2;
		else if ((m == 3 && n == 2) || (m == 2 && n == 3))
			return 3;
		int paths = 0;
		paths += uniquePaths(m - 1, n);
		paths += uniquePaths(m, n - 1);
		return paths;
	}
};

// ���� �ᳬʱ��
//typedef struct Node_Index
//{
//	int m;
//	int n;
//}Node;
//
//void GetPath(vector<vector<Node> > &out, int m, int n, vector<Node>& path, vector<vector<bool> > used)
//{
//	if (path.size() == m + n - 1)
//	{
//		out.push_back(path);
//	}
//	else
//	{
//		Node tmp = {0, 0};
//		for (int i = 0; i < m; ++i)
//		{
//			for (int j = 0; j < n; ++j)
//			{
//				Node node = { i, j };
//				if (used[i][j])
//				{
//					continue;
//				}
//
//				if (j == n - 1 || i == m - 1)
//				{
//					tmp = node;
//				}
//				
//				if ((node.m > tmp.m&& node.n < tmp.n) ||
//					(node.n > tmp.n&& node.m < tmp.m))
//				{
//					continue;
//				}
//
//				path.emplace_back(node);
//				used[i][j] = true;
//				GetPath(out, m, n, path, used);
//				path.pop_back();
//				used[i][j] = false;
//			}
//		}
//	}
//}
//
//int GetAllPath(vector<vector<Node> > &out, int m, int n)
//{
//	vector<Node> path;
//	if (m <= 0 && n <= 0)
//	{
//		return 0;
//	}
//	else if ((m > 0 && n <= 0) || (m <= 0 && n > 0))
//	{
//		return 1;
//	}
//	else
//	{
//		vector<bool> vb(n, false);
//		vector<vector<bool> > used;
//		used.resize(m);
//		for (vector<bool>& used_ : used)
//		{
//			used_ = vb;
//		}
//		GetPath(out, m, n, path, used);
//		return out.size();
//	}
//}

// ��̬�滮: ״̬ת�Ʒ���dp[i][j]=dp[i-1][j]+dp[i][j-1] dp[i][j]��ָ��(0, 0)��(i, j)��·������
// �ռ䣺O(m*n) ʱ�䣺O(m*n)
int GetAllPath_dp(vector<vector<int> > dp, int m, int n)
{
	if (m <= 0 && n <= 0)
	{
		return 0;
	}
	else if ((m > 0 && n <= 0) || (m <= 0 && n > 0))
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m; ++i) dp[i][0] = 1;
		for (int i = 0; i < n; ++i) dp[0][i] = 1;
		for (int i = 1; i < m; ++i)
		{
			for (int j = 1; j < n; ++j)
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}

		return dp[m - 1][n - 1];
	}
}

/*
�Ż�һ������dp[i][j] = dp[i-1][j] + dp[i][j-1]�����ֻ��Ҫ������ǰ������һ�е����� (�ڶ�̬�����У���pre[j] = dp[i-1][j])�����У��ռ临�Ӷ�O(2n)��
�Ż�����cur[j] += cur[j-1], ��cur[j] = cur[j] + cur[j-1] �ȼ���˼·��-->> cur[j] = pre[j] + cur[j-1]����˿ռ临�Ӷ�ΪO(n).
*/
// �ռ䣺O(2n) ʱ�䣺O(m*n)
class Solution_2n {
public:
	int uniquePaths(int m, int n) {
		vector<int> pre(n, 1);
		vector<int> cur(n, 1);
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				cur[j] = cur[j - 1] + pre[j];
			}
			pre = cur;
		}
		return pre[n - 1];
	}
};

// �ռ䣺O(n) ʱ�䣺O(m*n)  ֱ��ѭ�����ǿռ�ʹ��
class Solution_n {
public:
	int uniquePaths(int m, int n) {
		vector<int> cur(n, 1);
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				cur[j] += cur[j - 1];
			}
		}
		return cur[n - 1];
	}
};

int main()
{
	//vector<vector<Node> > out;
	//cout << GetAllPath(out, 2, 3) << endl;
	//Solution s;
	//cout << s.uniquePaths(12, 212) << endl;

	vector<vector<int> > dp(5, vector<int>(6));
	cout << GetAllPath_dp(dp, 5, 6) << endl;
	
	Solution_2n s2n;
	cout << s2n.uniquePaths(5, 6) << endl;

	Solution_n sn;
	cout << sn.uniquePaths(5, 6) << endl;
	return 0;
}
#endif