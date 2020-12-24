// 分割回文串
/*
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的最少分割次数。
示例:

输入: "aab"
输出: 1
解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
*/

#if 0
#include <iostream>
//#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

// 思路：动态规划
class Solution {
public:
    int minCut(string s) {
        if (s.size() == 0) return 0;
        int len = s.size();
        vector<vector<bool>> flag(len, vector<bool>(len, false));
        for (int k = 0; k < len; k++) {
            for (int i = 0, j = k; j < len; i++, j++) {
                if (i == j) flag[i][j] = true;
                else if (s[i] == s[j]) {
                    if (i == j - 1) flag[i][j] = true;
                    else if (flag[i + 1][j - 1]) flag[i][j] = true;
                    else flag[i][j] = false;
                }
                else {
                    flag[i][j] = false;
                }
            }
        }

        vector<int> nums(len, len - 1);
        nums[0] = 0;
        for (int i = 1; i < len; i++) {
            if (flag[0][i] == true) {
                nums[i] = 0;
                continue;
            }
            for (int j = i - 1; j >= 0; j--) {
                if (flag[j + 1][i] == false) continue;
                nums[i] = min(nums[i], nums[j] + 1);
                if (nums[i] == 1) break;
            }
        }
        return nums[len - 1];
    }
};

class Solution_midkz {
public:
    int minCut(string s) {
        if (s.size() == 0) return 0;
        int len = s.size();
        vector<int> nums(len + 1, 0);
        for (int i = 0; i <= len; i++) nums[i] = i - 1;
        for (int i = 1; i <= len; i++) {
            for (int j = 0; j < i && i + j <= len && s[i - j - 1] == s[i + j - 1]; j++) {
                nums[i + j] = min(nums[i + j], nums[i - j - 1] + 1);
            }
            for (int j = 0; i - j > 0 && i + j + 1 <= len && s[i - 1] == s[i] && s[i - j - 1] == s[i + j]; j++) {
                nums[i + j + 1] = min(nums[i + j + 1], nums[i - j - 1] + 1);
            }
        }
        return nums[len];
    }
};

// 回溯-容易超时
class Solution_huisu {
public:
    int minCut(string s) {
      
    }
};

int main()
{
    Solution s;
    cout << s.minCut("acb") << endl;
	return 0;
}
#endif