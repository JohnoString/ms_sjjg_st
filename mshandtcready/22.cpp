// 括号生成 排后
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// 回溯
//class Solution {
//public:
//    vector<string> generateParenthesis(int n) {
//        vector<string> ret;
//        if (n < 1) return ret;
//        string s = "";
//        help(s, 0, 0, n, ret);
//        return ret;
//    }
//
//private:
//    // left：左括号数量，right：右括号数量
//    void help(string s, int left, int right, int n, vector<string>& ret) {
//        if (s.size() == n * 2) {
//            ret.push_back(s);
//            return;
//        }
//        if (left < n)
//            help(s + "(", left + 1, right, n, ret);
//        if (right < left)
//            help(s + ")", left, right + 1, n, ret);
//    }
//};

// 动态规划
class Solution {
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> ans;
        vector<vector<string>> dp(n + 1);
        dp[1].push_back("()");
        for (int i = 2; i <= n; i++)
        {
            // 情况1
            for (int j = 0; j < dp[i - 1].size(); j++)
                dp[i].push_back("(" + dp[i - 1][j] + ")");
            // 枚举终点，将i拆分为j，i-j
            for (int j = 1; j <= i - 1; j++)
            {
                for (int l = 0; l < dp[j].size(); l++)
                {
                    for (int r = 0; r < dp[i - j].size(); r++)
                    {
                        dp[i].push_back(dp[j][l] + dp[i - j][r]);
                        dp[i].push_back(dp[i - j][r] + dp[j][l]);
                    }
                }
            }
            // hashset去重
            unordered_set<string> se(dp[i].begin(), dp[i].end());
            dp[i].assign(se.begin(), se.end());
        }
        for (int j = 0; j < dp[n].size(); j++)
            ans.push_back(dp[n][j]);
        return ans;
    }
};


int main()
{
    Solution s;
    vector<string> vs = s.generateParenthesis(3);
    for (string& s : vs)
    {
        cout << s << " ";
    }
    cout << endl;
	return 0;
}
#endif