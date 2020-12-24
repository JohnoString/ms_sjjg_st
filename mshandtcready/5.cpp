// 最长回文子串
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 暴力查找
// 思路：保证顺序的前提下 时间：O(n3) 空间：O(1)
string longestPalindrome(string s) {
    int len = s.length();
    if (len < 2) {
        return s;
    }
    int maxn = 1;
    int idx = 0;
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            string tmp = s.substr(i, j - i + 1);
            string tmp2 = tmp;
            reverse(tmp.begin(), tmp.end());
            if (tmp == tmp2 && j - i + 1 > maxn) {
                maxn = j - i + 1;
                idx = i;
            }
        }
    }
    return s.substr(idx, maxn);
}


// 动态规划 只遍历二维数组一半的区域
// 思路：找出状态转移方程
string longestPalindrome_dp(string s) {

    int size = s.size();
    if (size <= 1)  return s;  // 边界条件处理
    int len = 1;  // 记录回文子串的长度，回文子串的最小长度为1
    int start = 0; // 回文子串的开始位置

    /*
    这里有个有趣的现象就是如果我把下面的代码中的二维数组由 int 改为 vector<vector<int>> 后，就会超时，
    这说明 int 型的二维数组访问执行速度完爆 std 的 vector 啊，所以以后尽可能的还是用最原始的数据类型吧。
    */
    vector<vector<int>>dp(size, vector<int>(size, 0));  
    for (int i = 0; i < size; i++)  dp[i][i] = 1;  // 设置表格中对角线位置的值

    for (int j = 1; j < size; j++)  // i是开始位置，j是结束位置
    {
        for (int i = 0; i < j; i++)
        {
            if (s[i] == s[j])
            {
                if (j - i < 3)
                    dp[i][j] = 1; // 特殊情况处理:保证遍历范围在矩形的对角线之下(j>i) 反之亦然
                else
                    dp[i][j] = dp[i + 1][j - 1];  // 状态转移方程的确定是核心：i+1到j-1是回文, 说明i到j一定是回文
            }

            if (dp[i][j])   // 更新长度
            {
                if (j - i + 1 > len)
                {
                    len = j - i + 1;
                    start = i;
                }
            }
        }
    }

    return s.substr(start, len);
}

// 相同思路拓展：最长上升子序列
string longestRiseSub_dp(string s) {

    int size = s.size();
    if (size <= 1)  return s;  // 边界条件处理
    int len = 1;  // 记录长度，最小长度为1
    int start = 0; // 子串开始位置

    vector<vector<int>>dp(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)  dp[i][i] = 1;  // 设置表格中对角线位置的值

    for (int j = 1; j < size; j++)  // i是开始位置，j是结束位置
    {
        for (int i = 0; i < j; i++)
        {
            if (s[j] > s[j - 1])  // 升序 
            {
                if (j - i < 2)
                    dp[i][j] = 1; // 特殊情况处理:保证遍历范围在矩形的对角线之下(j>i) 反之亦然
                else
                    dp[i][j] = dp[i][j - 1];  // 状态转移方程
            }

            if (dp[i][j])   // 更新长度
            {
                if (j - i + 1 > len)
                {
                    len = j - i + 1;
                    start = i;
                }
            }
        }
    }

    return s.substr(start, len);
}

// 中心扩展 时间O(n^2) 空间O(1)
//int computeLen(string s, int l, int r) {
//    int len = s.length();
//    int i = l, j = r;
//    while (i >= 0 && j < len) {
//        if (s[i] == s[j]) {
//            i--; j++;
//        }
//        else
//        {
//            break;
//        }
//    }
//    return j - i - 1;
//}
//
//string longestPalindrome_center(string s) {
//    int len = s.length();
//    if (len < 2) {
//        return s;
//    }
//    int maxn = 1;
//    int idx = 0;
//
//    for (int i = 0; i < len - 1; i++) {
//        int oddLen = computeLen(s, i, i);
//        int evenLen = computeLen(s, i, i + 1);
//        int tempLen = max(oddLen, evenLen);
//        if (tempLen > maxn) {
//            maxn = tempLen;
//            idx = i - (tempLen - 1) / 2;
//        }
//    }
//    return s.substr(idx, maxn);
//}
//
//// 马拉车算法: 时间：O(n)
//string longestPalindrome_mlc(string s) {
//    string t = "$#";
//    for (int i = 0; i < s.size(); ++i) {
//        t += s[i];
//        t += '#';
//    }
//    int p[t.size()] = { 0 }, id = 0, mx = 0, resId = 0, resMx = 0;
//    for (int i = 1; i < t.size(); ++i) {
//        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
//        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
//        if (mx < i + p[i]) {
//            mx = i + p[i];
//            id = i;
//        }
//        if (resMx < p[i]) {
//            resMx = p[i];
//            resId = i;
//        }
//    }
//    return s.substr((resId - resMx) / 2, resMx - 1);
//}

int main()
{
   // cout << longestPalindrome_dp("abcbaaaabcddd") << endl;
    cout << longestRiseSub_dp("abcbaaaabcddd") << endl;
	return 0;
}
#endif