// 在排序的数组中查找元素的第一个和最后一个位置
#if 0
#include <iostream>
#include <vector>
using namespace std;

// 遍历 时间：O(n) 空间：O(1)
vector<int> GetFirstAndLastIndex(vector<int> v, int key)
{
	vector<int> vres;

	int a = -1;  // 记录左
	int b = -1;  // 记录右
	bool isleft = false;
	bool isright = false;
	for (int i = 0; i < v.size(); ++i)
	{
		if (key == v[i])
		{
			if (!isleft)
			{
				a = i;
				isleft = true;
				isright = false;
				continue;
			}

			if (!isright)
			{
				b = i;
			}
		}
	}

	vres.emplace_back(a);
	vres.emplace_back(b);
	return vres;
}
 
/*假设我们目前有左指针，右指针，并判断中间值和目标值之间的关系，那么一共有三种关系情况

中间值小于目标值，则目标值只可能在右子数组
中间值大于目标值，则目标值只可能在左子数组
中间值等于目标值，则目标值在左右子数组都可能存在
结合情况1和情况3，当中间值小于目标值，则将左指针右移至中间，否则将右指针左移至中间。这样一定可以找到目标值的初始下标
同理，结合情况2和情况3，当中间值大于目标值，则将右指针左移至中间，否则将左指针右移至中间，这样一定可以找到目标值的结束下标。
*/

int findFirst(vector<int> nums, int target) {
    int idx = -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (nums[mid] >= target) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
        if (nums[mid] == target) idx = mid;
    }
    return idx;
}

int findLast(vector<int> nums, int target) {
    int idx = -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (nums[mid] <= target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
        if (nums[mid] == target) idx = mid;
    }
    return idx;
}

vector<int> searchRange3(vector<int> nums, int target) {
    vector<int> result;
    result.emplace_back(findFirst(nums, target));
    result.emplace_back(findLast(nums, target));
    return result;
}

int main()
{
	vector<int> v = { 5,7,7,8,8,10 };
	vector<int> vv = searchRange3(v, 8);
	cout << vv[0] << ", " << vv[1] << endl;
	return 0;
}
#endif