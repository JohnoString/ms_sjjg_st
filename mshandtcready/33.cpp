// 搜索旋转排序数组 二分查找的变种
#if 0
#include <iostream>
#include <vector>
using namespace std;

int SerchKey(vector<int> v, int key)
{
	if (v.empty())
	{
		return -1;
	}

	int left = 0;
	int right = v.size() - 1;
	int mid = (left + right) / 2;
	while (left <= right)
	{
		if (v[mid] == key)
			return mid;
		else if (v[left] <= v[mid])
		{
			if (key >= v[left] && key < v[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		else
		{
			if (key > v[mid] && key <= v[right])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}

		mid = (left + right) / 2;
	}
}

int main()
{
	vector<int> v = { 4,5,6,7,0,1,2 };
	cout << SerchKey(v, 2) << endl;
	return 0;
}
#endif