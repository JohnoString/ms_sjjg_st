// 子集 回溯 时间：O(n*2~n) 空间：O(n)
#if 0 
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;

    void dfs(int cur, vector<int>& nums) {
        if (cur == nums.size()) {
            ans.push_back(t);
            return;
        }
        t.push_back(nums[cur]);
        dfs(cur + 1, nums);
        t.pop_back();
        dfs(cur + 1, nums);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(0, nums);
        return ans;
    }
};

int main()
{
    Solution s;
    vector<int> v = { 1, 2, 3, 4 };
    vector<vector<int>> vv = s.subsets(v);
    for (vector<int>& vvv : vv)
    {
        for (int& a : vvv)
        {
            cout << a;
        }

        cout << endl;
    }
	return 0;
}
#endif