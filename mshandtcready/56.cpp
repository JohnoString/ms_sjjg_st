// 合并区间 明天看
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 思路： 将所有区间按照第一个key进行升序排序, 遍历一次数组就可以合并 注意：有合并操作需要需要清除前一个节点
typedef struct Node_
{
	int a;
	int b;
}Node;

bool cmp(Node m, Node n)
{
	return m.a < n.a;
}

vector<Node> GetMerge(vector<Node> v)
{
	vector<Node> vout;
	if (v.empty())
	{
		return vout;
	}

	std::sort(v.begin(), v.end(), cmp);

	for (Node& n : v)
	{
		cout << n.a << ", " << n.b << endl;
	}
	cout << endl;

	Node n = v.front();
	vout.emplace_back(n);
	for (int i = 1; i < v.size(); ++i)
	{
		vout.pop_back();
		if (n.b < v[i].a)
		{
			vout.emplace_back(n);
			vout.emplace_back(v[i]);
			n = v[i];
		}
		else if (n.b == v[i].a)
		{
			n.b = v[i].b;
			vout.emplace_back(n);
		}
		else
		{
			if (n.b < v[i].b)
			{
				n.b = v[i].b;
			}

			vout.emplace_back(n);
		}
	}

	return vout;
}

int main()
{
	vector<Node> v = { {1, 3}, {2, 6}, {8, 10}, {5, 18} };
	vector<Node> vv = GetMerge(v);
	for (Node& n : vv)
	{
		cout << n.a << ", " << n.b << endl;
	}
	cout << endl;
	return 0;
}
#endif