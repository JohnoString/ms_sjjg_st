// ������Ӵ�
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ��������
// ˼·����֤˳���ǰ���� ʱ�䣺O(n3) �ռ䣺O(1)
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


// ��̬�滮 ֻ������ά����һ�������
// ˼·���ҳ�״̬ת�Ʒ���
string longestPalindrome_dp(string s) {

    int size = s.size();
    if (size <= 1)  return s;  // �߽���������
    int len = 1;  // ��¼�����Ӵ��ĳ��ȣ������Ӵ�����С����Ϊ1
    int start = 0; // �����Ӵ��Ŀ�ʼλ��

    /*
    �����и���Ȥ�������������Ұ�����Ĵ����еĶ�ά������ int ��Ϊ vector<vector<int>> �󣬾ͻᳬʱ��
    ��˵�� int �͵Ķ�ά�������ִ���ٶ��걬 std �� vector ���������Ժ󾡿��ܵĻ�������ԭʼ���������Ͱɡ�
    */
    vector<vector<int>>dp(size, vector<int>(size, 0));  
    for (int i = 0; i < size; i++)  dp[i][i] = 1;  // ���ñ���жԽ���λ�õ�ֵ

    for (int j = 1; j < size; j++)  // i�ǿ�ʼλ�ã�j�ǽ���λ��
    {
        for (int i = 0; i < j; i++)
        {
            if (s[i] == s[j])
            {
                if (j - i < 3)
                    dp[i][j] = 1; // �����������:��֤������Χ�ھ��εĶԽ���֮��(j>i) ��֮��Ȼ
                else
                    dp[i][j] = dp[i + 1][j - 1];  // ״̬ת�Ʒ��̵�ȷ���Ǻ��ģ�i+1��j-1�ǻ���, ˵��i��jһ���ǻ���
            }

            if (dp[i][j])   // ���³���
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

// ��ͬ˼·��չ�������������
string longestRiseSub_dp(string s) {

    int size = s.size();
    if (size <= 1)  return s;  // �߽���������
    int len = 1;  // ��¼���ȣ���С����Ϊ1
    int start = 0; // �Ӵ���ʼλ��

    vector<vector<int>>dp(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)  dp[i][i] = 1;  // ���ñ���жԽ���λ�õ�ֵ

    for (int j = 1; j < size; j++)  // i�ǿ�ʼλ�ã�j�ǽ���λ��
    {
        for (int i = 0; i < j; i++)
        {
            if (s[j] > s[j - 1])  // ���� 
            {
                if (j - i < 2)
                    dp[i][j] = 1; // �����������:��֤������Χ�ھ��εĶԽ���֮��(j>i) ��֮��Ȼ
                else
                    dp[i][j] = dp[i][j - 1];  // ״̬ת�Ʒ���
            }

            if (dp[i][j])   // ���³���
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

// ������չ ʱ��O(n^2) �ռ�O(1)
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
//// �������㷨: ʱ�䣺O(n)
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