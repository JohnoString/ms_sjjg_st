// 盛水最多的容器 时间：O(n) 空间：O(1)
// 思路：每次移动较小的边, 并更新最大容量
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

uint32_t GetMaxCapacity(const vector<uint32_t> v)
{
	if (v.empty())
	{
		return -1;
	}

	uint32_t l = 0, r = v.size() - 1;
	uint32_t maxC = 0;
	uint32_t tmp = 0；
	while (l < r)
	{
		tmp = min(v[l], v[r]) * (r - l);
		if (tmp > maxC)
		{
			maxC = tmp;
		}

		if (v[l] <= v[r])
		{
			l++;
		}
		else
		{
			r--;
		}
	}

	return maxC;
}

int main()
{
	vector<uint32_t> v = { 5, 10, 12, 3, 1, 2, 5, 10 };
	cout << GetMaxCapacity(v) << endl;
	return 0;
}
#endif