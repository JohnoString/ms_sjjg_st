// 跳跃游戏 贪心
#if 0
#include <iostream>
#include <vector>
using namespace std;

// 思路：维护一个实时更新的最大可到达长度
bool IsArrive(vector<int> v)
{
	if (v.empty())
	{
		return false;
	}

	int max = -1;  // 当前最远可到达位置
	for (int i = 0; i < v.size() - 1; ++i)
	{
		if (i + v[i] > max)
		{
			max = i + v[i];
		}
	}

	if (max >= v.size() - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	vector<int> v = {3,2,1,0,4};
	bool b = IsArrive(v);
	cout << b << endl;
	return 0;
}
#endif