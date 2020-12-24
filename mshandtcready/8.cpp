// �ַ���ת������ ʱ�䣺O(n) �ռ䣺O(1)
#if 0
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Automaton {
    string state = "start";
    // ö����һ�����е�����(����(in_number)������(signed)���հ�(start)������(end)ǰ������Ƿ���е����)
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };

    int get_col(char c) {
        if (isspace(c)) return 0;   // �հ��ַ�ֻ�����ո�
        if (c == '+' or c == '-') return 1;
        if (isdigit(c)) return 2;
        return 3;
    }
public:
    int sign = 1;    // ��������
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};

int main()
{
    Solution s;
    cout << s.myAtoi("-2 2324 234    1\n3 2sfwe13213213213213") << endl;
	return 0;
}
#endif