// 颜色分类
#if 0
#include <iostream>
#include <vector>
using namespace std;

// 思路:0 挪到最前面，2 挪到最后面就完事儿了  注意 2 挪完如果换出来的不是 1，那么指针要回退，因为 0 和 2 都是需要再次移动的
class Solution
{
public:
    void sortColors(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 2)
            return;

        //双指针
        int p = 0, q = n - 1;
        for (int i = 0; i <= q; ++i)
        {
            if (nums[i] == 0)
            {
                nums[i] = nums[p];
                nums[p] = 0;
                ++p;
            }
            if (nums[i] == 2)
            {
                nums[i] = nums[q];
                nums[q] = 2;
                --q;
                if (nums[i] != 1)
                    --i;
            }
        }
        return;
    }
};

int main()
{
    Solution s;
	vector<int> v = {1, 0, 2, 0, 2, 1, 1, 0, 2, 0, 1 };
	s.sortColors(v);
	for (int& a : v)
	{
		cout << a << " ";
	}
	cout << endl;
	return 0;
}
#endif