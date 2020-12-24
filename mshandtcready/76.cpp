// https://www.cnblogs.com/huansky/p/13488234.html滑动窗口算法
/*
题目描述
给定两个字符串 S 和 T，求 S 中包含 T 所有字符的最短连续子字符串的长度，同时要求时间
复杂度不得超过 O„n”。

输入输出样例
输入是两个字符串 S 和 T，输出是一个 S 字符串的子串。
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

在这个样例中， S 中同时包含一个 A、一个 B、一个 C 的最短子字符串是“BANC”。
*/
#if 0
#include <iostream>
#include <vector>
using namespace std;

string minWindow(string S, string T) 
{
	vector<int> chars(128, 0);
	vector<bool> flag(128, false);
	
	// 先统计T中的字符情况
	for (int i = 0; i < T.size(); ++i) {
		flag[T[i]] = true;
		++chars[T[i]];
	}
	
	// 移动滑动窗口， 不断更改统计数据
	int cnt = 0, l = 0, min_l = 0, min_size = S.size() + 1;
	for (int r = 0; r < S.size(); ++r) {
		if (flag[S[r]]) {
			if (--chars[S[r]] >= 0) {
				++cnt;
			}
			
			// 若目前滑动窗口已包含T中全部字符，
			// 则尝试将l右移， 在不影响结果的情况下获得最短子字符串
			while (cnt == T.size()) {
				if (r - l + 1 < min_size) {
					min_l = l;
					min_size = r - l + 1;    // 目标串大小, 不断更新
				}
				if (flag[S[l]] && ++chars[S[l]] > 0) {
					--cnt;
				}
				++l;
			}
		}
	}

	return min_size > S.size() ? "" : S.substr(min_l, min_size);
}

int main()
{
	cout << minWindow("ADOBECODEBANC", "ABC") << endl;
	return 0;
}
#endif